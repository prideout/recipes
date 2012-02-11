#define GLR_MAINLOOP 1
#define GLR_FORWARD_COMPATIBLE_GL 0

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "glew.h"

typedef struct GlrConfigRec
{
    const char* Title;
    int Width;
    int Height;
    int Multisampling;
    int VerticalSync;
} GlrConfig;

#ifdef GLR_MAINLOOP
GlrConfig GetConfig();
void Initialize();
void Render();
void Update(float seconds);

#ifdef GLR_MOUSE_HANDLER
void HandleMouse(int x, int y, int action);
#endif

#ifdef GLR_DROP_HANDLER
void ReceiveDrop(const char* filename);
#endif

#else
void glrSwapBuffers();
#endif

enum {GLR_DOWN, GLR_UP, GLR_MOVE, GLR_DOUBLECLICK};
#define TwoPi (6.28318531f)
#define Pi (3.14159265f)
#define countof(A) (sizeof(A) / sizeof(A[0]))

void glrPrintString(const char* pStr, ...);
void glrFatal(const char* pStr, ...);
void glrCheck(int condition, ...);
int glrIsPressing(char key);
const char* glrResourcePath();
const char* glrOpenFileDialog();
const char* glrGetDesktopFolder();

int glrInit();
int glrShutdown();
int glrAddPath(const char* pathPrefix, const char* pathSuffix);
const char* glrGetShader(const char* effectKey);
const char* glrGetError();
int glrAddDirective(const char* token, const char* directive);


typedef struct GlrAttribRec {
    const GLchar* Name;
    GLint Size;
    GLenum Type;
    GLsizei Stride;
    int FrameCount;
    GLvoid* Frames;
} GlrAttrib;

typedef struct GlrVertsRec {
    int AttribCount;
    int IndexCount;
    int VertexCount;
    GLenum IndexType;
    GLsizeiptr IndexBufferSize;
    GlrAttrib* Attribs;
    GLvoid* Indices;
    void* RawHeader;
} GlrVerts;

typedef struct GlrPixelsRec {
    int FrameCount;
    GLsizei Width;
    GLsizei Height;
    GLsizei Depth;
    GLint MipLevels;
    GLenum Format;
    GLenum InternalFormat;
    GLenum Type;
    GLsizeiptr BytesPerFrame;
    GLvoid* Frames;
    void* RawHeader;
} GlrPixels;

GlrVerts glrLoadVerts(const char* filename);
GlrVerts glrGenQuad(float left, float top, float right, float bottom);
void glrFreeVerts(GlrVerts verts);
void glrSaveVerts(GlrVerts verts, const char* filename);

GlrPixels glrLoadPixels(const char* filename);
void glrFreePixels(GlrPixels pixels);
void glrSavePixels(GlrPixels pixels, const char* filename);
void glrRenderText(GlrPixels pixels, const char* message);
GlrPixels glrGenNoise(GlrPixels desc, float alpha, float beta, int n);
#ifdef __cplusplus
}
#endif
