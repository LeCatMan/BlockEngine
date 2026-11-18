#pragma once

#include <vector>
#include "../Window/Window.hpp"
#include "../../Debugger/Logger/Logger.hpp"
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"
#include "../../Assets/BlockEngine/BasicShapes/BasicShapes.hpp"
#include "../../Assets/BlockEngine/GeneratedAssets/GeneratedAssets.hpp"
#include "../Color/Color.hpp"

// ########################
// #          2D          #
// ########################

struct Shape2DTarget
{
    Blockwindow *Window = nullptr;
    unsigned int Shape2DVAO = 0, Shape2DVBO = 0, Shape2DEBO = 0, Shape2DShader = 0;
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
    bool IsLoaded = false;
    std::vector<Shape2DTarget> Windows;
    int count = 0;
    size_t SizeOfMeshIndices = 0;
public:

    Shape2D() = default;

    BlockResult LoadShape2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, size_t ShapeIndicesArraySize, bool PerVertexColor, Color color, Blockwindow **Window, int WindowCount);

    BlockResult LoadEmbeddedShape2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, size_t ShapeIndicesArraySize, bool PerVertexColor, Color color, Blockwindow **Window, int WindowCount);

    void DrawShape2D(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale);

    BlockResult UnloadShape2D();

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

    Triangle() = default;

    BlockResult Create(Color color, Blockwindow **Window, int WindowCount, bool PerVertexColoring)
    {
        if (LoadEmbeddedShape2D(PerVertexColoring ? asset_BasicPerVertexVertexShader_vert : asset_BasicVertexShader_vert,
            PerVertexColoring ? asset_BasicPerVertexFragmentShader_frag : asset_BasicFragmentShader_frag,
            PerVertexColoring ? TriangleVerticesColor : TriangleVertices,
            PerVertexColoring ? sizeof(TriangleVerticesColor) : sizeof(TriangleVertices),
            TriangleIndices, sizeof(TriangleIndices), sizeof(TriangleIndices[0]),
            PerVertexColoring, color, Window, WindowCount) >= 0)
        {
            rendering("Created Triangle Resources");
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            error("Cannot Create Triangle Resources");
            return BLOCK_FAILURE;
        }
    }

    void Draw(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale)
    {
        DrawShape2D(WindowNumber, WireMode, color, Position, Rotation, Scale);
    }

    BlockResult Unload()
    {
        return UnloadShape2D();
    }

    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
    Triangle(Triangle&&) = delete;
    Triangle& operator=(Triangle&&) = delete;
private:
    using Shape2D::LoadShape2D;
    using Shape2D::LoadEmbeddedShape2D;
    using Shape2D::DrawShape2D;
    using Shape2D::UnloadShape2D;
}; 


class Square : public Shape2D
{
public:
    Square() = default;

    BlockResult Create(Color color, Blockwindow **Window, int WindowCount, bool PerVertexColoring)
    {
        if (LoadEmbeddedShape2D(PerVertexColoring ? asset_BasicPerVertexVertexShader_vert : asset_BasicVertexShader_vert,
            PerVertexColoring ? asset_BasicPerVertexFragmentShader_frag : asset_BasicFragmentShader_frag,
            PerVertexColoring ? SquareVerticesColor : SquareVertices,
            PerVertexColoring ? sizeof(SquareVerticesColor) : sizeof(SquareVertices),
            SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]),
            PerVertexColoring, color, Window, WindowCount) >= 0)
        {
            rendering("Created Square Resources");
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            error("Cannot Create Square Resources");
            return BLOCK_FAILURE;
        }
    }

    void Draw(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale)
    {
        DrawShape2D(WindowNumber, WireMode, color, Position, Rotation, Scale);
    };

    BlockResult Unload()
    {
        return UnloadShape2D();
    }

    Square(const Square&) = delete;
    Square& operator=(const Square&) = delete;
    Square(Square&&) = delete;
    Square& operator=(Square&&) = delete;
private:
    using Shape2D::LoadShape2D;
    using Shape2D::LoadEmbeddedShape2D;
    using Shape2D::DrawShape2D;
    using Shape2D::UnloadShape2D;
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


