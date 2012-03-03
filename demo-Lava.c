// Lava OpenGL Demo by Philip Rideout
// Licensed under the Creative Commons Attribution 3.0 Unported License. 
// http://creativecommons.org/licenses/by/3.0/

#include <stdlib.h>
#include <png.h>
#include "pez.h"
#include "vmath.h"

typedef struct {
    GLuint ColorTexture;
    GLuint DepthBuffer;
    GLuint Fbo;
    int Width;
    int Height;
} RenderTarget;

struct GlobalsParameters {
    int IndexCount;
    float Theta;
    float Time;
    Matrix4 Projection;
    Matrix4 Modelview;
    Matrix4 ViewMatrix;
    Matrix4 ModelMatrix;
    Matrix3 NormalMatrix;
    GLuint LavaTexture;
    GLuint CloudTexture;
    GLuint QuadProgram;
    GLuint LavaProgram;
    GLuint BlurProgram;
    GLuint TorusVao;
    GLuint QuadVao;
    RenderTarget Scene;
    RenderTarget Small[2];
} Globals;

static GLuint LoadProgram(const char* vsKey, const char* gsKey, const char* fsKey);
static GLuint CurrentProgram();
static GLuint LoadTexture(const char* filename);
static GLuint CreateQuad(int sourceWidth, int sourceHeight, int destWidth, int destHeight);
static GLuint CreateTorus(float major, float minor, int slices, int stacks);
static RenderTarget CreateRenderTarget(int width, int height, bool depth);

#define u(x) glGetUniformLocation(CurrentProgram(), x)
#define a(x) glGetAttribLocation(CurrentProgram(), x)
#define offset(x) ((const GLvoid*)x)
#define OpenGLError GL_NO_ERROR == glGetError(),                        \
        "%s:%d - OpenGL Error - %s", __FILE__, __LINE__, __FUNCTION__   \

PezConfig PezGetConfig()
{
    PezConfig config;
    config.Title = __FILE__;
    config.Width = 1280;
    config.Height = 800;
    config.Multisampling = true;
    config.VerticalSync = true;
    return config;
}

static GLuint CreateTorus(float major, float minor, int slices, int stacks)
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    int vertexCount = slices * stacks * 3;
    int vertexStride = sizeof(float) * 5;
    GLsizeiptr size = vertexCount * vertexStride;
    GLfloat* verts = (GLfloat*) malloc(size);

    GLfloat* vert = verts;
    for (int slice = 0; slice < slices; slice++) {
        float theta = slice * 2.0f * Pi / (slices - 1);
        for (int stack = 0; stack < stacks; stack++) {
            float phi = stack * 2.0f * Pi / (stacks - 1);
            float beta = major + minor * cos(phi);
            *vert++ = cos(theta) * beta;
            *vert++ = sin(theta) * beta;
            *vert++ = sin(phi) * minor;
            *vert++ = (float) slice / (slices-1);
            *vert++ = (float) stack / (stacks-1);
        }
    }

    GLuint handle;
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(a("Position"));
    glVertexAttribPointer(a("Position"), 3, GL_FLOAT, GL_FALSE, vertexStride, 0);
    if (a("TexCoord") != -1) {
        glEnableVertexAttribArray(a("TexCoord"));
        glVertexAttribPointer(a("TexCoord"), 2, GL_FLOAT, GL_FALSE, vertexStride, offset(12));
    }

    free(verts);

    Globals.IndexCount = (slices-1) * (stacks-1) * 6;
    size = Globals.IndexCount * sizeof(GLushort);
    GLushort* indices = (GLushort*) malloc(size);
    GLushort* index = indices;
    int v = 0;
    for (int i = 0; i < slices-1; i++) {
        for (int j = 0; j < stacks-1; j++) {
            int next = (j + 1) % stacks;
            *index++ = (v+next+stacks) % vertexCount;
            *index++ = (v+next) % vertexCount;
            *index++ = (v+j) % vertexCount;
            *index++ = (v+j) % vertexCount;
            *index++ = (v+j+stacks) % vertexCount;
            *index++ = (v+next+stacks) % vertexCount;
        }
        v += stacks;
    }
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    free(indices);
    return vao;
}

