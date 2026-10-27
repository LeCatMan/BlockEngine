#include "Essential.hpp"
// glad + glfw
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

// glm
#include "../../../external/glm/glm/glm.hpp" // vec2, vec3, mat4, radians
#include "../../../external/glm/glm/ext.hpp" // perspective, translate, rotate

// ========================
// |         VAO          |
// ========================


void CreateVAO(unsigned int *VAO)
{
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
}


void DestroyVAO(unsigned int VAO)
{
    glDeleteVertexArrays(1, &VAO);
}


// ========================
// |         VBO          |
// ========================


/**
 * @param Stride you can put it to 0 to auto stride.
 */
void CreateVBO(const float *Vertices, size_t VerticesSize, unsigned int *VBO, bool PerVertexColor, bool texture, size_t Stride, Color BorderColor, bool RGBA)
{
    if (Stride == 0)
    {
        Stride = (3 + (PerVertexColor ? 4 : 0) + (texture ? 2 : 0)) * sizeof(float);
    }

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, VerticesSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Stride, (void *)0);
    glEnableVertexAttribArray(0);

    if (PerVertexColor)
    {
        glEnableVertexAttribArray(1);
        if (RGBA)
        {
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, Stride, (void *)(3 * sizeof(float)));
        }
        else
        {
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Stride, (void *)(3 * sizeof(float)));
        }
    }
    else
    {
        glVertexAttrib4f(1, 1.0f, 1.0f, 1.0f, 1.0f);
    }

    if (texture)
    {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Stride, (void *)((3 + (PerVertexColor ? 4 : 0)) * sizeof(float)));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float BC[4] = {BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BC);
    }
}


void DestroyVBO(unsigned int VBO)
{
    glDeleteBuffers(1, &VBO);
}


// ========================
// |         EBO          |
// ========================


void CreateEBO(const unsigned int *Indices, size_t Size, unsigned int *EBO)
{
    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
}


void DestroyEBO(unsigned int EBO)
{
    glDeleteBuffers(1, &EBO);
}


// ========================
// |    Shader Program    |
// ========================


void ShaderProgram(unsigned int *Shader, unsigned int VertexShader, unsigned int FragmentShader)
{
    *Shader = glCreateProgram();

    glAttachShader(*Shader, VertexShader);
    glAttachShader(*Shader, FragmentShader);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    glLinkProgram(*Shader);

    int success;
    char infoLog[512];

    glGetProgramiv(*Shader, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(*Shader, 512, NULL, infoLog);
        printf("Shader linking failed: %s\n", infoLog);
    }
}


void DestroyShader(unsigned int Shader)
{
    glDeleteProgram(Shader);
}

