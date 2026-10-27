#pragma once

#include "../../Inputs/Inputs.hpp"
#include "../Color/Color.hpp"
#include "../../Debugger/Utilities/Utilities.hpp"
// glad + glfw
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

// this is a GLFWwindow and not a class please check the name before using because
// you might use BlockWindow which is a class.
using Blockwindow = GLFWwindow;

using BlockMonitor = GLFWmonitor;

// this is BlockWindow and not a window please check the name before using because
// you might use Blockwindow which is a GLFWwindow.
class BlockWindow
{
private:
    bool Isloaded = false;
public:
    int ExitKey = BLOCK_KEY_ESCAPE;
    Blockwindow *Window = nullptr;
    BlockMonitor *Monitor = nullptr;
    BlockResult CreateWindow(int WindowWidth, int WindowHeight, const char *WindowTitle, int Exitkey, bool VSync, int ImageCount, GLFWimage *Image);
    BlockResult CloseWindow();
    BlockResult WindowShouldClose();
    void UpdateWindow();
    void MakeCurrentWindowContext();
    BlockResult BackGroundColor(Color color);
    ~BlockWindow();

    BlockWindow() = default;
    BlockWindow(const BlockWindow&) = delete;
    BlockWindow& operator=(const BlockWindow&) = delete;
    BlockWindow(BlockWindow&&) = delete;
    BlockWindow& operator=(BlockWindow&&) = delete;
};


