// Lava OpenGL Demo by Philip Rideout
// Licensed under the Creative Commons Attribution 3.0 Unported License. 
// http://creativecommons.org/licenses/by/3.0/

#include <stdlib.h>
#include <png.h>
#include "pez.h"
#include "vmath.h"

struct SceneParameters {
    int IndexCount;
    float Theta;
    Matrix4 Projection;
    Matrix4 Modelview;
    Matrix4 ViewMatrix;
    Matrix4 ModelMatrix;
    Matrix3 NormalMatrix;
    Vector4 ClipPlane;
    GLfloat PackedNormalMatrix[9];
    GLuint LavaTexture;
    GLuint CloudTexture;
} Scene;

static GLuint LoadProgram(const char* vsKey, const char* gsKey, const char* fsKey);
static GLuint CurrentProgram();
static GLuint LoadTexture(const char* filename);

#define u(x) glGetUniformLocation(CurrentProgram(), x)
#define a(x) glGetAttribLocation(CurrentProgram(), x)
#define offset(x) ((const GLvoid*)x)
#define OpenGLError GL_NO_ERROR == glGetError(),                        \
        "%s:%d - OpenGL Error - %s", __FILE__, __LINE__, __FUNCTION__   \

PezConfig PezGetConfig()
{
    PezConfig config;
    config.Title = __FILE__;
    config.Width = 853;
    config.Height = 480;
    config.Multisampling = true;
    config.VerticalSync = false;
    return config;
}

static void CreateTorus(float major, float minor, int slices, int stacks)
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    int vertexCount = slices * stacks * 3;
    int vertexStride = sizeof(float) * 3;
    GLsizeiptr size = vertexCount * vertexStride;
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

    Scene.IndexCount = slices * stacks * 6;
    size = Scene.IndexCount * sizeof(GLushort);
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
}

void PezInitialize()
{
    LoadProgram("VS", "GS", "FS");

    PezConfig cfg = PezGetConfig();
    const float h = 5.0f;
    const float w = h * cfg.Width / cfg.Height;
    Scene.Projection = M4MakeFrustum(-w, w,   // left & right planes
                                     -h, h,   // bottom & top planes
                                     65, 90); // near & far planes

    const float MajorRadius = 8.0f, MinorRadius = 2.0f;
    const int Slices = 40, Stacks = 10;
    CreateTorus(MajorRadius, MinorRadius, Slices, Stacks);
    Scene.Theta = 0;
    Scene.ClipPlane = (Vector4){0, 1, 0, 7};

    // Load textures
    Scene.CloudTexture = LoadTexture("cloud.png");
    Scene.LavaTexture = LoadTexture("lavatile.png");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_DISTANCE0);
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
}

void PezUpdate(float seconds)
{
    const float RadiansPerSecond = 0.5f;
    Scene.Theta += seconds * RadiansPerSecond;
    
    // Create the model-view matrix:
    Scene.ModelMatrix = M4MakeRotationZ(Scene.Theta);
    Point3 eye = {0, -75, 25};
    Point3 target = {0, 0, 0};
    Vector3 up = {0, 1, 0};
    Scene.ViewMatrix = M4MakeLookAt(eye, target, up);
    Scene.Modelview = M4Mul(Scene.ViewMatrix, Scene.ModelMatrix);
    Scene.NormalMatrix = M4GetUpper3x3(Scene.Modelview);
    for (int i = 0; i < 9; ++i)
        Scene.PackedNormalMatrix[i] = M3GetElem(Scene.NormalMatrix, i/3, i%3);
}

void PezRender()
{
    float* pModel = (float*) &Scene.ModelMatrix;
    float* pView = (float*) &Scene.ViewMatrix;
    float* pModelview = (float*) &Scene.Modelview;
    float* pProjection = (float*) &Scene.Projection;
    float* pNormalMatrix = &Scene.PackedNormalMatrix[0];
    glUniformMatrix4fv(u("ViewMatrix"), 1, 0, pView);
    glUniformMatrix4fv(u("ModelMatrix"), 1, 0, pModel);
    glUniformMatrix4fv(u("Modelview"), 1, 0, pModelview);
    glUniformMatrix4fv(u("Projection"), 1, 0, pProjection);
    glUniformMatrix3fv(u("NormalMatrix"), 1, 0, pNormalMatrix);
    glUniform4fv(u("ClipPlane"), 1, &Scene.ClipPlane.x);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, Scene.IndexCount, GL_UNSIGNED_SHORT, 0);
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

    const char* gsSource = pezGetShader(gsKey);
    pezCheck(gsSource != 0, "Can't find gshader: %s\n", gsKey);
    GLuint gsHandle = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gsHandle, 1, &gsSource, 0);
    glCompileShader(gsHandle);
    glGetShaderiv(gsHandle, GL_COMPILE_STATUS, &compileSuccess);
    glGetShaderInfoLog(gsHandle, sizeof(spew), 0, spew);
    pezCheck(compileSuccess, "Can't compile gshader:\n%s", spew);
    glAttachShader(programHandle, gsHandle);

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

    //    pezCheck(setjmp(png_jmpbuf(png_ptr)), "PNG error line %d", __LINE__);

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int bit_depth;
    int color_type;
    unsigned long width;
    unsigned long height;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, 
                 &color_type, NULL, NULL, NULL);

    pezPrintString("%d x %d bpp=%d ct=%d\n", width, height, bit_depth, color_type); //..

#if 0
    unsigned char* buffer;
    unsigned char* image;
    size_t buffersize, imagesize;
    LodePNG_Decoder decoder;
    LodePNG_loadFile(&buffer, &buffersize, filename);
    LodePNG_Decoder_init(&decoder);
    decoder.infoRaw.color.colorType = 0;
    decoder.infoRaw.color.bitDepth = 8;
    LodePNG_Decoder_decode(&decoder, &image, &imagesize, buffer, buffersize);
    pezCheck(!decoder.error, "error %u: %s\n", decoder.error, LodePNG_error_text(decoder.error));
    int bpp = LodePNG_InfoColor_getBpp(&decoder.infoPng.color);
    int bitDepth = decoder.infoPng.color.bitDepth;
    int colorChannels = LodePNG_InfoColor_getChannels(&decoder.infoPng.color);
    pezCheck(bpp == 8 && bitDepth == 8 && colorChannels == 1);
    int w = decoder.infoPng.width;
    int h = decoder.infoPng.height;
    pezPrintString("Loaded %s (%d x %d) bufferSize = %d, imageSize = %d\n", filename, w, h, buffersize, imagesize);

    GLuint handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, image);

    free(buffer);
    free(image);
    LodePNG_Decoder_cleanup(&decoder);
#endif

    GLuint handle = 0;
    pezCheck(OpenGLError);
    return handle;
}

