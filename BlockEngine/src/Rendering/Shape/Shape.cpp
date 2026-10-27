#include "Shape.hpp"
#include "../Shader/Shader.hpp"
#include "../Window/Window.hpp"
#include "../RenderingUtilities.hpp"
#include "../Essential/Essential.hpp"
#include "../RenderingEngine/RenderingEngine.hpp"
#include "../../Debugger/Logger/Logger.hpp"
#include <stdio.h>
#include <string.h>



void Shape2D::LoadShape2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, BlockWindow *Window, bool PerVertexColor, Color color)
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            warning("Cannot load Shape2D because it's already loaded");
        }
        else
        {
            window = Window->Window;
            glfwMakeContextCurrent(window);
            VertexShader = new char[strlen(VertexShaderPath) + 1];
            FragmentShader = new char[strlen(FragmentShaderPath) + 1];

            strcpy(VertexShader, VertexShaderPath);
            strcpy(FragmentShader, FragmentShaderPath);

            Shader2D Shader;
            Shader.CreateShader2D(VertexShaderPath, FragmentShaderPath);
            CreateVAO(&Shape2DVAO);
            CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor, false, 0, {255.0f,0.0f,255.0f,255.0f}, true);
            CreateEBO(ShapeIndices, ShapeIndicesSize, &Shape2DEBO);
            ShaderProgram(&Shape2DShader, Shader.VertexShader, Shader.FragmentShader);
            glUseProgram(Shape2DShader);
            glUniform4f(glGetUniformLocation(Shape2DShader, "color"), color.r, color.g, color.b, color.a);
            IsLoaded = true;
        }
    }
    else
    {
        error("Cannot load Shape2D because the Rendering engine isn't Initialized");
    }
}


void Shape2D::LoadEmbeddedShape2D(const char *VertexShaderSource, const char *FragmentShaderSource, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, BlockWindow *Window, bool PerVertexColor, Color color)
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            warning("Cannot load EmbeddedShape2D because it's already loaded");
        }
        else
        {
            window = Window->Window;
            glfwMakeContextCurrent(window);

            VertexShader = new char[strlen(VertexShaderSource) + 1];
            FragmentShader = new char[strlen(FragmentShaderSource) + 1];

            strcpy(VertexShader, VertexShaderSource);
            strcpy(FragmentShader, FragmentShaderSource);
            Shader2D Shader;
            Shader.CreateEmbeddedShader2D(VertexShaderSource, FragmentShaderSource);
            CreateVAO(&Shape2DVAO);
            CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor, false, 0, {255.0f,0.0f,255.0f,255.0f}, true);
            CreateEBO(ShapeIndices, ShapeIndicesSize, &Shape2DEBO);
            ShaderProgram(&Shape2DShader, Shader.VertexShader, Shader.FragmentShader);
            glUseProgram(Shape2DShader);
            glUniform4f(glGetUniformLocation(Shape2DShader, "color"), color.r, color.g, color.b, color.a);
            IsLoaded = true;
        }
    }
    else
    {
        error("Cannot load EmbeddedShape2D because the Rendering engine isn't Initialized");
    }
}


void Shape2D::DrawShape2D(size_t ShapeIndicesSize)
{
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glfwMakeContextCurrent(window);
    glUseProgram(Shape2DShader);
    glBindVertexArray(Shape2DVAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, ShapeIndicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Shape2D::UnloadShape2D()
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            glfwMakeContextCurrent(window);
            DestroyShader(Shape2DShader);
            DestroyVAO(Shape2DVAO);
            DestroyVBO(Shape2DVBO);
            DestroyEBO(Shape2DEBO);

            delete[] VertexShader;
            delete[] FragmentShader;

            VertexShader = nullptr;
            FragmentShader = nullptr;

            Shape2DShader = 0;
            Shape2DVAO = 0;
            Shape2DVBO = 0;
            Shape2DEBO = 0;

            IsLoaded = false;

            rendering("Destroyed the Shapes resources");
        }
        else
        {
            warning("Cannot unload Shape2D because it's already unload");
        }
    }
    else
    {
        error("Cannot unload Shape2D because the Rendering engine isn't Initialized");
    }
}


Shape2D::~Shape2D()
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            glfwMakeContextCurrent(window);
            DestroyShader(Shape2DShader);
            DestroyVAO(Shape2DVAO);
            DestroyVBO(Shape2DVBO);
            DestroyEBO(Shape2DEBO);

            delete[] VertexShader;
            delete[] FragmentShader;

            VertexShader = nullptr;
            FragmentShader = nullptr;

            Shape2DShader = 0;
            Shape2DVAO = 0;
            Shape2DVBO = 0;
            Shape2DEBO = 0;

            IsLoaded = false;

            rendering("Destroyed the Shapes resources");
        }
        else
        {
            return;
        }
    }
    else
    {
        error("Cannot unload Shape2D because the Rendering engine isn't Initialized");
    }
}






