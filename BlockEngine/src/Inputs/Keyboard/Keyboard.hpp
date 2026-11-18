#pragma once

#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

using Blockwindow = GLFWwindow;
using BlockMonitor = GLFWmonitor;

bool KeyEvent(int key, int event);
void InitializeInput(Blockwindow *Window);
void UpdateInput(Blockwindow *Window);