#pragma once

#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"
#include "../../Debugger/Logger/Logger.hpp"
#include "../../Audio/Audio.hpp"
#include "../../Debugger/Utilities/Utilities.hpp"
#include "../../Inputs/Inputs.hpp"
#include "../RenderingEngine/RenderingEngine.hpp"
#include "../Color/Color.hpp"
#include "../RenderingUtilities.hpp"


// this is a GLFWwindow and not a class please check the name before using because
// you might use BlockWindow which is a class.
using Blockwindow = GLFWwindow;

using BlockMonitor = GLFWmonitor;


double GetTime();


// this is BlockWindow and not a window please check the name before using because
// you might use Blockwindow which is a GLFWwindow.
class BlockWindow
{
private:
    bool Isloaded = false;
protected:
    void framebuffersizecallback(GLFWwindow *Window, int WindowWidth, int WindowHeight);
public:
    int ExitKey = BLOCK_KEY_ESCAPE;
    Blockwindow *Window = nullptr;
    BlockMonitor *Monitor = nullptr;
    int Width = 0, Height = 0;
    float Aspect();

    BlockResult CreateWindow(int WindowWidth, int WindowHeight, const char *WindowTitle, int Exitkey, bool VSync, int ImageCount, GLFWimage *Image);
    BlockResult CloseWindow();
    BlockResult WindowShouldClose();
    void UpdateWindow();
    


    // States
    // Set
    BlockResult SetBackgroundColor(Color color);
    void MakeCurrentWindowContext();
    void SetWindowPosition(int X, int Y)
    {
        glfwSetWindowPos(Window, X, Y);
    }
    void SetWindowIcon(int ImageCount, GLFWimage *Image)
    {
        glfwSetWindowIcon(Window, ImageCount, Image);
    }
    void SetWindowSize(int WindowWidth, int WindowHeight)
    {
        glfwSetWindowSize(Window, WindowWidth, WindowHeight);
    }
    void SetWindowOpacity(float Opacity)
    {
        if (Opacity > -1 && Opacity < 256)
        {
            glfwSetWindowOpacity(Window, Opacity/255);
        }
        else
        {
            Opacity = 0;
            error("Color value over or under the limit which is 255");
        }
    }
    void SetWindowTitle(const char *Title)
    {
        glfwSetWindowTitle(Window, Title);
    }
    void RestoreWindow()
    {
        glfwRestoreWindow(Window);
    }


    // Get
    const char *GetWindowTitle()
    {
        return glfwGetWindowTitle(Window);
    }
    /**
     * @param WindowWidth this is where to store the width
     * @param WindowHeight this is where to store the height 
     */
    void GetWindowSize(int *WindowWidth, int *WindowHeight)
    {
        glfwGetWindowSize(Window, WindowWidth, WindowHeight);
    }
    float GetWindowOpacity()
    {
        return glfwGetWindowOpacity(Window) * 255.0f;
    }
    /**
     * @param X this is where to store the width
     * @param Y this is where to store the height 
     */
    void GetCursorPosition(double *X, double *Y)
    {
        if (Isloaded)
        {
            glfwGetCursorPos(Window, X, Y);
        }
        else
        {
            *X = 0.0;
            *Y = 0.0;   // give callers a defined value instead of leaving them untouched
        }
    }


    // Show/Hide
    void HideWindow()
    {
        glfwHideWindow(Window);
    }
    void ShowWindow()
    {
        glfwShowWindow(Window);
    }


    // destructor 
    ~BlockWindow();

    // Something
    BlockWindow() = default;
    BlockWindow(const BlockWindow&) = delete;
    BlockWindow& operator=(const BlockWindow&) = delete;
    BlockWindow(BlockWindow&&) = delete;
    BlockWindow& operator=(BlockWindow&&) = delete;
    friend void FrameBufferSizeCallback(GLFWwindow *window, int WindowWidth, int WindowHeight);
};


