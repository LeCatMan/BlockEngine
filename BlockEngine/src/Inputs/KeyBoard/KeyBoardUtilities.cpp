#include "KeyBoardUtilities.hpp"
#include "../../Rendering/RenderingUtilities/RenderingUtilities.hpp"
#include <stdio.h>

int ExitKey;
static bool previousState[GLFW_KEY_LAST + 1] = {};
static bool currentState[GLFW_KEY_LAST + 1] = {};


void InitializeInput()
{
    glfwSetInputMode(Bwindow, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void UpdateInput()
{
    glfwPollEvents();
    for (int key = 0; key <= GLFW_KEY_LAST; ++key)
    {
        previousState[key] = currentState[key];
        currentState[key] = glfwGetKey(Bwindow, key) == GLFW_PRESS;
    }
}

// check if a key event was activated
// you can use the event to specify the action (Press,Release,repeat)
bool KeyEvent(int key, int event)
{
    if (key < 0 || key > GLFW_KEY_LAST)
        return false;

    bool triggered = false;

    switch (event)
    {
        case BLOCK_PRESS:
            triggered = currentState[key] && !previousState[key];
            break;

        case BLOCK_RELEASE:
            triggered = !currentState[key] && previousState[key];
            break;

        case BLOCK_REPEAT:
            triggered = currentState[key] && previousState[key];
            break;
    }

    return triggered;
}

// if the key chosen was activated it will close the window.
void SetExitKey(int key)
{
    ExitKey = key;
}
