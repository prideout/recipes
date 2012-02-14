// Voronoi Picking OpenGL Demo by Philip Rideout
// Licensed under the Creative Commons Attribution 3.0 Unported License. 
// http://creativecommons.org/licenses/by/3.0/

#include <stdlib.h>
#include "pez.h"
#include "vmath.h"

struct {
    int IndexCount;
    int VertexCount;
    float Theta;
    Matrix4 Projection;
    Matrix4 OrthoMatrix;
    Matrix4 Modelview;
    Matrix4 ViewMatrix;
    Matrix4 ModelMatrix;
    Matrix3 NormalMatrix;
    GLfloat PackedNormalMatrix[9];
    Vector3 Mouse;
    GLuint LitProgram;
    GLuint QuadProgram;
    GLuint SpriteProgram;
    GLuint QuadVao;
    GLuint TorusVao;
    GLuint SinglePointVao;
    GLuint OffscreenFbo, ColorTexture, IdTexture;
} Globals;

static GLuint LoadProgram(const char* vsKey, const char* gsKey, const char* fsKey);
static GLuint CurrentProgram();
static GLuint CreateSinglePoint();
static void ModifySinglePoint(GLuint vao, Vector3 v);
static GLuint CreateTorus(float major, float minor, int slices, int stacks);
static GLuint CreateRenderTarget(GLuint* colorTexture, GLuint* idTexture);
static GLuint CreateQuad(int sourceWidth, int sourceHeight, int destWidth, int destHeight);

#define u(x) glGetUniformLocation(CurrentProgram(), x)
#define a(x) glGetAttribLocation(CurrentProgram(), x)
#define offset(x) ((const GLvoid*)x)

PezConfig PezGetConfig()
{
    PezConfig config;
    config.Title = __FILE__;
    config.Width = 853;
    config.Height = 480;
    config.Multisampling = 1;
    config.VerticalSync = 1;
    return config;
}

void PezInitialize()
{
    const float MajorRadius = 8.0f, MinorRadius = 2.0f;
    const int Slices = 40, Stacks = 10;
    const float ViewHeight = 5.0f;
    const float ViewNear = 65, ViewFar = 90;
    const PezConfig cfg = PezGetConfig();

    // Compile shaders
    Globals.QuadProgram = LoadProgram("Quad.VS", 0, "Quad.FS");
    Globals.SpriteProgram = LoadProgram("VS", "Sprite.GS", "Sprite.FS");
    Globals.LitProgram = LoadProgram("VS", "Lit.GS", "Lit.FS");

    // Set up viewport
    const float w = ViewHeight * cfg.Width / cfg.Height;
    Globals.Projection = M4MakeFrustum(-w, w,
                                       -ViewHeight, ViewHeight,
                                       ViewNear, ViewFar);
    Globals.OrthoMatrix = M4MakeOrthographic(0, cfg.Width, cfg.Height, 0, 0, 1);

    // Create geometry
    Globals.SinglePointVao = CreateSinglePoint();
    Globals.QuadVao = CreateQuad(cfg.Width, cfg.Height, cfg.Width, cfg.Height);
    Globals.TorusVao = CreateTorus(MajorRadius, MinorRadius, Slices, Stacks);
    Globals.OffscreenFbo = CreateRenderTarget(&Globals.ColorTexture, &Globals.IdTexture);

    // Misc Initialization
    Globals.Theta = 0;
    Globals.Mouse.z = -1;
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
}

void PezUpdate(float seconds)
{
    const float RadiansPerSecond = 0.5f;
    Globals.Theta += seconds * RadiansPerSecond;
    
    // Create the model-view matrix:
    Globals.ModelMatrix = M4MakeRotationX(Globals.Theta);
    Point3 eye = P3MakeFromElems(0, -75, 25);
    Point3 target = P3MakeFromElems(0, 0, 0);
    Vector3 up = V3MakeFromElems(0, 1, 0);
    Globals.ViewMatrix = M4MakeLookAt(eye, target, up);
    Globals.Modelview = M4Mul(Globals.ViewMatrix, Globals.ModelMatrix);
    Globals.NormalMatrix = M4GetUpper3x3(Globals.Modelview);
    for (int i = 0; i < 9; ++i)
        Globals.PackedNormalMatrix[i] = M3GetElem(Globals.NormalMatrix, i/3, i%3);
}

