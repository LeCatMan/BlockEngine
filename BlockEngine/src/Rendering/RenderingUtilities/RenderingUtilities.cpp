#define STB_IMAGE_IMPLEMENTATION
#include "../../../external/stb-master/stb_image.h"
#include "../../Debugger/Utilities/Utilities.hpp"
#include "RenderingUtilities.hpp"

// ########################
// #      Window Stuff    #
// ########################

static bool RenderingInitialized = BLOCK_SUCCESS_FALSE;
GLFWwindow *Bwindow;
GLFWmonitor *Monitor;

// Update the viewport to match the window size.
void FrameBufferSizeCallback(GLFWwindow *Bwindow, int WindowWidth, int WindowHeight)
{
    //         x  y    width        height
    glViewport(0, 0, WindowWidth, WindowHeight);
}


// Initialize the rendering engine with default settings.
BlockResult InitializeWindow(int WindowWidth, int WindowHeight, const char *WindowTitle, bool VSync)
{
    if (RenderingInitialized == BLOCK_SUCCESS_FALSE)
    {
    #pragma region load glad and glfw and make the window


    if (!glfwInit())
    {
        error("Failed to initialize GLFW");
        RenderingInitialized = BLOCK_SUCCESS_FALSE;
        return BLOCK_ERR_INIT_FAILED;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Bwindow = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

    if (Bwindow == NULL)
    {
        error("Failed to create GLFW window");
        glfwTerminate();
        RenderingInitialized = BLOCK_SUCCESS_FALSE;
        return BLOCK_ERR_INIT_FAILED;
    }
    glfwMakeContextCurrent(Bwindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        error("Failed to initialize GLAD");
        RenderingInitialized = BLOCK_SUCCESS_FALSE;
        return BLOCK_ERR_INIT_FAILED;
    }


    #pragma endregion

    #pragma region set the fps and vsync


    glfwSetFramebufferSizeCallback(Bwindow, FrameBufferSizeCallback);
    
    Monitor = glfwGetPrimaryMonitor();
    if (Monitor == NULL)
    {
        error("Couldn't get the monitor");
        RenderingInitialized = BLOCK_SUCCESS_FALSE;
        return BLOCK_ERR_INIT_FAILED;
    }
    else
    {
        const GLFWvidmode *Mode = glfwGetVideoMode(Monitor);

        rendering("Monitor: %d Hz", Mode->refreshRate);

        if (VSync)
        {
            glfwSwapInterval(1);
        }
    }


    #pragma endregion
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    rendering("Rendering engine initialized!");
    rendering("Window initialized!");
    RenderingInitialized = BLOCK_SUCCESS_TRUE;
    return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        warning("Cannot initialize the window because the window engine is already Initialized");
        return BLOCK_FAILURE;
    }
    

}


BlockResult CloseWindow()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        glfwSetWindowShouldClose(Bwindow, true);
        rendering("Closed the window");
        return BLOCK_SUCCESS_TRUE;
    }
    else 
    {
        warning("Cannot close the window because the rendering engine is not Initialized");
        return BLOCK_FAILURE;
    }
}


BlockResult RenderingShutdown()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        rendering("Rendering engine shutdown!");
        glfwTerminate();
        rendering("Shutingdown the Rendering Engine!");
        return BLOCK_SUCCESS_TRUE;
    }
    else 
    {
        warning("Cannot close the window because the rendering engine is not Initialized");
        return BLOCK_FAILURE;
    }

}


BlockResult BackGroundColor(Color color)
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        glClearColor((color.r), (color.g), (color.b), (color.a));
        glClear(GL_COLOR_BUFFER_BIT);
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        warning("Cannot change the background color because the rendering engine is not Initialized");
        return BLOCK_FAILURE;
    }
}


