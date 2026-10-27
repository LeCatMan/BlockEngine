#pragma once
#include "../../Assets/BlockEngine/BasicShapes/BasicShapes.hpp"
#include "../../Debugger/Logger/Logger.hpp"
#include "../Color/Color.hpp"
// glad + glfw
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

// ########################
// #          2D          #
// ########################

class BlockWindow;

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
    char *VertexShader = nullptr;
    char *FragmentShader = nullptr;
    unsigned int Shape2DVAO = 0;
    unsigned int Shape2DVBO = 0;
    unsigned int Shape2DEBO = 0;
    unsigned int Shape2DShader = 0;
    bool IsLoaded = false;
    GLFWwindow *window = nullptr;
public:

    Shape2D() = default;

    void LoadShape2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, BlockWindow *Window, bool PerVertexColor, Color color);

    void LoadEmbeddedShape2D(const char *VertexShaderSource, const char *FragmentShaderSource, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, BlockWindow *Window, bool PerVertexColor, Color color);

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


class Triangle : public Shape2D
{
public:
    Triangle(Color color, BlockWindow *Window)
    {
        LoadShape2D
        (
        "src/Assets/BlockEngine/Shaders/BasicPerVertexVertexShader.vert",
        "src/Assets/BlockEngine/Shaders/BasicPerVertexFragmentShader.frag",
        TriangleVerticesColor,
        sizeof(TriangleVerticesColor),
        TriangleIndices,
        sizeof(TriangleIndices),
        Window,
        true,
        color
        );

        rendering("Creating Triangle Resources");
    }

    void DrawTriangle()
    {
        DrawShape2D(sizeof(TriangleIndices) / sizeof(TriangleIndices[0]));
    }

    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
    Triangle(Triangle&&) = delete;
    Triangle& operator=(Triangle&&) = delete;

};


class Square : public Shape2D
{
public:
    Square(Color color, BlockWindow *Window)
    {
        LoadShape2D(
        "src/Assets/BlockEngine/Shaders/BasicVertexShader.vert",
        "src/Assets/BlockEngine/Shaders/BasicFragmentShader.frag",
        SquareVertices,
        sizeof(SquareVertices),
        SquareIndices,
        sizeof(SquareIndices),
        Window,
        false,
        color
        );

        rendering("Creating Square Resources");
    }

    void DrawSquare()
    {
        DrawShape2D((sizeof(SquareIndices) / sizeof(SquareIndices[0])));
    };

    Square(const Square&) = delete;
    Square& operator=(const Square&) = delete;
    Square(Square&&) = delete;
    Square& operator=(Square&&) = delete;

};



// ########################
// #          3D          #
// ########################


/**
 * Shape3D
 * -------
 * Base class for common 3D shapes and rendering.
 *
 * Used by objects such as Triangle and Square.
 */
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


