#include "Shader.hpp"
#include "../../Debugger/Logger/Logger.hpp"
#include "../../../external/glad/include/glad/glad.h"
#include "../../Debugger/Utilities/Utilities.hpp"
#include <string.h>

BlockResult Shader2D::CreateShader2D(const char *VertexShaderSourcePath, const char *FragmentShaderSourcePath)
{
    #pragma region Vertex Shader

    const char *VertexSource = GetFileText(VertexShaderSourcePath);

    if(!VertexSource)
    {
        error("Invalid Path (VertexShaderSourcePath)");
        return BLOCK_ERR_INVALID_PARAM;
    }

    vertexshadersource = new char[strlen(VertexSource) + 1];
    strcpy(vertexshadersource, VertexSource);

    if(!vertexshadersource)
    {
        error("Invalid Path (VertexShaderSourcePath)");
        return BLOCK_ERR_INVALID_PARAM;
    }

    VertexShader = glCreateShader(GL_VERTEX_SHADER);            // creating the vertex shader.
    glShaderSource(VertexShader, 1, &vertexshadersource, NULL); // addes the source to the shader.
    glCompileShader(VertexShader);
    delete[] vertexshadersource;
    vertexshadersource = nullptr;

    int success;
    char infoLog[512];

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.

    if (!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        error("Vertex shader compilation failed: %s", infoLog);
        return BLOCK_FAILURE;
    }

    #pragma endregion

    #pragma region Fragment Shader

    const char *FragmentSource = GetFileText(FragmentShaderSourcePath);

    if(!FragmentSource)
    {
        error("Invalid Path (FragmentShaderSourcePath)");
        return BLOCK_ERR_INVALID_PARAM;
    }

    fragmentshadersource = new char[strlen(FragmentSource) + 1];
    strcpy(fragmentshadersource, FragmentSource);

    if(!fragmentshadersource)
    {
        error("Invalid Path (FragmentShaderSourcePath)");
        return BLOCK_ERR_INVALID_PARAM;
    }

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentshadersource, NULL);
    glCompileShader(FragmentShader);
    delete[] fragmentshadersource;
    fragmentshadersource = nullptr;

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.
    
    if (!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        error("Fragment shader compilation failed: %s", infoLog);
        return BLOCK_FAILURE;
    }

    return BLOCK_SUCCESS_TRUE;
    #pragma endregion
}


BlockResult Shader2D::CreateEmbeddedShader2D(const char *VertexShaderSource, const char *FragmentShaderSource)
{
    #pragma region Vertex Shader

    vertexshadersource = new char[strlen(VertexShaderSource) + 1];
    strcpy(vertexshadersource, VertexShaderSource);

    if(!vertexshadersource)
    {
        error("Invalid Source (VertexShaderSource)");
        return BLOCK_ERR_INVALID_PARAM;
    }

    VertexShader = glCreateShader(GL_VERTEX_SHADER);            // creating the vertex shader.
    glShaderSource(VertexShader, 1, &vertexshadersource, NULL); // addes the source to the shader.
    glCompileShader(VertexShader);
    delete[] vertexshadersource;
    vertexshadersource = nullptr;

    int success;
    char infoLog[512];

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.

    if (!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        error("Vertex shader compilation failed: %s", infoLog);
        return BLOCK_FAILURE;
    }

    #pragma endregion

    #pragma region Fragment Shader

    fragmentshadersource = new char[strlen(FragmentShaderSource) + 1];
    strcpy(fragmentshadersource, FragmentShaderSource);

    if(!vertexshadersource)
    {
        error("Invalid Source (FragmentShaderSource)");
        return BLOCK_ERR_INVALID_PARAM;
    }

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentshadersource, NULL);
    glCompileShader(FragmentShader);
    delete[] fragmentshadersource;
    fragmentshadersource = nullptr;

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.

    if (!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        error("Fragment shader compilation failed: %s", infoLog);
        return BLOCK_FAILURE;
    }

    return BLOCK_SUCCESS_TRUE;
    #pragma endregion
}


Shader2D::~Shader2D()
{};