// Checks the close flag of the specified window.
BlockResult WindowShouldClose()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (glfwWindowShouldClose(Bwindow) == true)
        {
            return BLOCK_SUCCESS_TRUE;
        }
        else if (glfwWindowShouldClose(Bwindow) == false)
        {
            return BLOCK_SUCCESS_FALSE;
        }
        else
        {
            error("wtf did you do ? i mean there is a possible error which is glfw is not initialized but i just checked for that ???");
        }
        
    }
    else
    {
        warning("Cannot get the state of the window because the rendering engine is not Initialized");
        return BLOCK_FAILURE;
    }
    return BLOCK_FAILURE;

}


// process rendering events.
void UpdateWindow()
{
    UpdateAudio();
    UpdateInput();
    if (KeyEvent(ExitKey, BLOCK_PRESS))
    {
        CloseWindow();
    }
    glfwSwapBuffers(Bwindow); // Swaps the front and back buffers of the specified window.
}


// ########################
// #       Examples       #
// ########################
//
// Basic shapes provided by Block Engine.
//
// These shapes are ready to use and cover common
// use cases. You do not need to create your own
// vertex data unless you need a shape that is not
// provided here.
//
// The data is kept readable so you can understand
// and modify the shapes if needed.


// =========================
// |       Triangle        |
// =========================

// Position + Color
const float TriangleVerticesColor[21] = {
    // Position              // Color
    //  x      y      z       r      g      b      a
       0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   // Bottom right
      -0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   // Bottom left
       0.0f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f    // Top
};

// Position + Color + UV
const float TriangleVerticesColorUV[27] = {
    // Position              // Color              // UV
    //  x      y      z       r      g      b      a       u      v
       0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,   // Bottom right
      -0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   1.0f, 0.0f,   // Bottom left
       0.0f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f,   0.5f, 1.0f    // Top
};

// Position only
const float TriangleVertices[9] = {
    //  x      y      z
       0.5f, -0.5f, 0.0f,   // Bottom right
      -0.5f, -0.5f, 0.0f,   // Bottom left
       0.0f,  0.5f, 0.0f    // Top
};

const unsigned int TriangleIndices[3] = {
    0, 1, 2
};


// =========================
// |        Square         |
// =========================

// Position + Color
const float SquareVerticesColor[28] = {
    // Position              // Color
    //  x      y      z       r      g      b      a
      -0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f,   // Top left
       0.5f,  0.5f, 0.0f,    1.0f,  1.0f,  0.0f, 1.0f    // Top right
};

// Position + Color + UV
const float SquareVerticesColorUV[36] = {
    // Position              // Color              // UV
    //  x      y      z       r      g      b      a       u      v
      -0.5f, -0.5f, 0.0f,    1.0f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,    0.0f,  1.0f,  0.0f, 1.0f,   1.0f, 0.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,    0.0f,  0.0f,  1.0f, 1.0f,   0.0f, 1.0f,   // Top left
       0.5f,  0.5f, 0.0f,    1.0f,  1.0f,  0.0f, 1.0f,   1.0f, 1.0f    // Top right
};

// Position + UV
const float SquareVerticesUV[20] = {
    // Position              // UV
    //  x      y      z       u      v
      -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,    1.0f, 0.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,    0.0f, 1.0f,   // Top left
       0.5f,  0.5f, 0.0f,    1.0f, 1.0f    // Top right
};

// Position only
const float SquareVertices[12] = {
    //  x      y      z
      -0.5f, -0.5f, 0.0f,   // Bottom left
       0.5f, -0.5f, 0.0f,   // Bottom right
      -0.5f,  0.5f, 0.0f,   // Top left
       0.5f,  0.5f, 0.0f    // Top right
};

const unsigned int SquareIndices[6] = {
    0, 1, 2,
    1, 3, 2
};

// ########################
// #      Rendering       #
// ########################


// ========================
// |       Shader2D       |
// ========================


