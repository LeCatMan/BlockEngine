#include "Shape.hpp"


#include "../Shader/Shader.hpp"
#include "../RenderingUtilities.hpp"
#include "../Essential/Essential.hpp"
#include "../RenderingEngine/RenderingEngine.hpp"
#include <stdio.h>
#include <string.h>

#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"
#include "../Color/Color.hpp"
#include "../../../external/glm/glm/glm.hpp"
#include "../../../external/glm/glm/gtc/matrix_transform.hpp"
#include "../../../external/glm/glm/gtc/type_ptr.hpp"


BlockResult Shape2D::LoadShape2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, size_t ShapeIndicesArraySize, bool PerVertexColor, Color color, Blockwindow **Window, int WindowCount)
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            warning("Cannot load Shape2D because it's already loaded");
            return BLOCK_FAILURE;
        }
        else
        {
            if (WindowCount <= 0)
            {
                error("Invalid parameter WindowCount value should be over 0");
                return BLOCK_ERR_INVALID_PARAM;
            }
            else
            {
                count = WindowCount;
                Windows.resize(WindowCount);
                SizeOfMeshIndices = ShapeIndicesSize / ShapeIndicesArraySize;

                for (int i = 0; i < WindowCount; i++)
                {
                    if (Window[i] == nullptr)
                    {
                        error("Invalid window parameter");
                        return BLOCK_ERR_INVALID_PARAM;
                    }
                    else
                    {
                        Windows[i].Window = Window[i];
                        glfwMakeContextCurrent(Windows[i].Window);

                        Shader2D Shader;
                        if (Shader.CreateShader2D(VertexShaderPath, FragmentShaderPath) < 0)
                        {
                            error("Shader creation failed");
                            return BLOCK_FAILURE;
                        }
                        else
                        {
                            CreateVAO(&Windows[i].Shape2DVAO);
                            CreateVBO(Vertices, VerticesSize, &Windows[i].Shape2DVBO, PerVertexColor, false, true);
                            CreateEBO(ShapeIndices, ShapeIndicesSize, &Windows[i].Shape2DEBO);
                            ShaderProgram(&Windows[i].Shape2DShader, Shader.VertexShader, Shader.FragmentShader);

                            glUseProgram(Windows[i].Shape2DShader);
                            glUniform4f(glGetUniformLocation(Windows[i].Shape2DShader, "color"), color.r, color.g, color.b, color.a);
                        }
                    }
                }
                
                IsLoaded = true;
                return BLOCK_SUCCESS_TRUE;
            }
        }
    }
    else
    {
        error("Cannot load Shape2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
}


BlockResult Shape2D::LoadEmbeddedShape2D(const char *VertexShaderSource, const char *FragmentShaderSource, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, size_t ShapeIndicesArraySize, bool PerVertexColor, Color color, Blockwindow **Window, int WindowCount)
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            warning("Cannot load Shape2D because it's already loaded");
            return BLOCK_FAILURE;
        }
        else
        {
            if (WindowCount <= 0)
            {
                error("Invalid parameter WindowCount value should be over 0");
                return BLOCK_ERR_INVALID_PARAM;
            }
            else
            {
                count = WindowCount;
                Windows.resize(WindowCount);
                SizeOfMeshIndices = ShapeIndicesSize / ShapeIndicesArraySize;

                for (int i = 0; i < WindowCount; i++)
                {
                    if (Window[i] == nullptr)
                    {
                        error("Invalid window parameter");
                        return BLOCK_ERR_INVALID_PARAM;
                    }
                    else
                    {
                        Windows[i].Window = Window[i];
                        glfwMakeContextCurrent(Windows[i].Window);

                        Shader2D Shader;
                        if (Shader.CreateEmbeddedShader2D(VertexShaderSource, FragmentShaderSource) < 0)
                        {
                            error("Shader creation failed");
                            return BLOCK_FAILURE;
                        }
                        else
                        {
                            CreateVAO(&Windows[i].Shape2DVAO);
                            CreateVBO(Vertices, VerticesSize, &Windows[i].Shape2DVBO, PerVertexColor, false, true);
                            CreateEBO(ShapeIndices, ShapeIndicesSize, &Windows[i].Shape2DEBO);
                            ShaderProgram(&Windows[i].Shape2DShader, Shader.VertexShader, Shader.FragmentShader);

                            glUseProgram(Windows[i].Shape2DShader);
                            glUniform4f(glGetUniformLocation(Windows[i].Shape2DShader, "color"), color.r, color.g, color.b, color.a);
                        }
                    }
                }
                
                IsLoaded = true;
                return BLOCK_SUCCESS_TRUE;
            }
        }
    }
    else
    {
        error("Cannot load Shape2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
}


void Shape2D::DrawShape2D(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale)
{
    glm::mat4 Transform = glm::mat4(1.0f);

    Transform = glm::translate(Transform, glm::vec3(Position.x, Position.y, Position.z));

    Transform = glm::rotate(Transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    Transform = glm::rotate(Transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    Transform = glm::rotate(Transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    Transform = glm::scale(Transform, glm::vec3(Scale.x, Scale.y, Scale.z));

    if (WindowNumber <= count && WindowNumber >= 1)
    {
        glfwMakeContextCurrent(Windows[WindowNumber - 1].Window);
        glUseProgram(Windows[WindowNumber - 1].Shape2DShader);
        glUniformMatrix4fv(glGetUniformLocation(Windows[WindowNumber - 1].Shape2DShader, "Transform"), 1, GL_FALSE, glm::value_ptr(Transform));
        glUniform4f(glGetUniformLocation(Windows[WindowNumber - 1].Shape2DShader, "color"), color.r, color.g, color.b, color.a);
        glBindVertexArray(Windows[WindowNumber - 1].Shape2DVAO);
        glPolygonMode(GL_FRONT_AND_BACK, WireMode ? GL_LINE : GL_FILL);
        glDrawElements(GL_TRIANGLES, SizeOfMeshIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    else
    {
        error("Invalid parameter WindowNumber out of bounds");
    }
}


BlockResult Shape2D::UnloadShape2D()
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            for (int i = 0; i < count; i++)
            {
                glfwMakeContextCurrent(Windows[i].Window);
                DestroyShader(Windows[i].Shape2DShader);
                DestroyVAO(Windows[i].Shape2DVAO);
                DestroyVBO(Windows[i].Shape2DVBO);
                DestroyEBO(Windows[i].Shape2DEBO);

                Windows[i].Shape2DShader = 0;
                Windows[i].Shape2DVAO = 0;
                Windows[i].Shape2DVBO = 0;
                Windows[i].Shape2DEBO = 0;
            }
            Windows.clear();
            Windows.shrink_to_fit();
            count = 0;
            IsLoaded = false;
            rendering("Destroyed the Shapes resources");
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            warning("Cannot unload Shape2D because it's already unload");
            return BLOCK_FAILURE;
        }
    }
    else
    {
        error("Cannot unload Shape2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
}


Shape2D::~Shape2D()
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            for (int i = 0; i < count; i++)
            {
                glfwMakeContextCurrent(Windows[i].Window);
                DestroyShader(Windows[i].Shape2DShader);
                DestroyVAO(Windows[i].Shape2DVAO);
                DestroyVBO(Windows[i].Shape2DVBO);
                DestroyEBO(Windows[i].Shape2DEBO);

                Windows[i].Shape2DShader = 0;
                Windows[i].Shape2DVAO = 0;
                Windows[i].Shape2DVBO = 0;
                Windows[i].Shape2DEBO = 0;
            }
            Windows.clear();
            Windows.shrink_to_fit();
            count = 0;
            IsLoaded = false;
            rendering("Destroyed the Shapes resources");
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        error("Cannot unload Shape2D because the Rendering engine isn't Initialized");
        return;
    }
}






