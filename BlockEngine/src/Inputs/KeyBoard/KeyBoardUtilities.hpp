#pragma once

class BlockWindow;

#include "../../Rendering/RenderingUtilities.hpp"

bool KeyEvent(int key, int event);
void InitializeInput(BlockWindow *Window);
void UpdateInput(BlockWindow *Window);