void Shader2D::CreateShader2D(char *VertexShaderSourcePath, char *FragmentShaderSourcePath)
{
    #pragma region Vertex Shader

    vertexshadersource = GetFileText(VertexShaderSourcePath);

    if(!vertexshadersource)
    {
        error("Invalid Path (VertexShaderSourcePath)");
        return;
    }

    VertexShader = glCreateShader(GL_VERTEX_SHADER);            // creating the vertex shader.
    glShaderSource(VertexShader, 1, &vertexshadersource, NULL); // addes the source to the shader.
    glCompileShader(VertexShader);
    free(vertexshadersource);
    vertexshadersource = nullptr;

    int success;
    char infoLog[512];

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.

    if (!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        error("Vertex shader compilation failed: %s", infoLog);
        return;
    }

    #pragma endregion

    #pragma region Fragment Shader

    fragmentshadersource = GetFileText(FragmentShaderSourcePath);

    if(!fragmentshadersource)
    {
        error("Invalid Path (FragmentShaderSourcePath)");
        return;
    }

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentshadersource, NULL);
    glCompileShader(FragmentShader);
    free(fragmentshadersource);
    fragmentshadersource = nullptr;

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.
    
    if (!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        error("Fragment shader compilation failed: %s", infoLog);
        return;
    }

    #pragma endregion
}


void Shader2D::CreateEmbeddedShader2D(char *VertexShaderSource, char *FragmentShaderSource)
{
    vertexshadersource = VertexShaderSource;

    if(!vertexshadersource)
    {
        error("Invalid Source (VertexShaderSource)");
        return;
    }

    VertexShader = glCreateShader(GL_VERTEX_SHADER);            // creating the vertex shader.
    glShaderSource(VertexShader, 1, &vertexshadersource, NULL); // addes the source to the shader.
    glCompileShader(VertexShader);
    free(vertexshadersource);
    vertexshadersource = nullptr;

    int success;
    char infoLog[512];

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.

    if (!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        error("Vertex shader compilation failed: %s", infoLog);
        return;
    }

    vertexshadersource = FragmentShaderSource;

    if(!vertexshadersource)
    {
        error("Invalid Source (FragmentShaderSource)");
        return;
    }

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentshadersource, NULL);
    glCompileShader(FragmentShader);
    free(fragmentshadersource);
    fragmentshadersource = nullptr;

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.

    if (!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        error("Fragment shader compilation failed: %s", infoLog);
        return;
    }
}


Shader2D::~Shader2D()
{};


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


// ========================
// |       Texture        |
// ========================


/**
 * 
 * @param ImagePath The path to the image relative to the program.
 * @param MinifyFilter The filtering method used when the image is displayed smaller.
 * @param MagnifyingFilter The filtering method used when the image is displayed larger.
 * @param Border Controls how the texture behaves outside its normal UV range.
 * @param RGBA When it's true the image will use RGBA when its false it will use RGB.
*/
void Texture2D::LoadTexture2D(const char *ImagePath, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(ImagePath, &width, &height, &nrChannels, RGBA ? 4 : 3);

    if (!data)
    {
        error("Failed to Load texture!");
        error("STBI reason: %s", stbi_failure_reason());
        return;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
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
        }
        stbi_image_free(data);
    }

    rendering("Loaded texture");
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
void Texture2D::LoadEmbeddedTexture2D(const char *ImageData, size_t ImageSize, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load_from_memory((const stbi_uc*)ImageData, ImageSize, &width, &height, &nrChannels, RGBA ? 4 : 3);

    if (!data)
    {
        error("Failed to Load texture!");
        error("STBI reason: %s", stbi_failure_reason());
        return;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
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
    }
    else 
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    rendering("Loaded texture");
};


//LoadTextureMesh(Color(0.0f, 0.0f, 0.0f, 255.0f), "src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert", "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag", SquareVertices, sizeof(SquareVertices), SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]), false);
void Texture2D::LoadTextureMesh(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor)
{
    SizeOfMeshIndices = MeshIndicesSize / MeshIndicesArraySize;
    rendering("Loading the texture mesh");
    strcpy(VertexShader, VertexShaderPath);
    strcpy(FragmentShader, FragmentShaderPath);
    Shader2D Shader;
    Shader.CreateShader2D((char*)VertexShaderPath, (char*)FragmentShaderPath);
    CreateVAO(&Texture2DVAO);
    CreateVBO(Vertices, VerticesSize, &Texture2DVBO, PerVertexColor, true, 0, {255.0f, 0.0f, 255.0f, 255.0f}, true);
    CreateEBO(MeshIndices, MeshIndicesSize, &Texture2DEBO);
    ShaderProgram(&Texture2DShader, Shader.VertexShader, Shader.FragmentShader);
}


