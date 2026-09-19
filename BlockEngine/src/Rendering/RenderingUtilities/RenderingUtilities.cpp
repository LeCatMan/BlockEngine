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

const float TrianglePerVertexColor[18] = {
    // bottom right vertex
   // positions               
   //  x  |  y  |  z  |
     0.5f, -0.5f, 0.0f,
   // colors
   //|  r  |  g  |  b  |
      1.0f, 0.0f, 0.0f,

    // bottom left vertex
   // positions               
   //  x  |  y  |  z  |
    -0.5f, -0.5f, 0.0f,
   // colors
   //|  r  |  g  |  b  |
      0.0f, 1.0f, 0.0f,

    // top vertex
   // positions               
   //  x  |  y  |  z  |
     0.0f, 0.5f, 0.0f,
   // colors
   //|  r  |  g  |  b  |
      0.0f, 0.0f, 1.0f
};

const float TrianglePosColorUV[24] = {
    // bottom right vertex
   // positions               
   //  x  |  y  |  z  |
     0.5f, -0.5f, 0.0f
   // colors
   //|  r  |  g  |  b  |
    , 1.0f, 0.0f, 0.0f
   // uv
   //|  x  |  y  |
    , 0.0f, 0.0f,


   // bottom left vertex

   // positions               
   //  x  |  y  |  z  |
    -0.5f, -0.5f, 0.0f
   // colors
   //|  r  |  g  |  b  |
    , 0.0f, 1.0f, 0.0f
   // uv
   //|  x  |  y  |
    , 1.0f, 0.0f,


    // top vertex

   // positions               
   //  x  |  y  |  z  |
     0.0f,  0.5f, 0.0f
   // colors
   //|  r  |  g  |  b  |
    , 0.0f, 0.0f, 1.0f
   // uv
   //|  x  |  y  |
    , 0.5f, 1.0f,
};

const float TriangleVertices[9] = {
    // bottom right vertex
   // positions               
   //  x  |  y  |  z  |
     0.5f, -0.5f, 0.0f,

    // bottom left vertex
   // positions               
   //  x  |  y  |  z  |
    -0.5f, -0.5f, 0.0f,

    // top vertex
   // positions               
   //  x  |  y  |  z  |
     0.0f, 0.5f, 0.0f,
};

const unsigned int TriangleIndices[3] = {
    0, 1, 2
};

const float SquarePerVertexColor[24] = {
    // bottom left vertex
   // positions               
   //  x  |  y  |  z  |
    -0.5f, -0.5f, 0.0f,
   // colors
   //|  r  |  g  |  b  |
      1.0f, 0.0f, 0.0f,

    // bottom right vertex
   // positions               
   //  x  |  y  |  z  |
     0.5f, -0.5f, 0.0f,
   // colors
   //|  r  |  g  |  b  |
      0.0f, 1.0f, 0.0f,

    // top left vertex
   // positions               
   //  x  |  y  |  z  |
    -0.5f,  0.5f, 0.0f,
   // colors
   //|  r  |  g  |  b  |
      0.0f, 0.0f, 1.0f,

    // top right vertex
   // positions               
   //  x  |  y  |  z  |
     0.5f,  0.5f, 0.0f,
   // colors
   //|  r  |  g  |  b  |
      1.0f, 1.0f, 0.0f
};

const float SquarePosColorUV[32] = {
    // bottom left vertex
   // positions               
   //  x  |  y  |  z  |
    -0.5f, -0.5f, 0.0f
   // colors
   //|  r  |  g  |  b  |
    , 1.0f, 0.0f, 0.0f
   // uv
   //|  x  |  y  |
    , 0.0f, 0.0f,


    // bottom right vertex

   // positions               
   //  x  |  y  |  z  |
     0.5f, -0.5f, 0.0f
   // colors
   //|  r  |  g  |  b  |
    , 0.0f, 1.0f, 0.0f
   // uv
   //|  x  |  y  |
    , 1.0f, 0.0f,


    // top left vertex

   // positions               
   //  x  |  y  |  z  |
    -0.5f,  0.5f, 0.0f
   // colors
   //|  r  |  g  |  b  |
    , 0.0f, 0.0f, 1.0f
   // uv
   //|  x  |  y  |
    , 0.0f, 1.0f,


    // top right vertex

   // positions               
   //  x  |  y  |  z  |
     0.5f,  0.5f, 0.0f
   // colors
   //|  r  |  g  |  b  |
    , 1.0f, 1.0f, 0.0f
   // uv
   //|  x  |  y  |
    , 1.0f, 1.0f,
};

