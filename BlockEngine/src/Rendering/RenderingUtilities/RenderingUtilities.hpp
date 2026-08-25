#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../../Debugger/Debugger.hpp"
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"
#include "../../Inputs/Inputs.hpp"

extern GLFWwindow* Bwindow;
extern const char *TestFragmentShaderSource;
extern const char *TestVertexShaderSource;
class Shape2D;

/**
 * Color
 * -----
 * Represents an RGB color using values from 0 to 255.
 *
 * Example:
 *     Color MyColor(255, 128, 64);
 */
struct Color
{
    float r;
    float g;
    float b;

    Color(float r, float g, float b)
    {
        this->r = r / 255.0f;
        this->g = g / 255.0f;
        this->b = b / 255.0f;
    }
};

/**
 * Texture
 * -------
 * Handles texture creation, loading, and unloading.
 *
 * Example:
 *     Texture MyTexture;
 *     MyTexture.CreateTexture("texture.png", GL_LINEAR, GL_LINEAR);
 */
class Texture
{
private:
    unsigned int texture;

public:
    void CreateTexture(const char *ImagePath, GLint MinifyFilter, GLint MagnifyingFilter);
    void LoadTexture(Shape2D& shape);
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

public:
    unsigned int VertexShader;
    unsigned int FragmentShader;

    Shader2D(char *VertexShaderSourcePath, char *FragmentShaderSourcePath);

    ~Shader2D();
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
    friend class Texture;

public:

    Shape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor, bool HasTexture);

    ~Shape2D();

    Shape2D(const Shape2D&) = delete;

    Shape2D& operator=(const Shape2D&) = delete;

    Shape2D(Shape2D&&) = delete;

    Shape2D& operator=(Shape2D&&) = delete;

    void DrawShape2D(size_t ShapeIndicesSize);
};

// ========================
// |        Shapes        |
// ========================

// Triangle
extern const float TrianglePerVertexColor[18];
extern const float TrianglePosColorUV[24];
extern const float TriangleVertices[9];
extern const unsigned int TriangleIndices[3];

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
    Triangle(Color color) : Shape2D(
        color,
        "src/Assets/BlockEngine/Shaders/BasicPerVertexVertexShader.vert",
        "src/Assets/BlockEngine/Shaders/BasicPerVertexFragmentShader.frag",
        TrianglePerVertexColor,
        sizeof(TrianglePerVertexColor),
        TriangleIndices,
        sizeof(TriangleIndices),
        true,
        false)
    {
        info("Creating Triangle Resources");
    }

    ~Triangle();

    /**
     * Draw Triangle
     * -------------
     * Draws the triangle.
     *
     * Example:
     *     MyTriangle.DrawTriangle();
     */
    void DrawTriangle()
    {
        DrawShape2D(sizeof(TriangleIndices) / sizeof(TriangleIndices[0]));
    }
};

// square
extern const float SquarePerVertexColor[24];
extern const float SquarePosColorUV[32];
extern const float SquareVertices[12];
extern const unsigned int SquareIndices[6];

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
    Square(Color color) : Shape2D(color, "src/Assets/BlockEngine/Shaders/BasicVertexShader.vert", "src/Assets/BlockEngine/Shaders/BasicFragmentShader.frag", SquareVertices, sizeof(SquareVertices), SquareIndices, sizeof(SquareIndices), false, false)
    {
    }

    ~Square();

    /**
     * Draw Square
     * -----------
     * Draws the square.
     *
     * Example:
     *     MySquare.DrawSquare();
     */
    void DrawSquare()
    {
        DrawShape2D(sizeof(SquareIndices) / sizeof(SquareIndices[0]));
    }
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


int InitializeWindow(int WindowWidth,int WindowHeight,const char *WindowTitle);
void UpdateWindow();
bool WindowShouldClose();
void CloseWindow();
void BackGroundColor(Color color, int opacity);
void RenderingShutDown();