void Texture2D::drawtexture2D(size_t ShapeIndicesSize)
{
    glUseProgram(Texture2DShader);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(Texture2DShader, "texture1"), 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(Texture2DVAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, ShapeIndicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Texture2D::UnloadTexture()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (texture != 0)
        {
            DestroyShader(Texture2DShader);
            DestroyVAO(Texture2DVAO);
            DestroyVBO(Texture2DVBO);
            DestroyEBO(Texture2DEBO);
            glDeleteTextures(1, &texture);
            texture = 0;
        }
        else
        {
            warning("The texture is already been unloaded!");
        }
    }
    else
    {
        warning("Cannot unload texture because the rendering engine is not initialized!");
    }
    rendering("Unloaded the texture");
}


Texture2D::~Texture2D()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (texture != 0)
        {
            DestroyShader(Texture2DShader);
            DestroyVAO(Texture2DVAO);
            DestroyVBO(Texture2DVBO);
            DestroyEBO(Texture2DEBO);
            glDeleteTextures(1, &texture);
            texture = 0;
        }
    }
    else
    {
        warning("Cannot unload texture because the rendering engine is not initialized!");
    }
    rendering("Unloaded the texture");
};


// ========================
// |          2D          |
// ========================


void Shape2D::LoadShape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor)
{
    strcpy(VertexShader, VertexShaderPath);
    strcpy(FragmentShader, FragmentShaderPath);
    Shader2D Shader;
    Shader.CreateShader2D((char*)VertexShaderPath, (char*)FragmentShaderPath);
    CreateVAO(&Shape2DVAO);
    CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor, false, 0, {0.0f,0.0f,0.0f,255.0f}, true);
    CreateEBO(ShapeIndices, ShapeIndicesSize, &Shape2DEBO);
    ShaderProgram(&Shape2DShader, Shader.VertexShader, Shader.FragmentShader);
    glUseProgram(Shape2DShader);
    if (!PerVertexColor){glUniform4f(glGetUniformLocation(Shape2DShader, "color"), color.r, color.g, color.b, color.a);}
}


void Shape2D::LoadEmbeddedShape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor)
{
    strcpy(VertexShader, VertexShaderPath);
    strcpy(FragmentShader, FragmentShaderPath);
    Shader2D Shader;
    Shader.CreateShader2D((char*)VertexShaderPath, (char*)FragmentShaderPath);
    CreateVAO(&Shape2DVAO);
    CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor, false, 0, {0.0f,0.0f,0.0f,255.0f}, true);
    CreateEBO(ShapeIndices, ShapeIndicesSize, &Shape2DEBO);
    ShaderProgram(&Shape2DShader, Shader.VertexShader, Shader.FragmentShader);
    glUseProgram(Shape2DShader);
    glUniform4f(glGetUniformLocation(Shape2DShader, "color"), color.r, color.g, color.b, color.a);
}


void Shape2D::DrawShape2D(size_t ShapeIndicesSize)
{
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUseProgram(Shape2DShader);
    glBindVertexArray(Shape2DVAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, ShapeIndicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Shape2D::UnloadShape2D()
{
    DestroyShader(Shape2DShader);
    DestroyVAO(Shape2DVAO);
    DestroyVBO(Shape2DVBO);
    DestroyEBO(Shape2DEBO);
    rendering("Destroyed the Shapes resources");
}


Shape2D::~Shape2D()
{
    DestroyShader(Shape2DShader);
    DestroyVAO(Shape2DVAO);
    DestroyVBO(Shape2DVBO);
    DestroyEBO(Shape2DEBO);
    rendering("Destroyed the Shapes resources");
}


// ========================
// |        Shapes        |
// ========================

// Destroys the triangle resources.
Triangle::~Triangle()
{
}


// Destroys the Square resources.
Square::~Square()
{
}

// ========================
// |          3D          |
// ========================
