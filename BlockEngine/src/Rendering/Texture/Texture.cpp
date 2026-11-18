#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../external/stb-master/stb_image.h"
#include "../../Debugger/Logger/Logger.hpp"
#include "../Essential/Essential.hpp"
#include "../Shader/Shader.hpp"
#include "../RenderingEngine/RenderingEngine.hpp"
#include <stdio.h>
#include "../../../external/glm/glm/glm.hpp"
#include "../../../external/glm/glm/gtc/matrix_transform.hpp"
#include "../../../external/glm/glm/gtc/type_ptr.hpp"
#include "../../Assets/BlockEngine/BasicShapes/Data/2D/Data.hpp"


/**
 * Loads an image file as a texture.
 * Load the image before the texture mesh, because the mesh load sets the
 * wrap mode and border color on the texture that is bound at that moment.
 *
 * @param ImagePath The path to the image, relative to the folder you run the program from.
 * @param MinifyFilter The filtering method used when the image is displayed smaller (BLOCK_NEAREST or BLOCK_LINEAR).
 * @param MagnifyingFilter The filtering method used when the image is displayed larger (BLOCK_NEAREST or BLOCK_LINEAR).
 * @param RGBA When it's true the image will use RGBA when it's false it will use RGB.
 * @return BLOCK_SUCCESS_TRUE on success, BLOCK_SUCCESS_FALSE if already loaded,
 *  1       BLOCK_ERR_INIT_FAILED if the file can't be read, BLOCK_FAILURE if the rendering engine isn't initialized.
 */