const float SquareVertices[12] = {
    // bottom left vertex
   // positions               
   //  x  |  y  |  z  |
    -0.5f, -0.5f, 0.0f,

    // bottom right vertex
   // positions               
   //  x  |  y  |  z  |
     0.5f, -0.5f, 0.0f,

    // top left vertex
   // positions               
   //  x  |  y  |  z  |
    -0.5f,  0.5f, 0.0f,

    // top right vertex
   // positions               
   //  x  |  y  |  z  |
     0.5f,  0.5f, 0.0f
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


void CreateVBO(const float *Vertices, size_t VerticesSize, unsigned int *VBO, bool PerVertexColor, bool texture, size_t Stride, Color BorderColor)
{
    if (Stride == 0)
    {
        Stride = (3 + (PerVertexColor ? 3 : 0) + (texture ? 2 : 0)) * sizeof(float);
    }

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, VerticesSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Stride, (void *)0);
    glEnableVertexAttribArray(0);

    if (PerVertexColor)
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Stride, (void *)(3 * sizeof(float)));
    }

    if (texture)
    {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Stride, (void *)((3 + (PerVertexColor ? 3 : 0)) * sizeof(float)));

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


void Texture::LoadTexture(const char *ImagePath, GLint MinifyFilter, GLint MagnifyingFilter)
{
    rendering("Loading texture");
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinifyFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagnifyingFilter);

    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(ImagePath, &width, &height, &nrChannels, 4);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        error("Failed to generate texture!");
    }

    stbi_image_free(data);
};


//LoadTextureMesh(Color(0.0f, 0.0f, 0.0f, 255.0f), "src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert", "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag", SquareVertices, sizeof(SquareVertices), SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]), false);
void Texture::LoadTextureMesh(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor)
{
    SizeOfMeshIndices = MeshIndicesSize / MeshIndicesArraySize;
    rendering("Loading the texture mesh");
    strcpy(VertexShader, VertexShaderPath);
    strcpy(FragmentShader, FragmentShaderPath);
    Shader2D Shader;
    Shader.CreateShader2D((char*)VertexShaderPath, (char*)FragmentShaderPath);
    CreateVAO(&Texture2DVAO);
    CreateVBO(Vertices, VerticesSize, &Texture2DVBO, PerVertexColor, true, 0, {0.0f,0.0f,0.0f,255.0f});
    CreateEBO(MeshIndices, MeshIndicesSize, &Texture2DEBO);
    ShaderProgram(&Texture2DShader, Shader.VertexShader, Shader.FragmentShader);
}


void Texture::drawtexture2D(size_t ShapeIndicesSize)
{
    glUseProgram(Texture2DShader);
    glUniform1i(glGetUniformLocation(Texture2DShader, "texture1"), 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(Texture2DVAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, ShapeIndicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Texture::UnloadTexture()
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


Texture::~Texture()
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
    CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor, false, 0, {0.0f,0.0f,0.0f,255.0f});
    CreateEBO(ShapeIndices, ShapeIndicesSize, &Shape2DEBO);
    ShaderProgram(&Shape2DShader, Shader.VertexShader, Shader.FragmentShader);
    glUseProgram(Shape2DShader);
    glUniform4f(glGetUniformLocation(Shape2DShader, "color"), color.r, color.g, color.b, color.a);
}


void Shape2D::LoadEmbeddedShape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor)
{
    strcpy(VertexShader, VertexShaderPath);
    strcpy(FragmentShader, FragmentShaderPath);
    Shader2D Shader;
    Shader.CreateShader2D((char*)VertexShaderPath, (char*)FragmentShaderPath);
    CreateVAO(&Shape2DVAO);
    CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor, false, 0, {0.0f,0.0f,0.0f,255.0f});
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
