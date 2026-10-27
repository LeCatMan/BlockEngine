#pragma once
#include "../Shape/Shape.hpp"
#include "../Texture/Texture.hpp"

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

    BlockResult CreateShader2D(const char *VertexShaderSourcePath, const char *FragmentShaderSourcePath);

    BlockResult CreateEmbeddedShader2D(const char *VertexShaderSource, const char *FragmentShaderSource);

    ~Shader2D();

    Shader2D() = default;
    Shader2D(const Shader2D&) = delete;
    Shader2D& operator=(const Shader2D&) = delete;
    Shader2D(Shader2D&&) = delete;
    Shader2D& operator=(Shader2D&&) = delete;

    friend Shape2D;
    friend Texture2D;
};

