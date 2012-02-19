// Deep Opacity OpenGL Demo by Philip Rideout
// Licensed under the Creative Commons Attribution 3.0 Unported License. 
// http://creativecommons.org/licenses/by/3.0/

#include "pez.h"
#include "vmath.h"

static const Point3 EyePosition = {0, 0, 2};
static Point3 LightPosition = {1, 1, 2};
static const float FieldOfView = 0.7f;
static const int GridSize = 96;
static const int ViewSamples = 96 * 2;
static const int LightSamples = 96;

PezConfig PezGetConfig()
{
    PezConfig config;
    config.Title = __FILE__;
    config.Width = 853;
    config.Height = 480;
    config.Multisampling = false;
    config.VerticalSync = false;
    return config;
}

typedef struct VolumeRec {
    GLuint FboHandle;
    GLuint TextureHandle;
    GLsizei Width;
    GLsizei Height;
    GLsizei Depth;
} Volume;

struct VolumesRec {
    Volume Density;
    Volume LightCache;
} Volumes;

struct MatricesRec {
    Matrix4 Projection;
    Matrix4 Modelview;
    Matrix4 ModelviewProjection;
} Matrices;

struct VbosRec {
    GLuint CubeCenter;
    GLuint FullscreenQuad;
} Vbos;

struct ProgramsRec {
    GLuint Raycast;
    GLuint Light;
} Programs;

static GLuint LoadProgram(char* vs, char* gs, char* fs);
static Volume CreateVolume(GLsizei w, GLsizei h, GLsizei d, int numComponents);
static GLuint CurrentProgram();

#define u(x) glGetUniformLocation(CurrentProgram(), x)
#define a(x) glGetAttribLocation(CurrentProgram(), x)

void PezInitialize()
{
    Programs.Raycast = LoadProgram("VS", "GS", "FS");
    Programs.Light = LoadProgram("Fluid.Vertex", "Fluid.PickLayer", "Light.Cache");

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float p[] = {0, 0, 0};
    glGenBuffers(1, &Vbos.CubeCenter);
    glBindBuffer(GL_ARRAY_BUFFER, Vbos.CubeCenter);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p[0], GL_STATIC_DRAW);

    short q[] = { -1, -1, 1, -1, -1, 1, 1, 1 };
    glGenBuffers(1, &Vbos.FullscreenQuad);
    glBindBuffer(GL_ARRAY_BUFFER, Vbos.FullscreenQuad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(q), q, GL_STATIC_DRAW);

    Volumes.Density = CreateVolume(GridSize, GridSize, GridSize, 1);
    Volumes.LightCache = CreateVolume(GridSize, GridSize, GridSize, 1);

    PezPixels pixels = pezLoadPixels("Smoke96.pbo");
    glBindTexture(GL_TEXTURE_3D, Volumes.Density.TextureHandle);
    glTexImage3D(GL_TEXTURE_3D, 0, pixels.InternalFormat,
        pixels.Width, pixels.Height, pixels.Depth,
        0, pixels.Format, pixels.Type, pixels.Frames);
    pezFreePixels(pixels);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnableVertexAttribArray(0);
}

void PezRender()
{
    PezConfig cfg = PezGetConfig();
    Vector3 rayOrigin = V4GetXYZ(M4MulP3(M4Transpose(Matrices.Modelview), EyePosition));
    GLfloat* mvp = &Matrices.ModelviewProjection.col0.x;
    GLfloat* mv = &Matrices.Modelview.col0.x;
    GLfloat* proj = &Matrices.Projection.col0.x;

    // Generate the light cache:
    glDisable(GL_BLEND);
    glBindFramebuffer(GL_FRAMEBUFFER, Volumes.LightCache.FboHandle);
    glViewport(0, 0, Volumes.LightCache.Width, Volumes.LightCache.Height);
    glBindBuffer(GL_ARRAY_BUFFER, Vbos.FullscreenQuad);
    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(short), 0);
    glBindTexture(GL_TEXTURE_3D, Volumes.Density.TextureHandle);
    glUseProgram(Programs.Light);
    glUniform3fv(u("LightPosition"), 1, &LightPosition.x);
    glUniform1f(u("LightStep"), sqrtf(2.0f) / LightSamples);
    glUniform1i(u("LightSamples"), LightSamples);
    glUniform1f(u("InverseSize"), 1.0f / GridSize);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, GridSize);

    // Perform raycasting:
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, cfg.Width, cfg.Height);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBindBuffer(GL_ARRAY_BUFFER, Vbos.CubeCenter);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, Volumes.Density.TextureHandle);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_3D, Volumes.LightCache.TextureHandle);
    glUseProgram(Programs.Raycast);
    glUniformMatrix4fv(u("ModelviewProjection"), 1, 0, mvp);
    glUniformMatrix4fv(u("Modelview"), 1, 0, mv);
    glUniformMatrix4fv(u("ProjectionMatrix"), 1, 0, proj);
    glUniform1i(u("ViewSamples"), ViewSamples);
    glUniform3fv(u("EyePosition"), 1, &EyePosition.x);
    glUniform1i(u("Density"), 0);
    glUniform1i(u("LightCache"), 1);
    glUniform3fv(u("RayOrigin"), 1, &rayOrigin.x);
    glUniform1f(u("FocalLength"), 1.0f / tanf(FieldOfView / 2));
    glUniform2f(u("WindowSize"), (float) cfg.Width, (float) cfg.Height);
    glUniform1f(u("StepSize"), sqrtf(3.0f) / ViewSamples); // should be sqrt(2)
    glDrawArrays(GL_POINTS, 0, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_3D, 0);
    glActiveTexture(GL_TEXTURE0);
}

