// Toon Shading OpenGL Demo by Philip Rideout
// Licensed under the Creative Commons Attribution 3.0 Unported License. 
// http://creativecommons.org/licenses/by/3.0/

#include <stdlib.h>
#include <stdbool.h>
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
    float Theta;
    GLuint LitProgram;
    GLuint SinglePointVao;
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

#define u(x) glGetUniformLocation(CurrentProgram(), x)
#define a(x) glGetAttribLocation(CurrentProgram(), x)
#define offset(x) ((const GLvoid*)x)

PezConfig PezGetConfig()
{
    PezConfig config;
    config.Title = __FILE__;
    config.Width = 853;
    config.Height = 480;
    config.Multisampling = true;
    config.VerticalSync = true;
    return config;
}

void PezInitialize()
{
    const PezConfig cfg = PezGetConfig();

    // Compile shaders
    Globals.LitProgram = LoadProgram("Lit.VS", 0, "Lit.FS");

    // Set up viewport
    float fovy = 16 * TwoPi / 180;
    float aspect = (float) cfg.Width / cfg.Height;
    float zNear = 0.1, zFar = 300;
    Globals.Transforms.Projection = M4MakePerspective(fovy, aspect, zNear, zFar);
    Globals.Transforms.Ortho = M4MakeOrthographic(0, cfg.Width, cfg.Height, 0, 0, 1);

    // Create geometry
    glUseProgram(Globals.LitProgram);
    Globals.TrefoilKnot = CreateTrefoil();

    // Misc Initialization
    Globals.Theta = 0;
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
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
    float* pModel = (float*) &Globals.Transforms.Model;
    float* pView = (float*) &Globals.Transforms.View;
    float* pModelview = (float*) &Globals.Transforms.Modelview;
    float* pProjection = (float*) &Globals.Transforms.Projection;
    float* pNormalMatrix = &Globals.Transforms.PackedNormal[0];
    MeshPod* mesh = &Globals.TrefoilKnot;

    glUseProgram(Globals.LitProgram);
    glBindVertexArray(mesh->Vao);
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pView);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pModel);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pModelview);
    glUniformMatrix4fv(u("Projection"), 1, 0, pProjection);
    glUniformMatrix3fv(u("NormalMatrix"), 1, 0, pNormalMatrix);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, mesh->IndexCount, GL_UNSIGNED_SHORT, 0);
}

void PezHandleMouse(int x, int y, int action)
{
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

static Vector3 EvaluateTrefoil(float s, float t)
{
    const float a = 0.5f;
    const float b = 0.3f;
    const float c = 0.5f;
    const float d = 0.1f;
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
    const int Slices = 256;
    const int Stacks = 32;
    const int VertexCount = Slices * Stacks;
    const int IndexCount = VertexCount * 6;

    MeshPod mesh;
    glGenVertexArrays(1, &mesh.Vao);
    glBindVertexArray(mesh.Vao);

    // Create a buffer with interleaved positions and normals
    if (1) {
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
    if (1) {
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