void PezInitialize()
{
    Globals.QuadProgram = LoadProgram("Quad.VS", 0, "Quad.FS");
    Globals.BlurProgram = LoadProgram("Quad.VS", 0, "Blur.FS");
    Globals.LavaProgram = LoadProgram("TheGameMaker.VS", 0, "TheGameMaker.FS");

    PezConfig cfg = PezGetConfig();
    Globals.Scene = CreateRenderTarget(cfg.Width, cfg.Height, true);
    int d = 4;
    Globals.Small[0] = CreateRenderTarget(cfg.Width/d, cfg.Height/d, false);
    Globals.Small[1] = CreateRenderTarget(cfg.Width/d, cfg.Height/d, false);

    float fovy = 170 * TwoPi / 180;
    float aspect = (float) cfg.Width / cfg.Height;
    float zNear = 65, zFar = 90;
    Globals.Projection = M4MakePerspective(fovy, aspect, zNear, zFar);

    const float MajorRadius = 8.0f, MinorRadius = 4.0f;
    const int Slices = 60, Stacks = 30;
    Globals.QuadVao = CreateQuad(1, -1, 1, 1);
    Globals.TorusVao = CreateTorus(MajorRadius, MinorRadius, Slices, Stacks);
    Globals.Theta = 0;

    // Load textures
    Globals.CloudTexture = LoadTexture("cloud.png");
    Globals.LavaTexture = LoadTexture("lavatile.png");

    glClearColor(0, 0, 0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PezUpdate(float seconds)
{
    const float RadiansPerSecond = 0.5f;
    Globals.Theta += seconds * RadiansPerSecond;
    Globals.Time += seconds;
    
    // Create the model-view matrix:
    Globals.ModelMatrix = M4MakeRotationZYX((Vector3){Globals.Theta, Globals.Theta, Globals.Theta});
    Point3 eye = {0, 0, -80};
    Point3 target = {0, 0, 0};
    Vector3 up = {0, 1, 0};
    Globals.ViewMatrix = M4MakeLookAt(eye, target, up);
    Globals.Modelview = M4Mul(Globals.ViewMatrix, Globals.ModelMatrix);
    Globals.NormalMatrix = M4GetUpper3x3(Globals.Modelview);
}

void PezRender()
{
    PezConfig cfg = PezGetConfig();
    float* pModel = (float*) &Globals.ModelMatrix;
    float* pView = (float*) &Globals.ViewMatrix;
    float* pModelview = (float*) &Globals.Modelview;
    float* pProjection = (float*) &Globals.Projection;
    int w = Globals.Small[0].Width;
    int h = Globals.Small[0].Height;
    const float hoffsets[5] = {
        -2.0f / w,
        -1.0f / w,
        0,
        +1.0f / w,
        +2.0f / w,
    };
    const float voffsets[5] = {
        -2.0f / h,
        -1.0f / h,
        0,
        +1.0f / h,
        +2.0f / h,
    };
    const float weights[5] = {
        1.0f / 16.0f,
        4.0f / 16.0f,
        6.0f / 16.0f,
        4.0f / 16.0f,
        1.0f / 16.0f,
    };

    glBindFramebuffer(GL_FRAMEBUFFER, Globals.Scene.Fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glUseProgram(Globals.LavaProgram);
    glBindVertexArray(Globals.TorusVao);
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pView);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pModel);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pModelview);
    glUniformMatrix4fv(u("Projection"), 1, 0, pProjection);
    glUniform1f(u("time"), Globals.Time * 3);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Globals.CloudTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Globals.LavaTexture);
    glDrawElements(GL_TRIANGLES, Globals.IndexCount, GL_UNSIGNED_SHORT, 0);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_DEPTH_TEST);

    // Downsample
    glBindFramebuffer(GL_FRAMEBUFFER, Globals.Small[0].Fbo);
    glViewport(0, 0, w, h);
    glUseProgram(Globals.QuadProgram);
    glBindTexture(GL_TEXTURE_2D, Globals.Scene.ColorTexture);
    glBindVertexArray(Globals.QuadVao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Horizontal Pass
    glBindFramebuffer(GL_FRAMEBUFFER, Globals.Small[1].Fbo);
    glUseProgram(Globals.BlurProgram);
    glUniform2fv(u("Offsets"), 5, hoffsets);
    glUniform1fv(u("Weights"), 5, weights);
    glBindTexture(GL_TEXTURE_2D, Globals.Small[0].ColorTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Vertical Pass
    glBindFramebuffer(GL_FRAMEBUFFER, Globals.Small[0].Fbo);
    glUniform2fv(u("Offsets"), 5, voffsets);
    glBindTexture(GL_TEXTURE_2D, Globals.Small[1].ColorTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Blit full-res unprocessed scene to screen:
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, cfg.Width, cfg.Height);
    glUseProgram(Globals.QuadProgram);
    glUniform1f(u("Alpha"), 1.0);
    glBindTexture(GL_TEXTURE_2D, Globals.Scene.ColorTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Blend over the blurred image:
    glEnable(GL_BLEND);
    glUniform1f(u("Alpha"), 0.5);
    glBindTexture(GL_TEXTURE_2D, Globals.Small[0].ColorTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
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

static GLuint LoadTexture(const char* filename)
{
    unsigned long w, h;
    int color_type, bit_depth, row_stride;
    png_bytep image;

    if (true) {
        FILE *fp = fopen(filename, "rb");
        pezCheck(fp ? 1 : 0, "Can't find %s", filename);
        unsigned char header[8];
        fread(header, 1, 8, fp);
        bool isPng = !png_sig_cmp(header, 0, 8);
        pezCheck(isPng, "%s is not a valid PNG file.", filename);
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        pezCheckPointer(png_ptr, "PNG error line %d", __LINE__);
        png_infop info_ptr = png_create_info_struct(png_ptr);
        pezCheckPointer(info_ptr, "PNG error line %d", __LINE__);
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);
        w = png_get_image_width(png_ptr, info_ptr);
        h = png_get_image_height(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        pezPrintString("%s %dx%d bpp=%d ct=%d\n", filename, w, h, bit_depth, color_type);
        png_read_update_info(png_ptr, info_ptr);
        row_stride = png_get_rowbytes(png_ptr,info_ptr);
        image = (png_bytep) malloc(h * row_stride);
        png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * h);
        png_bytep row = image;
        for (int y = h-1; y >= 0; y--, row += row_stride) {
            row_pointers[y] = row;
        }
        png_read_image(png_ptr, row_pointers);
        free(row_pointers);
        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
    }

    pezCheck(bit_depth == 8, "Bit depth must be 8.");

    GLenum type = 0;
    switch (color_type) {
    case PNG_COLOR_TYPE_RGB:  type = GL_RGB;  break;
    case PNG_COLOR_TYPE_RGBA: type = GL_RGBA; break;
    case PNG_COLOR_TYPE_GRAY: type = GL_RED;  break;
    default: pezFatal("Unknown color type: %d.", color_type);
    }

    GLuint handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, type, w, h, 0, type, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    pezCheck(OpenGLError);

    free(image);
    return handle;
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

static RenderTarget CreateRenderTarget(int width, int height, bool depth)
{
    pezCheck(GL_NO_ERROR == glGetError(), "OpenGL error on line %d",  __LINE__);

    RenderTarget rt;
    rt.Width = width;
    rt.Height = height;

    glGenTextures(1, &rt.ColorTexture);
    glBindTexture(GL_TEXTURE_2D, rt.ColorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    pezCheck(GL_NO_ERROR == glGetError(), "Unable to create color texture.");

    glGenFramebuffers(1, &rt.Fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, rt.Fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rt.ColorTexture, 0);

    if (depth) {
        glGenRenderbuffers(1, &rt.DepthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, rt.DepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rt.DepthBuffer);
    } else {
        rt.DepthBuffer = 0;
    }

    pezCheck(GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER), "Invalid FBO.");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return rt;
}
