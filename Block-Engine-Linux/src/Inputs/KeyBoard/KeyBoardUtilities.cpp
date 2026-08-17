#include "KeyBoardUtilities.hpp"
#include "../../Rendering/RenderingUtilities/RenderingUtilities.hpp"
#include <stdio.h>

int ExitKey;

// check if a key event was activated
// you can use the event to specify the action (Press,Release)
bool KeyEvent(int key, int event)
{
    return glfwGetKey(Bwindow, key) == event;
}


// if the key chosen was activated it will close the window.
void SetExitKey(int key)
{
    ExitKey = key;
}
