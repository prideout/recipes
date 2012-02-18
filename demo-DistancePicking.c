// Distance Picking OpenGL Demo by Philip Rideout
// Licensed under the Creative Commons Attribution 3.0 Unported License. 
// http://creativecommons.org/licenses/by/3.0/

#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "pez.h"
#include "vmath.h"

typedef struct {
    int VertexCount;
    int IndexCount;
    GLuint Vao;
} MeshPod;

typedef struct {
    Matrix4 Projection;
    Matrix4 Ortho;
    Matrix4 Modelview;
    Matrix4 View;
    Matrix4 Model;
    Matrix3 Normal;
    GLfloat PackedNormal[9];
} TransformsPod;

struct {
    bool IsDragging;
    float Theta;
    Vector3 Mouse;
    GLuint QueryObject;
    GLuint LitProgram;
    GLuint QuadProgram;
    GLuint SpriteProgram;
    GLuint ErodeProgram;
    GLuint QuadVao;
    GLuint OffscreenFbo;
    GLuint ColorTexture;
    GLenum ColorAttachment;
    GLenum DistanceAttachments[2]; // ping-pong
    GLuint DistanceTextures[2]; // ping-pong
    MeshPod TrefoilKnot;
    TransformsPod Transforms;
} Globals;

typedef struct {
    Vector3 Position;
    Vector3 Normal;
} Vertex;

static GLuint LoadProgram(const char* vsKey, const char* gsKey, const char* fsKey);
static GLuint CurrentProgram();
static MeshPod CreateTrefoil();
static GLuint CreateRenderTarget();
static GLuint CreateQuad(int sourceWidth, int sourceHeight, int destWidth, int destHeight);
static void SwapPingPong();
static void DrawBuffers(const char* fsOut0, GLenum attachment0,
                        const char* fsOut1, GLenum attachment1);

#define u(x) glGetUniformLocation(CurrentProgram(), x)
#define a(x) glGetAttribLocation(CurrentProgram(), x)
#define f(x) glGetFragDataLocation(CurrentProgram(), x)
#define offset(x) ((const GLvoid*)x)

PezConfig PezGetConfig()
{
    PezConfig config;
    config.Title = __FILE__;
    config.Width = 853;
    config.Height = 480;
    config.Multisampling = 0;
    config.VerticalSync = 1;
    return config;
}

