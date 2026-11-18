#pragma once

#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"
#include "../../Debugger/Utilities/BlockResult.hpp"
#include "../Color/Color.hpp"

using Blockwindow = GLFWwindow;

class Shader2D;

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

struct Texture2DTarget
{
    Blockwindow *Window = nullptr;
    unsigned int Texture2DVAO = 0, Texture2DVBO = 0, Texture2DEBO = 0, Texture2DShader = 0;
};


class Texture2D
{
private:
    unsigned int Texture = 0;
    size_t SizeOfMeshIndices = 0;
    bool IsMeshLoaded = false;
    bool IsLoaded = false;
    std::vector<Texture2DTarget> Windows;
    int count = 0;
public:

    BlockResult LoadTexture2D(const char *ImagePath, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, bool RGBA);
    BlockResult LoadEmbeddedTexture2D(const char *ImageData, size_t ImageSize, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, bool RGBA);
    
    
    BlockResult LoadTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor, BlockTextureFlags TextureBorder, Color TextureBorderColor, Color color, Blockwindow **Window, int WindowCount);
    BlockResult LoadEmbeddedTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor, BlockTextureFlags TextureBorder, Color TextureBorderColor, Color color, Blockwindow **Window, int WindowCount);

    void Draw(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale);

    BlockResult UnloadTexture2D();
    BlockResult UnloadTextureMesh2D();
    ~Texture2D();

    Texture2D() = default;
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&&) = delete;
    Texture2D& operator=(Texture2D&&) = delete;

    friend Shader2D;
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

