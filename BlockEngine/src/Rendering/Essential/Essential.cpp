#include "Essential.hpp"
// glad + glfw

#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

// ========================
// |         VAO          |
// ========================


BlockResult CreateVAO(unsigned int *VAO)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    glGenVertexArrays(1, VAO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to generate VAO");
        return BLOCK_FAILURE;
    }

    glBindVertexArray(*VAO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to bind VAO");
        return BLOCK_FAILURE;
    }

    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}



BlockResult DestroyVAO(unsigned int VAO)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    glDeleteVertexArrays(1, &VAO);

    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to destroy VAO");
        return BLOCK_FAILURE;
    }

    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}



// ========================
// |         VBO          |
// ========================


/**
 * Creates a VBO, uploads the vertex data and configures the vertex attributes.
 * A VAO must be bound before calling this.
 *
 * Vertex layout per vertex: position (3 floats), then optional color
 * (3 or 4 floats), then optional texture coordinates (2 floats).
 *
 * Attribute locations: 0 = position, 1 = color, 2 = texture coordinates.
 * If PerVertexColor is false, attribute 1 is set to constant white.
 *
 * @param Vertices           Pointer to the vertex data.
 * @param VerticesSize       Size of the vertex data in bytes.
 * @param VBO                Output: receives the generated buffer ID.
 * @param PerVertexColor     True if each vertex contains color values.
 * @param texture            True if each vertex contains texture coordinates.
 * @param RGBA               True if vertex colors are RGBA (4 floats), false for RGB (3 floats).
 * @param TextureBorder      Wrap mode for the texture (e.g. GL_REPEAT, GL_CLAMP_TO_BORDER).
 *                           Ignored when texture is false.
 * @param TextureBorderColor Border color (0-255 via Color) used with GL_CLAMP_TO_BORDER.
 *                           Ignored when texture is false or the wrap mode isn't GL_CLAMP_TO_BORDER.
 *                           Invalid values fall back to magenta.
 * @return BLOCK_SUCCESS_TRUE on success, BLOCK_FAILURE if buffer creation or binding fails.
 */
BlockResult CreateVBO(const float *Vertices, size_t VerticesSize, unsigned int *VBO, bool PerVertexColor, bool texture, bool RGBA, BlockTextureFlags TextureBorder, Color TextureBorderColor)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    int ColorSize = PerVertexColor ? (RGBA ? 4 : 3) : 0;
    size_t Stride = (3 + ColorSize + (texture ? 2 : 0)) * sizeof(float);

    glGenBuffers(1, VBO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to generate VBO");
        return BLOCK_FAILURE;
    }
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to bind VBO");
        return BLOCK_FAILURE;
    }
    glBufferData(GL_ARRAY_BUFFER, VerticesSize, Vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Stride, (void *)0);
    glEnableVertexAttribArray(0);


    if (PerVertexColor)
    {
        glVertexAttribPointer(1, ColorSize, GL_FLOAT, GL_FALSE, Stride, (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    else
    {
        glVertexAttrib4f(1, 1.0f, 1.0f, 1.0f, 1.0f);
    }

    if (texture)
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Stride, (void *)((3 + ColorSize) * sizeof(float)));
        glEnableVertexAttribArray(2);

        if (TextureBorder == GL_CLAMP_TO_BORDER)
        {
            float BorderColor[4] = {1.0f, 0.0f, 1.0f, 1.0f};
            
            if (TextureBorderColor.r >= 0.0f && TextureBorderColor.r <= 1.0f && TextureBorderColor.g >= 0.0f && TextureBorderColor.g <= 1.0f && TextureBorderColor.b >= 0.0f && TextureBorderColor.b <= 1.0f && TextureBorderColor.a >= 0.0f && TextureBorderColor.a <= 1.0f)
            {
                BorderColor[0] = TextureBorderColor.r;
                BorderColor[1] = TextureBorderColor.g;
                BorderColor[2] = TextureBorderColor.b;
                BorderColor[3] = TextureBorderColor.a;
            }
            else
            {
                error("Color value over 255 or under 0");
            }
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureBorder);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureBorder);
    }

    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}



BlockResult DestroyVBO(unsigned int VBO)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    glDeleteBuffers(1, &VBO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to destroy VBO");
        return BLOCK_FAILURE;
    }

    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}



// ========================
// |         EBO          |
// ========================


BlockResult CreateEBO(const unsigned int *Indices, size_t Size, unsigned int *EBO)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    glGenBuffers(1, EBO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to generate EBO");
        return BLOCK_FAILURE;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to bind EBO");
        return BLOCK_FAILURE;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}



BlockResult DestroyEBO(unsigned int EBO)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    glDeleteBuffers(1, &EBO);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to destroy EBO");
        return BLOCK_FAILURE;
    }

    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}



// ========================
// |    Shader Program    |
// ========================


BlockResult ShaderProgram(unsigned int *Shader, unsigned int VertexShader, unsigned int FragmentShader)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    *Shader = glCreateProgram();
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to create shader program");
        return BLOCK_FAILURE;
    }

    glAttachShader(*Shader, VertexShader);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to attach vertex shader");
        return BLOCK_FAILURE;
    }
    glAttachShader(*Shader, FragmentShader);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to attach fragment shader");
        return BLOCK_FAILURE;
    }

    glDeleteShader(VertexShader);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to delete vertex shader");
        return BLOCK_FAILURE;
    }
    glDeleteShader(FragmentShader);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to delete fragment shader");
        return BLOCK_FAILURE;
    }

    glLinkProgram(*Shader);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to link shader program");
        return BLOCK_FAILURE;
    }

    int success;
    char infoLog[512];

    glGetProgramiv(*Shader, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(*Shader, 512, NULL, infoLog);
        printf("Shader linking failed: %s\n", infoLog);
    }

    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}



BlockResult DestroyShader(unsigned int Shader)
{
    GLenum GError;
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }

    glDeleteProgram(Shader);
    if (glGetError() != GL_NO_ERROR)
    {
        error("Failed to destroy shader program");
        return BLOCK_FAILURE;
    }
    while ((GError = glGetError()) != GL_NO_ERROR)
    {
        error("OpenGL error detected: %u", GError);
    }
    return BLOCK_SUCCESS_TRUE;
}


