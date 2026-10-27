class BlockWindow;
#include "KeyBoardUtilities.hpp"
#include <stdio.h>
#include "../Inputs.hpp"


static bool previousState[GLFW_KEY_LAST + 1] = {};
static bool currentState[GLFW_KEY_LAST + 1] = {};


void InitializeInput(BlockWindow *Window)
{
    glfwSetInputMode(Window->Window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void UpdateInput(BlockWindow *Window)
{
    glfwPollEvents();
    for (int key = 0; key <= GLFW_KEY_LAST; ++key)
    {
        previousState[key] = currentState[key];
        currentState[key] = glfwGetKey(Window->Window, key) == GLFW_PRESS;
    }
}

/** check if a key event was activated
 * BLOCK_PRESS if the key was pressed
 * BLOCK_RELEASE if the key was released
 * BLOCK_REPEAT if the key was held
*/
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
