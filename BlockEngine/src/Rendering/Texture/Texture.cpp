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
 * 
 * @param ImagePath The path to the image relative to the program.
 * @param MinifyFilter The filtering method used when the image is displayed smaller.
 * @param MagnifyingFilter The filtering method used when the image is displayed larger.
 * @param Border Controls how the texture behaves outside its normal UV range.
 * @param RGBA When it's true the image will use RGBA when its false it will use RGB.
*/
BlockResult Texture2D::LoadTexture2D(const char *ImagePath, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA)
{
    if (Texture != 0)
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Border);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Border);
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
};


/**
 * 
 * @param ImageData The Data of the image.
 * @param ImageSize Just use sizeof(ImageData). 
 * @param MinifyFilter The filtering method used when the image is displayed smaller.
 * @param MagnifyingFilter The filtering method used when the image is displayed larger.
 * @param Border Controls how the texture behaves outside its normal UV range.
 * @param RGBA When it's true the image will use RGBA when its false it will use RGB.
*/
BlockResult Texture2D::LoadEmbeddedTexture2D(const char *ImageData, size_t ImageSize, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA)
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Border);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Border);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinifyFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagnifyingFilter);

        if (RGBA)
        {    
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
            return BLOCK_SUCCESS_TRUE;
        }
        else 
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
            return BLOCK_SUCCESS_TRUE;
        }
        rendering("Loaded texture");
        IsLoaded = true;
        return BLOCK_SUCCESS_TRUE;
    }
};


BlockResult Texture2D::LoadTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor)
{
    if (IsMeshLoaded)
    {
        warning("The mesh is already loaded!");
        return BLOCK_SUCCESS_FALSE;
    }
    else
    {
        SizeOfMeshIndices = MeshIndicesSize / MeshIndicesArraySize;
        rendering("Loading the texture mesh");
        Shader2D Shader;
        Shader.CreateShader2D(VertexShaderPath, FragmentShaderPath);
        CreateVAO(&Texture2DVAO);
        CreateVBO(Vertices, VerticesSize, &Texture2DVBO, PerVertexColor, true, 0, {255.0f, 0.0f, 255.0f, 255.0f}, true);
        CreateEBO(MeshIndices, MeshIndicesSize, &Texture2DEBO);
        ShaderProgram(&Texture2DShader, Shader.VertexShader, Shader.FragmentShader);
        IsMeshLoaded = true;
        return BLOCK_SUCCESS_TRUE;
    }
}


BlockResult Texture2D::LoadEmbeddedTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor)
{
    if (IsMeshLoaded)
    {
        warning("The mesh is already loaded!");
        return BLOCK_SUCCESS_FALSE;
    }
    else
    {
        SizeOfMeshIndices = MeshIndicesSize / MeshIndicesArraySize;
        rendering("Loading the texture mesh");
        Shader2D Shader;
        Shader.CreateShader2D(VertexShaderPath, FragmentShaderPath);
        CreateVAO(&Texture2DVAO);
        CreateVBO(Vertices, VerticesSize, &Texture2DVBO, PerVertexColor, true, 0, {255.0f, 0.0f, 255.0f, 255.0f}, true);
        CreateEBO(MeshIndices, MeshIndicesSize, &Texture2DEBO);
        ShaderProgram(&Texture2DShader, Shader.VertexShader, Shader.FragmentShader);
        IsMeshLoaded = true;
        return BLOCK_SUCCESS_TRUE;
    }
}


void Texture2D::DrawTexture2D()
{
    glUseProgram(Texture2DShader);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(Texture2DShader, "Texture"), 0);
    unsigned int transformLoc = glGetUniformLocation(Texture2DShader, "Transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, BasicTransform);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glBindVertexArray(Texture2DVAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, SizeOfMeshIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
            DestroyShader(Texture2DShader);
            DestroyVAO(Texture2DVAO);
            DestroyVBO(Texture2DVBO);
            DestroyEBO(Texture2DEBO);
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
        if (IsMeshLoaded)
        {
            DestroyShader(Texture2DShader);
            DestroyVAO(Texture2DVAO);
            DestroyVBO(Texture2DVBO);
            DestroyEBO(Texture2DEBO);
            IsMeshLoaded = false;
            rendering("Unloaded the TextureMesh");
        }
    }
    else
    {
        error("Cannot unload Texture2D because the Rendering engine isn't Initialized");
    }
}


