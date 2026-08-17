#define STB_IMAGE_IMPLEMENTATION
#include "../../../external/stb-master/stb_image.h"

#include "RenderingUtilities.hpp"


// ########################
// #      Window Stuff    #
// ########################


GLFWwindow* Bwindow;

void framebuffer_size_callback(GLFWwindow* Bwindow, int WindowWidth, int WindowHeight)
{
    glViewport(0, 0, WindowWidth, WindowHeight);
}  


// Initialize the rendering engine with default settings.
int InitializeWindow(int WindowWidth,int WindowHeight,const char *WindowTitle)
{
    if (!glfwInit())
    {
        error("Failed to initialize GLFW");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Bwindow = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

    
    if (Bwindow == NULL)
    {
        error("Failed to create GLFW window");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(Bwindow);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        error("Failed to initialize GLAD");
        return 1;
    }
    
    glfwSetFramebufferSizeCallback(Bwindow, framebuffer_size_callback);
    
    return 0;
}


// Closes the window ? what did you expect ;) .
void CloseWindow()
{
    glfwSetWindowShouldClose(Bwindow,true);
}


// Clean up and shutdown engine.
void RenderingShutDown()
{
    glfwTerminate();
}


// Changes the background color.
void BackGroundColor(Color color, int opacity)
{
    glClearColor((color.r), (color.g), (color.b), (opacity/255));
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
    if (KeyEvent(ExitKey,BLOCK_PRESS))
    {CloseWindow();}
    
    glfwSwapBuffers(Bwindow);// Swaps the front and back buffers of the specified window.
    glfwPollEvents();// Processes all pending events.
}


// ########################
// #       Examples       #
// ########################


float TrianglePerVertexColorVertices[18] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

float TriangleVertices[26] = {
    // positions         // colors          // uv
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f // top 
};

float SquareVertices[12] = {
    -0.5f, -0.5f, 0.0f, // bottom left
     0.5f, -0.5f, 0.0f, // bottom right
    -0.5f,  0.5f, 0.0f, // top left
     0.5f,  0.5f, 0.0f  // top right
};

const unsigned int SquareIndices[6] = {
    0, 1, 2,
    1, 3, 2
}; 

const unsigned int TriangleIndices[3] = {
    0,1,2
};

// ########################
// #      Low Level       #
// ########################


// ########################
// #      Rendering       #
// ########################





//Create a fragment and vertex shader with custom shader code.
Shader2D::Shader2D(char *VertexShaderSourcePath, char *fragmentShaderSourcePath)
{
    vertexshadersource = GetFileText(VertexShaderSourcePath);
    VertexShader = glCreateShader(GL_VERTEX_SHADER); // creating the vertex shader.
    glShaderSource(VertexShader, 1, &vertexshadersource, NULL);   // addes the source to the shader.
    glCompileShader(VertexShader);                                // compiles the shader ?
    int success;
    char infoLog[512];
    char buffer[548];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.
    if (!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        snprintf(buffer, sizeof(buffer), "Vertex shader compilation failed: %s", infoLog);
        error(buffer);
    }

    fragmentshadersource = GetFileText(fragmentShaderSourcePath);
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentshadersource, NULL);
    glCompileShader(FragmentShader);
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success); // checks if the shader compiled successfully.
    if (!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        snprintf(buffer, sizeof(buffer), "Fragment shader compilation failed: %s", infoLog);
        error(buffer);
    }
}


Shader2D::~Shader2D()
{
    free(vertexshadersource);
    free(fragmentshadersource);
}


// Creates vertex array object.
void CreateVAO(unsigned int* VAO)
{
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
}


// Creates vertex buffer object.
void CreateVBO(const float* Vertices, size_t Size, unsigned int* VBO, bool PerVertexColor, bool texture)
{
    size_t stride =
        PerVertexColor && texture ? 8 * sizeof(float) :
        PerVertexColor            ? 6 * sizeof(float) :
        texture                    ? 5 * sizeof(float) :
                                    3 * sizeof(float);                 

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,(void*)0);

    if (PerVertexColor && !texture)
    {
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,stride,(void*)(3 * sizeof(float)));
    }
    
    if (texture)
    {

        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,stride,(void*)(PerVertexColor && texture ? 6 * sizeof(float) :3 * sizeof(float)));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        float TBC[3] = {1.0f, 0.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, TBC);
        
    }

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}


// Creates element buffer object.
void CreateEBO(const unsigned int* Indices, size_t Size, unsigned int* EBO)
{
    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
}


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


// Cleanup
void DestroyVBO(unsigned int VBO)
{
    glDeleteBuffers(1, &VBO);
}
void DestroyVAO(unsigned int VAO)
{
    glDeleteVertexArrays(1, &VAO);
}
void DestroyEBO(unsigned int EBO)
{
    glDeleteBuffers(1, &EBO);
}
void DestroyShader(unsigned int Shader)
{
    glDeleteProgram(Shader);
}


// ########################
// #          2D          #
// ########################

// Creates the Shapes resources.
// it should look like this (Shape(color, TestVertexShaderSource, TestFragmentShaderSource, TriangleVertices, sizeof(TriangleVertices), TriangleIndices, sizeof(TriangleIndices, false)))
Shape2D::Shape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor, bool HasTexture)
{
    strcpy(VertexShader, VertexShaderPath);
    strcpy(FragmentShader, FragmentShaderPath);
    Shader2D Shader(VertexShader,FragmentShader);
    CreateVAO(&Shape2DVAO);
    CreateVBO(Vertices, VerticesSize, &Shape2DVBO, PerVertexColor , HasTexture);
    CreateEBO(ShapeIndices, ShapeIndicesSize, &Shape2DEBO);
    ShaderProgram(&Shape2DShader, Shader.VertexShader, Shader.FragmentShader);
    glUseProgram(Shape2DShader);
    glUniform3f(glGetUniformLocation(Shape2DShader, "color"), color.r, color.g, color.b);
}


// Draws the the shape.
void Shape2D::DrawShape2D(size_t ShapeIndicesSize)
{    
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    info("Destroyed the Shapes resources");
}


// ########################
// #       Triangle       #
// ########################


// Destroys the triangle resources.
Triangle::~Triangle()
{
}

// ########################
// #       Square       #
// ########################

// Destroys the Square resources.
Square::~Square()
{
}


// ########################
// #          3D          #
// ########################