BlockResult Texture2D::LoadTexture2D(const char *ImagePath, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, bool RGBA)
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            warning("The texture is already loaded!");
            return BLOCK_SUCCESS_FALSE;
        }
        else
        {
            stbi_set_flip_vertically_on_load(true);
            int width, height, nrChannels;
            unsigned char *data = stbi_load(ImagePath, &width, &height, &nrChannels, RGBA ? 4 : 3);

            if (!data)
            {
                error("Failed to Load texture!");
                error("STBI reason: %s", stbi_failure_reason());
                return BLOCK_ERR_INIT_FAILED;
            }

            glGenTextures(1, &Texture);
            glBindTexture(GL_TEXTURE_2D, Texture);
            // set the texture wrapping/filtering options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinifyFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagnifyingFilter);

            if (RGBA)
            {    
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else
                {
                    error("Failed to Load texture!");
                    return BLOCK_ERR_INIT_FAILED;
                }
                stbi_image_free(data);
            }
            else 
            {
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else
                {
                    error("Failed to Load texture!");
                    return BLOCK_ERR_INIT_FAILED;
                }
                stbi_image_free(data);
            }
            rendering("Loaded texture");
            IsLoaded = true;
            return BLOCK_SUCCESS_TRUE;
        }
    }
    else
    {
        error("Cannot load Texture2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
};


/**
 * Loads an image file as a texture.
 * Load the image before the texture mesh, because the mesh load sets the
 * wrap mode and border color on the texture that is bound at that moment.
 *
 * @param ImageData The Data of the image.
 * @param ImageSize Just use sizeof(ImageData).
 * @param MinifyFilter The filtering method used when the image is displayed smaller (BLOCK_NEAREST or BLOCK_LINEAR).
 * @param MagnifyingFilter The filtering method used when the image is displayed larger (BLOCK_NEAREST or BLOCK_LINEAR).
 * @param RGBA When it's true the image will use RGBA when it's false it will use RGB.
 * @return BLOCK_SUCCESS_TRUE on success, BLOCK_SUCCESS_FALSE if already loaded,
 *         BLOCK_ERR_INIT_FAILED if the file can't be read, BLOCK_FAILURE if the rendering engine isn't initialized.
 */
BlockResult Texture2D::LoadEmbeddedTexture2D(const char *ImageData, size_t ImageSize, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, bool RGBA)
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            warning("The texture is already loaded!");
            return BLOCK_SUCCESS_FALSE;
        }
        else
        {
            stbi_set_flip_vertically_on_load(true);
            int width, height, nrChannels;
            unsigned char *data = stbi_load_from_memory((const stbi_uc*)ImageData, ImageSize, &width, &height, &nrChannels, RGBA ? 4 : 3);

            if (!data)
            {
                error("Failed to Load texture!");
                error("STBI reason: %s", stbi_failure_reason());
                return BLOCK_ERR_INIT_FAILED;
            }

            glGenTextures(1, &Texture);
            glBindTexture(GL_TEXTURE_2D, Texture);
            // set the texture wrapping/filtering options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinifyFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagnifyingFilter);

            if (RGBA)
            {    
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else
                {
                    error("Failed to Load texture!");
                    return BLOCK_ERR_INIT_FAILED;
                }
                stbi_image_free(data);
            }
            else 
            {
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else
                {
                    error("Failed to Load texture!");
                    return BLOCK_ERR_INIT_FAILED;
                }
                stbi_image_free(data);
            }
            rendering("Loaded texture");
            IsLoaded = true;
            return BLOCK_SUCCESS_TRUE;
        }
    }
    else
    {
        error("Cannot load Texture2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
};


BlockResult Texture2D::LoadTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor, BlockTextureFlags TextureBorder, Color TextureBorderColor, Color color, Blockwindow **Window, int WindowCount)
{
    if (RenderingInitialized)
    {
        if (IsMeshLoaded)
        {
            warning("Cannot load Texture2DMesh because it's already loaded");
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
                SizeOfMeshIndices = MeshIndicesSize / MeshIndicesArraySize;
                Windows.resize(WindowCount);
                
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
                            CreateVAO(&Windows[i].Texture2DVAO);
                            CreateVBO(Vertices, VerticesSize, &Windows[i].Texture2DVBO, PerVertexColor, true, true, TextureBorder, TextureBorderColor);
                            CreateEBO(MeshIndices, MeshIndicesSize, &Windows[i].Texture2DEBO);
                            ShaderProgram(&Windows[i].Texture2DShader, Shader.VertexShader, Shader.FragmentShader);
                            IsMeshLoaded = true;
                            glUseProgram(Windows[i].Texture2DShader);
                            glUniform4f(glGetUniformLocation(Windows[i].Texture2DShader, "color"), color.r, color.g, color.b, color.a);
                        }
                    }
                }
                rendering("Loaded the texture mesh");
                return BLOCK_SUCCESS_TRUE;
            }
        }
    }
    else
    {
        error("Cannot load Texture2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
}


BlockResult Texture2D::LoadEmbeddedTextureMesh2D(const char *VertexShaderSource, const char *FragmentShaderSource, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor, BlockTextureFlags TextureBorder, Color TextureBorderColor, Color color, Blockwindow **Window, int WindowCount)
{
    if (RenderingInitialized)
    {
        if (IsMeshLoaded)
        {
            warning("Cannot load Texture2DMesh because it's already loaded");
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
                SizeOfMeshIndices = MeshIndicesSize / MeshIndicesArraySize;
                Windows.resize(WindowCount);
                
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
                            CreateVAO(&Windows[i].Texture2DVAO);
                            CreateVBO(Vertices, VerticesSize, &Windows[i].Texture2DVBO, PerVertexColor, true, true, TextureBorder, TextureBorderColor);
                            CreateEBO(MeshIndices, MeshIndicesSize, &Windows[i].Texture2DEBO);
                            ShaderProgram(&Windows[i].Texture2DShader, Shader.VertexShader, Shader.FragmentShader);
                            IsMeshLoaded = true;
                            glUseProgram(Windows[i].Texture2DShader);
                            glUniform4f(glGetUniformLocation(Windows[i].Texture2DShader, "color"), color.r, color.g, color.b, color.a);
                        }
                    }
                }
                rendering("Loaded the texture mesh");
                return BLOCK_SUCCESS_TRUE;
            }
        }
    }
    else
    {
        error("Cannot load Texture2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
}


void Texture2D::Draw(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale)
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
        glUseProgram(Windows[WindowNumber - 1].Texture2DShader);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(Windows[WindowNumber - 1].Texture2DShader, "Texture"), 0);
        glUniformMatrix4fv(glGetUniformLocation(Windows[WindowNumber - 1].Texture2DShader, "Transform"), 1, GL_FALSE, glm::value_ptr(Transform));
        glBindTexture(GL_TEXTURE_2D, Texture);
        glUniform4f(glGetUniformLocation(Windows[WindowNumber - 1].Texture2DShader, "color"), color.r, color.g, color.b, color.a);
        glBindVertexArray(Windows[WindowNumber - 1].Texture2DVAO);
        glPolygonMode(GL_FRONT_AND_BACK, WireMode ? GL_LINE : GL_FILL);
        glDrawElements(GL_TRIANGLES, SizeOfMeshIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    else
    {
        error("Invalid parameter WindowNumber out of bounds");
    }
}