void PezInitialize()
{
    const PezConfig cfg = PezGetConfig();
    pezSwAddDirective("*", "#extension GL_ARB_explicit_attrib_location : enable");

    // Compile shaders
    Globals.QuadProgram = LoadProgram("Quad.VS", 0, "Quad.FS");
    Globals.SpriteProgram = LoadProgram("Sprite.VS", "Sprite.GS", "Sprite.FS");
    Globals.ErodeProgram = LoadProgram("Quad.VS", 0, "Erode.FS");
    Globals.LitProgram = LoadProgram("Lit.VS", 0, "Lit.FS");

    // Set up viewport
    float fovy = 16 * TwoPi / 180;
    float aspect = (float) cfg.Width / cfg.Height;
    float zNear = 0.1, zFar = 300;
    Globals.Transforms.Projection = M4MakePerspective(fovy, aspect, zNear, zFar);
    Globals.Transforms.Ortho = M4MakeOrthographic(0, cfg.Width, cfg.Height, 0, 0, 1);

    // Create geometry
    Globals.QuadVao = CreateQuad(cfg.Width, -cfg.Height, cfg.Width, cfg.Height);
    glUseProgram(Globals.LitProgram);
    Globals.TrefoilKnot = CreateTrefoil();
    Globals.OffscreenFbo = CreateRenderTarget();

    // Misc Initialization
    glGenQueries(1, &Globals.QueryObject);
    Globals.IsDragging = false;
    Globals.Theta = 0;
    Globals.Mouse.z = -1;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PezUpdate(float seconds)
{
    const float RadiansPerSecond = 0.5f;
    Globals.Theta += seconds * RadiansPerSecond;
    
    // Create the model-view matrix:
    Globals.Transforms.Model = M4MakeRotationY(Globals.Theta);
    Point3 eye = P3MakeFromElems(0, 0, 4);
    Point3 target = P3MakeFromElems(0, 0, 0);
    Vector3 up = V3MakeFromElems(0, 1, 0);
    Globals.Transforms.View = M4MakeLookAt(eye, target, up);
    Globals.Transforms.Modelview = M4Mul(Globals.Transforms.View, Globals.Transforms.Model);
    Globals.Transforms.Normal = M4GetUpper3x3(Globals.Transforms.Modelview);
    for (int i = 0; i < 9; ++i)
        Globals.Transforms.PackedNormal[i] = M3GetElem(Globals.Transforms.Normal, i/3, i%3);
}

void PezRender()
{
    static int frame = 0; frame++;

    float* pModel = (float*) &Globals.Transforms.Model;
    float* pView = (float*) &Globals.Transforms.View;
    float* pModelview = (float*) &Globals.Transforms.Modelview;
    float* pProjection = (float*) &Globals.Transforms.Projection;
    float* pNormalMatrix = &Globals.Transforms.PackedNormal[0];
    MeshPod* mesh = &Globals.TrefoilKnot;
    float initColor[4] = { 0.5f, 0.6f, 0.7f, 1.0f };
    float initDistance[4] = { 0, 0, FLT_MAX, 0 };
    int MaxPassCount = 50;
    const float w = PezGetConfig().Width;
    const float h = PezGetConfig().Height;
    bool isComputingDistance = true;

    // Create the seed texture and perform lighting simultaneously:
    glBindFramebuffer(GL_FRAMEBUFFER, Globals.OffscreenFbo);
    glUseProgram(Globals.LitProgram);
    DrawBuffers("FragColor", Globals.ColorAttachment,
                "DistanceMap", Globals.DistanceAttachments[0]);
    glBindVertexArray(mesh->Vao);
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pView);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pModel);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pModelview);
    glUniformMatrix4fv(u("Projection"), 1, 0, pProjection);
    glUniformMatrix3fv(u("NormalMatrix"), 1, 0, pNormalMatrix);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearBufferfv(GL_COLOR, 0, initColor);
    if (isComputingDistance) {
        glClearBufferfv(GL_COLOR, 1, initDistance);
    }
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, mesh->IndexCount, GL_UNSIGNED_SHORT, 0);
    glDisable(GL_DEPTH_TEST);

    // Compute a distance field, first with horizontal passes, then with vertical passes:
    glUseProgram(Globals.ErodeProgram);
    glUniform2f(u("InverseViewport"), 1.0f / w, 1.0f / h);
    glBindVertexArray(Globals.QuadVao);
    glUniform2f(u("Offset"), 1.0f / PezGetConfig().Width, 0);
    for (int pass = 0, isVertical = 0; isComputingDistance; ++pass) {
        
        // Swap the source & destination surfaces and bind them:
        SwapPingPong();
        glBindTexture(GL_TEXTURE_2D, Globals.DistanceTextures[0]);
        DrawBuffers("DistanceMap", Globals.DistanceAttachments[0], 0, 0);

        // Draw the full-screen quad:
        glUniform1f(u("Beta"), (GLfloat) pass * 2 + 1);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        if (pass < MaxPassCount)
            continue;

        // If we exhausted the pass count, we're done with this phase:
        if (!isVertical) {
            isVertical = !isVertical;
            pass = 0;
            glUniform2f(u("Offset"), 0, 1.0f / PezGetConfig().Height);
        } else {
            break;
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // Draw the backbuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
    glUseProgram(Globals.QuadProgram);
    glBindVertexArray(Globals.QuadVao);
    if (Globals.IsDragging) {
        glBindTexture(GL_TEXTURE_2D, Globals.DistanceTextures[0]);
        glUniform3f(u("Scale"),
                    1.0f / PezGetConfig().Width,
                    1.0f / PezGetConfig().Width,
                    1.0f / 100.0f );
    } else {
        glBindTexture(GL_TEXTURE_2D, Globals.ColorTexture);
        glUniform3f(u("Scale"), 1.0f, 1.0f, 1.0f);
    }
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Leave early if we don't have a valid mouse position yet
    if (Globals.Mouse.z < 0) {
        return;
    }

    glUseProgram(Globals.SpriteProgram);

    // Update the teeny VBO for the mouse cursor
    if (true) {
        float x = Globals.Mouse.x;
        float y = h - Globals.Mouse.y - 1;
        glUniform2f(u("MouseLocation"), x, y);
    }

    Matrix4 i = M4MakeIdentity();
    float* pIdentity = (float*) &i;
    float* pOrtho = (float*) &Globals.Transforms.Ortho;

    glBindTexture(GL_TEXTURE_2D, Globals.DistanceTextures[0]);
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pIdentity);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pIdentity);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pIdentity);
    glUniformMatrix4fv(u("Projection"), 1, 0, pOrtho);
    glUniformMatrix3fv(u("NormalMatrix"), 1, 0, pNormalMatrix);
    glUniform2f(u("SpriteSize"), 32, 32);
    glUniform2f(u("HalfViewport"), w / 2.0f, h / 2.0f);
    glUniform2f(u("InverseViewport"), 1.0f / w, 1.0f / h);
    glUniform1f(u("Height"), h);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisable(GL_BLEND);
}