void PezUpdate(float dt)
{
    static float theta = 0;
    theta += dt / 2.0f;
    
    Vector3 up = {1, 0, 0}; Point3 target = {0, 0, 0};
    Matrix4 view = M4MakeLookAt(EyePosition, target, up);
    Matrix4 spin = M4MakeRotationX(sin(theta / 4) * Pi / 2);
    Matrix4 model = M4Mul(spin, M4MakeRotationY(0.75));
    Matrices.Modelview = M4Mul(view, model);
    
    Point3 p = {1, 1, 2};
    LightPosition = T3MulP3(T3MakeRotationY(2 * theta), p);

    PezConfig cfg = PezGetConfig();
    float aspectRatio = (float) cfg.Width / cfg.Height;
    Matrices.Projection = M4MakePerspective(
        FieldOfView, aspectRatio,
        0.0f, 1.0f);

    Matrices.ModelviewProjection = M4Mul(Matrices.Projection, Matrices.Modelview);
}

void PezHandleMouse(int x, int y, int action)
{
}

static GLuint LoadProgram(char* vsKey, char* gsKey, char* fsKey)
{
    const char* vsSource = pezGetShader(vsKey);
    const char* gsSource = pezGetShader(gsKey);
    const char* fsSource = pezGetShader(fsKey);

    const char* msg = "Can't find %s shader: '%s'.\n";
    pezCheck(vsSource != 0, msg, "vertex", vsKey);
    pezCheck(gsKey == 0 || gsSource != 0, msg, "geometry", gsKey);
    pezCheck(fsKey == 0 || fsSource != 0, msg, "fragment", fsKey);
    
    GLint compileSuccess;
    GLchar compilerSpew[256];
    GLuint programHandle = glCreateProgram();

    GLuint vsHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsHandle, 1, &vsSource, 0);
    glCompileShader(vsHandle);
    glGetShaderiv(vsHandle, GL_COMPILE_STATUS, &compileSuccess);
    glGetShaderInfoLog(vsHandle, sizeof(compilerSpew), 0, compilerSpew);
    pezCheck(compileSuccess, "Can't compile %s:\n%s", vsKey, compilerSpew);
    glAttachShader(programHandle, vsHandle);

    GLuint gsHandle;
    if (gsKey) {
        gsHandle = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gsHandle, 1, &gsSource, 0);
        glCompileShader(gsHandle);
        glGetShaderiv(gsHandle, GL_COMPILE_STATUS, &compileSuccess);
        glGetShaderInfoLog(gsHandle, sizeof(compilerSpew), 0, compilerSpew);
        pezCheck(compileSuccess, "Can't compile %s:\n%s", gsKey, compilerSpew);
        glAttachShader(programHandle, gsHandle);
    }
    
    GLuint fsHandle;
    if (fsKey) {
        fsHandle = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fsHandle, 1, &fsSource, 0);
        glCompileShader(fsHandle);
        glGetShaderiv(fsHandle, GL_COMPILE_STATUS, &compileSuccess);
        glGetShaderInfoLog(fsHandle, sizeof(compilerSpew), 0, compilerSpew);
        pezCheck(compileSuccess, "Can't compile %s:\n%s", fsKey, compilerSpew);
        glAttachShader(programHandle, fsHandle);
    }

    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    glGetProgramInfoLog(programHandle, sizeof(compilerSpew), 0, compilerSpew);

    if (!linkSuccess) {
        pezPrintString("Link error.\n");
        if (vsKey) pezPrintString("Vertex Shader: %s\n", vsKey);
        if (gsKey) pezPrintString("Geometry Shader: %s\n", gsKey);
        if (fsKey) pezPrintString("Fragment Shader: %s\n", fsKey);
        pezPrintString("%s\n", compilerSpew);
    }
    
    return programHandle;
}

static Volume CreateVolume(GLsizei w, GLsizei h, GLsizei d, int numComponents)
{
    GLuint fboHandle;
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

    GLuint textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_3D, textureHandle);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum internalFmt, fmt;
    switch (numComponents) {
        case 1: internalFmt = GL_R16F; fmt = GL_RED; break;
        case 2: internalFmt = GL_RG16F; fmt = GL_RG; break;
        case 3: internalFmt = GL_RGB16F; fmt = GL_RGB; break;
        case 4: internalFmt = GL_RGBA16F; fmt = GL_RGBA; break;
        default: internalFmt = fmt = 0; pezFatal("%d components", numComponents);
    }
    
    GLenum type = GL_HALF_FLOAT;
    glTexImage3D(GL_TEXTURE_3D, 0, internalFmt, w, h, d, 0, fmt, type, 0);
    pezCheck(GL_NO_ERROR == glGetError(), "Unable to create volume texture");

    GLuint colorbuffer;
    glGenRenderbuffers(1, &colorbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureHandle, 0);
    pezCheck(GL_NO_ERROR == glGetError(), "Unable to attach color buffer");

    GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    pezCheck(GL_FRAMEBUFFER_COMPLETE == fboStatus, "Unable to create FBO.");

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Volume volume = { fboHandle, textureHandle, w, h, d };
    return volume;
}

static GLuint CurrentProgram()
{
    GLuint p;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &p);
    return p;
}