BlockResult Texture2D::UnloadTexture2D()
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            glDeleteTextures(1, &Texture);
            Texture = 0;
            IsLoaded = false;
            rendering("Unloaded the texture");
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            warning("The texture is already been unloaded!");
            return BLOCK_SUCCESS_FALSE;
        }
    }
    else
    {
        error("Cannot unload Texture2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
}


BlockResult Texture2D::UnloadTextureMesh2D()
{
    if (RenderingInitialized)
    {
        if (IsMeshLoaded)
        {
            for (int i = 0; i < count; i++)
            {
                glfwMakeContextCurrent(Windows[i].Window);
                DestroyShader(Windows[i].Texture2DShader);
                DestroyVAO(Windows[i].Texture2DVAO);
                DestroyVBO(Windows[i].Texture2DVBO);
                DestroyEBO(Windows[i].Texture2DEBO);

                Windows[i].Texture2DShader = 0;
                Windows[i].Texture2DVAO = 0;
                Windows[i].Texture2DVBO = 0;
                Windows[i].Texture2DEBO = 0;
            }
            Windows.clear();
            Windows.shrink_to_fit();
            count = 0;
            IsMeshLoaded = false;
            rendering("Unloaded the TextureMesh");
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            warning("The TextureMesh2D is already been unloaded!");
            return BLOCK_SUCCESS_FALSE;
        }
    }
    else
    {
        error("Cannot unload Texture2D because the Rendering engine isn't Initialized");
        return BLOCK_FAILURE;
    }
}


Texture2D::~Texture2D()
{
    if (RenderingInitialized)
    {
        if (IsLoaded)
        {
            glDeleteTextures(1, &Texture);
            Texture = 0;
            IsLoaded = false;
            rendering("Unloaded the texture");
        }
        else
        {
            warning("The texture is already been unloaded!");
        }
        if (IsMeshLoaded)
        {
            for (int i = 0; i < count; i++)
            {
                glfwMakeContextCurrent(Windows[i].Window);
                DestroyShader(Windows[i].Texture2DShader);
                DestroyVAO(Windows[i].Texture2DVAO);
                DestroyVBO(Windows[i].Texture2DVBO);
                DestroyEBO(Windows[i].Texture2DEBO);

                Windows[i].Texture2DShader = 0;
                Windows[i].Texture2DVAO = 0;
                Windows[i].Texture2DVBO = 0;
                Windows[i].Texture2DEBO = 0;
            }
            Windows.clear();
            Windows.shrink_to_fit();
            count = 0;
            IsMeshLoaded = false;
            rendering("Unloaded the TextureMesh");
        }
        else
        {
            warning("The TextureMesh2D is already been unloaded!");
        }
    }
    else
    {
        error("Cannot unload Texture2D because the Rendering engine isn't Initialized");
    }
}


