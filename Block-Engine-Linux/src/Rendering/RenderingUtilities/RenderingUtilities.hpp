#ifndef RENDERINGUTILITIES_HPP
#define RENDERINGUTILITIES_HPP
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

extern GLFWwindow* Bwindow;
extern const char *TestFragmentShaderSource;
extern const char *TestVertexShaderSource;
extern float TriangleVertices[26];
extern float SquareVertices[12];
extern const unsigned int SquareIndices[6];
extern const unsigned int TriangleIndices[3];
extern float TrianglePerVertexColorVertices[18];

struct Color
{
    float r;
    float g;
    float b;

    Color(float r, float g, float b)
    {
        this->r = r / 255.0f;
        this->g = g / 255.0f;
        this->b = b / 255.0f;
    }
};

// ########################
// #          2D          #
// ########################

class Shader2D
{
    private:
    char *vertexshadersource;
    char *fragmentshadersource;
    public:
    unsigned int VertexShader;
    unsigned int FragmentShader;
    Shader2D(char *VertexShaderSourcePath, char *fragmentShaderSourcePath);
    ~Shader2D();
};

// Common 2D objects
class Shape2D
{
    protected:
        char VertexShader[256];
        char FragmentShader[256];
        unsigned int Shape2DVAO;
        unsigned int Shape2DVBO;
        unsigned int Shape2DEBO;
        unsigned int Shape2DShader;
    public:
        Shape2D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, bool PerVertexColor, bool HasTexture);
        ~Shape2D();
        void DrawShape2D(size_t ShapeIndicesSize);
};

class Texture
{
    public:

};

// Triangle
class Triangle : public Shape2D
{
public:
    Triangle(Color color): Shape2D(color, "src/Data/Shaders/BasicPerVertexVertexShader.vert", "src/Data/Shaders/BasicPerVertexFragmentShader.frag", TrianglePerVertexColorVertices, sizeof(TrianglePerVertexColorVertices), TriangleIndices, sizeof(TriangleIndices), true, false)
    {}
    
    ~Triangle();

    // Draws the triangle.
    void DrawTriangle()
    {
        DrawShape2D(sizeof(TriangleIndices) / sizeof(TriangleIndices[0]));
    }

};

// square
class Square : public Shape2D
{
    public:
    
        Square(Color color): Shape2D(color, "src/Data/Shaders/BasicVertexShader.vert", "src/Data/Shaders/BasicFragmentShader.frag", SquareVertices, sizeof(SquareVertices), SquareIndices, sizeof(SquareIndices), false, false)
        {}
        
        ~Square();

        // Draws the square.
        void DrawSquare()
        {
            DrawShape2D(sizeof(SquareIndices) / sizeof(SquareIndices[0]));
        }
};

// ########################
// #          3D          #
// ########################

// Common 3D objects
class Shape3D
{
    protected:
        unsigned int Shape3DVAO;
        unsigned int Shape3DVBO;
        unsigned int Shape3DEBO;
        unsigned int Shape3DShader;
    public:
        //Shape3D(Color color, const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize);
        //~Shape3D();
        //void DrawShape3D(size_t ShapeIndicesSize);
};


int InitializeWindow(int WindowWidth,int WindowHeight,const char *WindowTitle);
void UpdateWindow();
bool WindowShouldClose();
void CloseWindow();
void BackGroundColor(Color color, int opacity);
void RenderingShutDown();


//void DrawTriangle();
//void CreateTriangle(Color color);
//void DestroyTriangle();
//void DrawSquare();
//void CreateSquare(Color color);
//void DestroySquare();


#endif