void PezHandleMouse(int x, int y, int action)
{
    Globals.Mouse.x = x;
    Globals.Mouse.y = y;
    Globals.Mouse.z = action;

    if (action == PEZ_DOWN) {
        Globals.IsDragging = true;
    } else if (action == PEZ_UP) {
        Globals.IsDragging = false;
    }
}

static GLuint CurrentProgram()
{
    GLuint p;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &p);
    return p;
}

static GLuint LoadProgram(const char* vsKey, const char* gsKey, const char* fsKey)
{
    GLchar spew[256];
    GLint compileSuccess;
    GLuint programHandle = glCreateProgram();

    const char* vsSource = pezGetShader(vsKey);
    pezCheck(vsSource != 0, "Can't find vshader: %s\n", vsKey);
    GLuint vsHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsHandle, 1, &vsSource, 0);
    glCompileShader(vsHandle);
    glGetShaderiv(vsHandle, GL_COMPILE_STATUS, &compileSuccess);
    glGetShaderInfoLog(vsHandle, sizeof(spew), 0, spew);
    pezCheck(compileSuccess, "Can't compile vshader:\n%s", spew);
    glAttachShader(programHandle, vsHandle);

    if (gsKey) {
        const char* gsSource = pezGetShader(gsKey);
        pezCheck(gsSource != 0, "Can't find gshader: %s\n", gsKey);
        GLuint gsHandle = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gsHandle, 1, &gsSource, 0);
        glCompileShader(gsHandle);
        glGetShaderiv(gsHandle, GL_COMPILE_STATUS, &compileSuccess);
        glGetShaderInfoLog(gsHandle, sizeof(spew), 0, spew);
        pezCheck(compileSuccess, "Can't compile gshader:\n%s", spew);
        glAttachShader(programHandle, gsHandle);
    }

    const char* fsSource = pezGetShader(fsKey);
    pezCheck(fsSource != 0, "Can't find fshader: %s\n", fsKey);
    GLuint fsHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsHandle, 1, &fsSource, 0);
    glCompileShader(fsHandle);
    glGetShaderiv(fsHandle, GL_COMPILE_STATUS, &compileSuccess);
    glGetShaderInfoLog(fsHandle, sizeof(spew), 0, spew);
    pezCheck(compileSuccess, "Can't compile fshader:\n%s", spew);
    glAttachShader(programHandle, fsHandle);

    glLinkProgram(programHandle);
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    glGetProgramInfoLog(programHandle, sizeof(spew), 0, spew);
    pezCheck(linkSuccess, "Can't link shaders:\n%s", spew);
    glUseProgram(programHandle);
    return programHandle;
}

