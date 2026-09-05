#define STB_IMAGE_IMPLEMENTATION
#include "../../../external/stb-master/stb_image.h"
#include "../../Debugger/Utilities/Utilities.hpp"
#include "RenderingUtilities.hpp"

// ########################
// #      Window Stuff    #
// ########################

GLFWwindow *Bwindow;
GLFWmonitor *Monitor;

// Update the viewport to match the window size.
void FrameBufferSizeCallback(GLFWwindow *Bwindow, int WindowWidth, int WindowHeight)
{
    //         x  y    width        height
    glViewport(0, 0, WindowWidth, WindowHeight);
}

// Initialize the rendering engine with default settings.
int InitializeWindow(int WindowWidth, int WindowHeight, const char *WindowTitle, bool VSync)
{
    if (!glfwInit())
    {
        error("Failed to initialize GLFW");
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
        return BLOCK_ERR_INIT_FAILED;
    }
    glfwMakeContextCurrent(Bwindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        error("Failed to initialize GLAD");
        return BLOCK_ERR_INIT_FAILED;
    }

    glfwSetFramebufferSizeCallback(Bwindow, FrameBufferSizeCallback);
    
    Monitor = glfwGetPrimaryMonitor();
    if (Monitor == NULL)
    {
        error("Couldn't get the monitor");
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
    rendering("Rendering engine initialized!");
    return BLOCK_SUCCESS_TRUE;
}

// Closes the window ? what did you expect ;) .
void CloseWindow()
{
    glfwSetWindowShouldClose(Bwindow, true);
}

// Clean up and shutdown engine.
void RenderingShutdown()
{
    #pragma region just shutting down
    rendering("Rendering engine shutdown!");
    glfwTerminate();
    #pragma endregion
}

// Changes the background color.
void BackGroundColor(Color color, int opacity)
{
    glClearColor((color.r), (color.g), (color.b), (opacity / 255.0f));
    glClear(GL_COLOR_BUFFER_BIT);
}

// Checks the close flag of the specified window.
bool WindowShouldClose()
{
    return glfwWindowShouldClose(Bwindow);
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
// |       Texture        |
// ========================

//GL_NEAREST_MIPMAP_NEAREST
void Texture::CreateTexture(const char *ImagePath, GLint MinifyFilter, GLint MagnifyingFilter)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinifyFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagnifyingFilter);

    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(ImagePath, &width, &height, &nrChannels, 0);

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

//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
void Texture::LoadTexture(Shape2D& shape)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(shape.Shape2DVAO);
};

void Texture::UnloadTexture()
{
    if (texture != 0)
    {
        glDeleteTextures(1, &texture);
        texture = 0;
    }
    else
    {
        warning("The texture is already been unloaded!");
    }
}

Texture::~Texture()
{
    if (texture != 0)
    {
        UnloadTexture();
    }
};


// ========================
// |       Shader2D       |
// ========================

// Create a fragment and vertex shader with custom shader code.
Shader2D::Shader2D(char *VertexShaderSourcePath, char *FragmentShaderSourcePath)
{
    vertexshadersource = GetFileText(VertexShaderSourcePath);

    if(!vertexshadersource)
    {
        error("Invalid Path (VertexShaderSourcePath)");
        return;
    }

    VertexShader = glCreateShader(GL_VERTEX_SHADER);            // creating the vertex shader.
    glShaderSource(VertexShader, 1, &vertexshadersource, NULL); // addes the source to the shader.
    glCompileShader(VertexShader);                              // compiles the shader ? ;)
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

Shader2D::~Shader2D()
{};


// ========================
// |         VAO          |
// ========================

// Creates vertex array object.
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

// Creates vertex buffer object.
void CreateVBO(const float *Vertices, size_t Size, unsigned int *VBO, bool PerVertexColor, bool texture)
{
    size_t stride =
        PerVertexColor && texture ? 8 * sizeof(float)
        : PerVertexColor ? 6 * sizeof(float)
        : texture          ? 5 * sizeof(float)
        : 3 * sizeof(float);

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);

    if (PerVertexColor && !texture)
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
    }

    if (texture)
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(PerVertexColor && texture ? 6 * sizeof(float) : 3 * sizeof(float)));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float TBC[4] = {1.0f, 0.0f, 1.0f, 1.0f};// this is the color of the texture
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, TBC);
    }

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void DestroyVBO(unsigned int VBO)
{
    glDeleteBuffers(1, &VBO);
}

// ========================
// |         EBO          |
// ========================

// Creates element buffer object.
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

// this is were we attach and link things to the program.
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
// |       Cleanup        |
// ========================











// ========================
// |          2D          |
// ========================

// Creates the Shapes resources.
// it should look like this
// "Shape2D(color, "src/Assets/Shaders/BasicPerVertexVertexShader.vert", "src/Assets/Shaders/BasicPerVertexFragmentShader.frag", TrianglePerVertexColorVertices, sizeof(TrianglePerVertexColorVertices), TriangleIndices, sizeof(TriangleIndices), true, false)"
Shape2D::Shape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor, bool HasTexture)
{
    strcpy(VertexShader, VertexShaderPath);
    strcpy(FragmentShader, FragmentShaderPath);
    Shader2D Shader(VertexShader, FragmentShader);
    CreateVAO(&Shape2DVAO);
    CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor, HasTexture);
    CreateEBO(ShapeIndices, ShapeIndicesSize, &Shape2DEBO);
    ShaderProgram(&Shape2DShader, Shader.VertexShader, Shader.FragmentShader);
    glUseProgram(Shape2DShader);
    glUniform3f(glGetUniformLocation(Shape2DShader, "color"), color.r, color.g, color.b);
}

// Draws the the shape.
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

// Destroys the Shapes resources.
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
