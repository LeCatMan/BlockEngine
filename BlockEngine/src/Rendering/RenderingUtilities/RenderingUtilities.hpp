#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../../Debugger/Debugger.hpp"
#include "../../Inputs/Inputs.hpp"
#include "../../Audio/Audio.hpp"
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
BLOCK_TEXTURE_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER

} BlockTextureFlags;






extern GLFWwindow* Bwindow;
extern const char *TestFragmentShaderSource;
extern const char *TestVertexShaderSource;
class Shape2D;

// square
extern const float SquarePerVertexColor[24];
extern const float SquarePosColorUV[32];
extern const float SquareVertices[12];
extern const unsigned int SquareIndices[6];

// Triangle
extern const float TrianglePerVertexColor[18];
extern const float TrianglePosColorUV[24];
extern const float TriangleVertices[9];
extern const unsigned int TriangleIndices[3];

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color(float r, float g, float b, float a)
    {
        this->r = r / 255.0f;
        this->g = g / 255.0f;
        this->b = b / 255.0f;
        this->a = a / 255.0f;
    }
};


class Texture
{
private:
    unsigned int texture;
    char VertexShader[256];
    char FragmentShader[256];
    unsigned int Texture2DVAO;
    unsigned int Texture2DVBO;
    unsigned int Texture2DEBO;
    unsigned int Texture2DShader;
    size_t SizeOfMeshIndices;

public:
    void LoadTexture(const char *ImagePath, GLint MinifyFilter, GLint MagnifyingFilter);
    // plz don't use this its just some bullshit i need
    void drawtexture2D(size_t ShapeIndicesSize);

    void DrawTexture2D()
    {
        drawtexture2D(SizeOfMeshIndices);
    }
    void LoadTextureMesh(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor);
    void UnloadTexture();
    ~Texture();
};

// ########################
// #          2D          #
// ########################


/**
 * Shader2D
 * --------
 * Handles shader creation and management for 2D rendering.
 *
 * Example:
 *     Shader2D MyShader("vertex.vert", "fragment.frag");
 */
class Shader2D
{
private:
    char *vertexshadersource;
    char *fragmentshadersource;
    unsigned int VertexShader;
    unsigned int FragmentShader;
public:

    void CreateShader2D(char *VertexShaderSourcePath, char *FragmentShaderSourcePath);

    void CreateEmbeddedShader2D(char *VertexShaderSource, char *FragmentShaderSource);

    Shader2D() = default;

    ~Shader2D();
    friend Shape2D;
    friend Texture;

    Shader2D(const Shader2D&) = delete;

    Shader2D& operator=(const Shader2D&) = delete;

    Shader2D(Shader2D&&) = delete;

    Shader2D& operator=(Shader2D&&) = delete;

};


/**
 * Shape2D
 * -------
 * Base class for common 2D shapes and rendering.
 *
 * Used by objects such as Triangle and Square.
 */
class Shape2D
{
protected:
    char VertexShader[256];
    char FragmentShader[256];
    unsigned int Shape2DVAO;
    unsigned int Shape2DVBO;
    unsigned int Shape2DEBO;
    unsigned int Shape2DShader;
public:

    Shape2D() = default;

    void LoadShape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor);

    void LoadEmbeddedShape2D(Color color, const char *VertexShader, const char *FragmentShader, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor);

    void DrawShape2D(size_t ShapeIndicesSize);

    void UnloadShape2D();

    ~Shape2D();

    Shape2D(const Shape2D&) = delete;

    Shape2D& operator=(const Shape2D&) = delete;

    Shape2D(Shape2D&&) = delete;

    Shape2D& operator=(Shape2D&&) = delete;
};


// ========================
// |        Shapes        |
// ========================


/**
 * Triangle
 * --------
 * Creates a 2D triangle with the specified color.
 *
 * Example:
 *     Triangle MyTriangle(Color(180, 180, 180));
 */
class Triangle : public Shape2D
{
public:
    Triangle(Color color)
    {
        LoadShape2D
        (
        color,
        "src/Assets/BlockEngine/Shaders/BasicPerVertexVertexShader.vert",
        "src/Assets/BlockEngine/Shaders/BasicPerVertexFragmentShader.frag",
        TrianglePerVertexColor,
        sizeof(TrianglePerVertexColor),
        TriangleIndices,
        sizeof(TriangleIndices),
        true
        );

        rendering("Creating Triangle Resources");
    }

    ~Triangle();

    void DrawTriangle()
    {
        DrawShape2D(sizeof(TriangleIndices) / sizeof(TriangleIndices[0]));
    }
};


/**
 * Square
 * ------
 * Creates a 2D square with the specified color.
 *
 * Example:
 *     Square MySquare(Color(155, 155, 180));
 */
class Square : public Shape2D
{
public:
    Square(Color color)
    {
        LoadShape2D(
        color,
        "src/Assets/BlockEngine/Shaders/BasicVertexShader.vert",
        "src/Assets/BlockEngine/Shaders/BasicFragmentShader.frag",
        SquareVertices,
        sizeof(SquareVertices),
        SquareIndices,
        sizeof(SquareIndices),
        false
        );
        rendering("Creating Square Resources");
    }

    void DrawSquare()
    {
        DrawShape2D((sizeof(SquareIndices) / sizeof(SquareIndices[0])));
    };

    ~Square();
};


// ########################
// #          3D          #
// ########################


// Common 3D objects
class Shape3D
{
protected:
    unsigned int Shape3DVAO;
    unsigned int Shape3DVBO;
    unsigned int Shape3DEBO;
    unsigned int Shape3DShader;
public:
    //Shape3D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize);
    //~Shape3D();
    //void DrawShape3D(size_t ShapeIndicesSize);
};


BlockResult InitializeWindow(int WindowWidth,int WindowHeight,const char *WindowTitle, bool VSync);
void UpdateWindow();
BlockResult WindowShouldClose();
BlockResult CloseWindow();
BlockResult BackGroundColor(Color color);
BlockResult RenderingShutdown();