static GLuint CreateRenderTarget()
{
    GLuint* colorTexture = &Globals.ColorTexture;

    pezCheck(GL_NO_ERROR == glGetError(), "OpenGL error on line %d",  __LINE__);
    PezConfig cfg = PezGetConfig();

    glGenTextures(1, colorTexture);
    glBindTexture(GL_TEXTURE_2D, *colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cfg.Width, cfg.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    pezCheck(GL_NO_ERROR == glGetError(), "Unable to create color texture.");

    GLuint* distanceTexture = &Globals.DistanceTextures[0];
    for (int i = 0; i < 2; i++) {
        glGenTextures(1, distanceTexture);
        glBindTexture(GL_TEXTURE_2D, *distanceTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, cfg.Width, cfg.Height, 0, GL_RGB, GL_HALF_FLOAT, 0);
        pezCheck(GL_NO_ERROR == glGetError(), "Unable to create distance texture.");
        ++distanceTexture;
    }
    distanceTexture = &Globals.DistanceTextures[0];

    Globals.ColorAttachment         = GL_COLOR_ATTACHMENT0; 
    Globals.DistanceAttachments[0]  = GL_COLOR_ATTACHMENT1;
    Globals.DistanceAttachments[1]  = GL_COLOR_ATTACHMENT2;

    GLuint fboHandle;
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, Globals.ColorAttachment,        GL_TEXTURE_2D, *colorTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, Globals.DistanceAttachments[0], GL_TEXTURE_2D, distanceTexture[0], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, Globals.DistanceAttachments[1], GL_TEXTURE_2D, distanceTexture[1], 0);

    GLuint depthBuffer;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, cfg.Width, cfg.Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    pezCheck(GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER), "Invalid FBO.");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return fboHandle;
}

static GLuint CreateQuad(int sourceWidth, int sourceHeight, int destWidth, int destHeight)
{
    // Stretch to fit:
    float q[] = {
        -1, -1, 0, 1,
        +1, -1, 1, 1,
        -1, +1, 0, 0,
        +1, +1, 1, 0 };
        
    if (sourceHeight < 0) {
        sourceHeight = -sourceHeight;
        q[3] = 1-q[3];
        q[7] = 1-q[7];
        q[11] = 1-q[11];
        q[15] = 1-q[15];
    }

    float sourceRatio = (float) sourceWidth / sourceHeight;
    float destRatio = (float) destWidth  / destHeight;
    
    // Horizontal fit:
    if (sourceRatio > destRatio) {
        q[1] = q[5] = -destRatio / sourceRatio;
        q[9] = q[13] = destRatio / sourceRatio;

    // Vertical fit:    
    } else {
        q[0] = q[8] = -sourceRatio / destRatio;
        q[4] = q[12] = sourceRatio / destRatio;
    }

    GLuint vbo, vao;
    glUseProgram(Globals.QuadProgram);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(q), q, GL_STATIC_DRAW);
    glVertexAttribPointer(a("Position"), 2, GL_FLOAT, GL_FALSE, 16, 0);
    glVertexAttribPointer(a("TexCoord"), 2, GL_FLOAT, GL_FALSE, 16, offset(8));
    glEnableVertexAttribArray(a("Position"));
    glEnableVertexAttribArray(a("TexCoord"));
    return vao;
}

static Vector3 EvaluateTrefoil(float s, float t)
{
    const float a = 0.5f; const float b = 0.3f;
    const float c = 0.5f; const float d = 0.1f;
    const float u = (1 - s) * 2 * TwoPi;
    const float v = t * TwoPi;
    const float r = a + b * cos(1.5f * u);
    const float x = r * cos(u);
    const float y = r * sin(u);
    const float z = c * sin(1.5f * u);

    Vector3 dv;
    dv.x = -1.5f * b * sin(1.5f * u) * cos(u) - (a + b * cos(1.5f * u)) * sin(u);
    dv.y = -1.5f * b * sin(1.5f * u) * sin(u) + (a + b * cos(1.5f * u)) * cos(u);
    dv.z = 1.5f * c * cos(1.5f * u);

    Vector3 q = V3Normalize(dv);
    Vector3 qvn = V3Normalize(V3MakeFromElems(q.y, -q.x, 0));
    Vector3 ww = V3Cross(q, qvn);
        
    Vector3 range;
    range.x = x + d * (qvn.x * cos(v) + ww.x * sin(v));
    range.y = y + d * (qvn.y * cos(v) + ww.y * sin(v));
    range.z = z + d * ww.z * sin(v);
    return range;
}

