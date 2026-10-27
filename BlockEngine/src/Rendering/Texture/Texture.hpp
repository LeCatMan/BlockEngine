#pragma once

// glad + glfw
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

/* Texture flags. */
typedef enum BlockTextureFlags
{
// The default behavior for textures. Repeats the texture image.
BLOCK_TEXTURE_REPEAT = GL_REPEAT,

// Same as GL_REPEAT but mirrors the image with each repeat.
BLOCK_TEXTURE_REPEAT_MIRRORED = GL_MIRRORED_REPEAT,

// Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
BLOCK_TEXTURE_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,

//Coordinates outside the range are now given a user-specified border color.
BLOCK_TEXTURE_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,

BLOCK_TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,

BLOCK_TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,

BLOCK_NEAREST = GL_NEAREST,

BLOCK_LINEAR = GL_LINEAR

} BlockTextureFlags;


class Texture2D
{
private:
    unsigned int texture = 0;
    unsigned int Texture2DVAO = 0;
    unsigned int Texture2DVBO = 0;
    unsigned int Texture2DEBO = 0;
    unsigned int Texture2DShader = 0;
    size_t SizeOfMeshIndices = 0;
    bool IsLoaded = false;
    bool IsMeshLoaded = false;

public:

    void LoadTexture2D(const char *ImagePath, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA);
    void LoadEmbeddedTexture2D(const char *ImageData, size_t ImageSize, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA);
    
    
    void LoadTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor);
    void LoadEmbeddedTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor);
    

    // plz don't use this its just some bullshit i need
    void drawtexture2D(size_t ShapeIndicesSize);

    void DrawTexture2D()
    {
        drawtexture2D(SizeOfMeshIndices);
    }
    

    void UnloadTexture2D(int Slot);
    void UnloadTextureMesh2D();
    ~Texture2D();

    Texture2D() = default;
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&&) = delete;
    Texture2D& operator=(Texture2D&&) = delete;
};


/*
#define GL_REPEAT 0x2901
#define GL_MIRRORED_REPEAT 0x8370
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
*/