void PezRender()
{
    float* pModel = (float*) &Globals.ModelMatrix;
    float* pView = (float*) &Globals.ViewMatrix;
    float* pModelview = (float*) &Globals.Modelview;
    float* pProjection = (float*) &Globals.Projection;
    float* pNormalMatrix = &Globals.PackedNormalMatrix[0];

    glUseProgram(Globals.LitProgram);
    glBindVertexArray(Globals.TorusVao);
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pView);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pModel);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pModelview);
    glUniformMatrix4fv(u("Projection"), 1, 0, pProjection);
    glUniformMatrix3fv(u("NormalMatrix"), 1, 0, pNormalMatrix);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, Globals.IndexCount, GL_UNSIGNED_SHORT, 0);

    const float w = PezGetConfig().Width;
    const float h = PezGetConfig().Height;
    const float s = 64;

    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(Globals.SpriteProgram);
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pView);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pModel);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pModelview);
    glUniformMatrix4fv(u("Projection"), 1, 0, pProjection);
    glUniformMatrix3fv(u("NormalMatrix"), 1, 0, pNormalMatrix);
    glUniform1i(u("Nailboard"), GL_TRUE);
    glUniform2f(u("SpriteSize"), s, s);
    glUniform2f(u("HalfViewport"), w / 2.0f, h / 2.0f);
    glUniform2f(u("InverseViewport"), 1.0f / w, 1.0f / h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_POINTS, 0, Globals.VertexCount);
    glDisable(GL_BLEND);

    if (Globals.Mouse.z < 0) {
        return;
    }

    glUseProgram(Globals.SpriteProgram);
    float x = Globals.Mouse.x;
    float y = Globals.Mouse.y;
    float z = 0;
    Vector3 p = {x, y, z};
    ModifySinglePoint(Globals.SinglePointVao, p);

    Matrix4 i = M4MakeIdentity();
    float* pIdentity = (float*) &i;
    float* pOrtho = (float*) &Globals.OrthoMatrix;

    glBindVertexArray(Globals.SinglePointVao);
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pIdentity);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pIdentity);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pIdentity);
    glUniformMatrix4fv(u("Projection"), 1, 0, pOrtho);
    glUniform1i(u("Nailboard"), GL_FALSE);
    glUniform2f(u("SpriteSize"), 32, 32);
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

static GLuint CreateSinglePoint()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Vector3 v = V3MakeFromScalar(0);
    GLsizeiptr size = sizeof(v);

    GLuint handle;
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, size, &v.x, GL_STATIC_DRAW);
    glEnableVertexAttribArray(a("Position"));
    glVertexAttribPointer(a("Position"), 3, GL_FLOAT, GL_FALSE,
                          size, 0);

    return vao;
}

static void ModifySinglePoint(GLuint vao, Vector3 v)
{
    glBindVertexArray(vao);

    GLuint handle;
    glGetVertexAttribiv(a("Position"), GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, (GLint*) &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);

    GLsizeiptr size = sizeof(v);
    glBufferData(GL_ARRAY_BUFFER, size, &v.x, GL_STATIC_DRAW);
}

static GLuint CreateTorus(float major, float minor, int slices, int stacks)
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Globals.VertexCount = slices * stacks;
    int vertexStride = sizeof(float) * 3;
    GLsizeiptr size = Globals.VertexCount * vertexStride;
    GLfloat* positions = (GLfloat*) malloc(size);

    GLfloat* position = positions;
    for (int slice = 0; slice < slices; slice++) {
        float theta = slice * 2.0f * Pi / slices;
        for (int stack = 0; stack < stacks; stack++) {
            float phi = stack * 2.0f * Pi / stacks;
            float beta = major + minor * cos(phi);
            *position++ = cos(theta) * beta;
            *position++ = sin(theta) * beta;
            *position++ = sin(phi) * minor;
        }
    }

    GLuint handle;
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, size, positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(a("Position"));
    glVertexAttribPointer(a("Position"), 3, GL_FLOAT, GL_FALSE,
                          vertexStride, 0);

    free(positions);

    Globals.IndexCount = slices * stacks * 6;
    size = Globals.IndexCount * sizeof(GLushort);
    GLushort* indices = (GLushort*) malloc(size);
    GLushort* index = indices;
    int v = 0;
    for (int i = 0; i < slices - 1; i++) {
        for (int j = 0; j < stacks; j++) {
            int next = (j + 1) % stacks;
            *index++ = v+next+stacks; *index++ = v+next; *index++ = v+j;
            *index++ = v+j; *index++ = v+j+stacks; *index++ = v+next+stacks;
        }
        v += stacks;
    }
    for (int j = 0; j < stacks; j++) {
        int next = (j + 1) % stacks;
        *index++ = next; *index++ = v+next; *index++ = v+j;
        *index++ = v+j; *index++ = j; *index++ = next;
    }

    glGenBuffers(1, &handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    free(indices);
    return vao;
}

static GLuint CreateRenderTarget(GLuint* colorTexture, GLuint* idTexture)
{
    PezConfig cfg = PezGetConfig();

    glGenTextures(1, colorTexture);
    glBindTexture(GL_TEXTURE_2D, *colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cfg.Width, cfg.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    pezCheck(GL_NO_ERROR == glGetError(), "Unable to create color texture.");

    glGenTextures(1, idTexture);
    glBindTexture(GL_TEXTURE_2D, *idTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, cfg.Width, cfg.Height, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, 0);
    pezCheck(GL_NO_ERROR == glGetError(), "Unable to create id texture.");

    GLuint fboHandle;
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *colorTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, *idTexture, 0);

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