static MeshPod CreateTrefoil()
{
    const int Slices = 128;
    const int Stacks = 32;
    const int VertexCount = Slices * Stacks;
    const int IndexCount = VertexCount * 6;

    MeshPod mesh;
    glGenVertexArrays(1, &mesh.Vao);
    glBindVertexArray(mesh.Vao);

    // Create a buffer with interleaved positions and normals
    if (true) {
        Vertex verts[VertexCount];
        Vertex* pVert = &verts[0];
        float ds = 1.0f / Slices;
        float dt = 1.0f / Stacks;

        // The upper bounds in these loops are tweaked to reduce the
        // chance of precision error causing an incorrect # of iterations.
        for (float s = 0; s < 1 - ds / 2; s += ds) {
            for (float t = 0; t < 1 - dt / 2; t += dt) {
                const float E = 0.01f;
                Vector3 p = EvaluateTrefoil(s, t);
                Vector3 u = V3Sub(EvaluateTrefoil(s + E, t), p);
                Vector3 v = V3Sub(EvaluateTrefoil(s, t + E), p);
                Vector3 n = V3Normalize(V3Cross(u, v));
                pVert->Position = p;
                pVert->Normal = n;
                ++pVert;
            }
        }

        pezCheck(pVert - &verts[0] == VertexCount, "Tessellation error.");

        GLuint vbo;
        GLsizeiptr size = sizeof(verts);
        const GLvoid* data = &verts[0].Position.x;
        GLenum usage = GL_STATIC_DRAW;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    // Create a buffer of 16-bit indices
    if (true) {
        GLushort inds[IndexCount];
        GLushort* pIndex = &inds[0];
        GLushort n = 0;
        for (GLushort i = 0; i < Slices; i++) {
            for (GLushort j = 0; j < Stacks; j++) {
                *pIndex++ = (n + j + Stacks) % VertexCount;
                *pIndex++ = n + (j + 1) % Stacks;
                *pIndex++ = n + j;
                
                *pIndex++ = (n + (j + 1) % Stacks + Stacks) % VertexCount;
                *pIndex++ = (n + (j + 1) % Stacks) % VertexCount;
                *pIndex++ = (n + j + Stacks) % VertexCount;
            }
            n += Stacks;
        }

        pezCheck(n == VertexCount, "Tessellation error.");
        pezCheck(pIndex - &inds[0] == IndexCount, "Tessellation error.");

        GLuint handle;
        GLsizeiptr size = sizeof(inds);
        const GLvoid* data = &inds[0];
        GLenum usage = GL_STATIC_DRAW;
        glGenBuffers(1, &handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    }

    mesh.VertexCount = VertexCount;
    mesh.IndexCount = IndexCount;

    glVertexAttribPointer(a("Position"), 3, GL_FLOAT, GL_FALSE, 24, 0);
    glVertexAttribPointer(a("Normal"), 3, GL_FLOAT, GL_FALSE, 24, offset(12));
    glEnableVertexAttribArray(a("Position"));
    glEnableVertexAttribArray(a("Normal"));

    return mesh;
}

static void SwapPingPong()
{
    GLenum t0 = Globals.DistanceAttachments[1];
    Globals.DistanceAttachments[1] = Globals.DistanceAttachments[0];
    Globals.DistanceAttachments[0] = t0;
    GLuint t1 = Globals.DistanceTextures[1];
    Globals.DistanceTextures[1] = Globals.DistanceTextures[0];
    Globals.DistanceTextures[0] = t1;
}

// Wraps glDrawBuffers so that unused slots are easily zeroed out.
// Takes pairs: fragment shader out variable + FBO attachment
// For example: "MyFragColor" + GL_COLOR_ATTACHMENT0
// Since this queries for a fragment shader location, a chosen shader
// must be bound when this is called.
static void DrawBuffers(const char* fsOut0, GLenum attachment0,
                        const char* fsOut1, GLenum attachment1)
{
    GLenum slots[] = {GL_NONE, GL_NONE};
    int numSlots = sizeof(slots) / sizeof(slots[0]);

    int slot0 = f(fsOut0);
    pezCheck(slot0 >= 0 && slot0 < numSlots, "Bad juju: %s\n", fsOut0);
    slots[slot0] = attachment0;

    if (fsOut1) {
        int slot1 = f(fsOut1);
        pezCheck(slot1 >= 0 && slot1 < numSlots, "Bad juju: %s\n", fsOut1);
        slots[slot1] = attachment1;
    }

    glDrawBuffers(numSlots, &slots[0]);
}
