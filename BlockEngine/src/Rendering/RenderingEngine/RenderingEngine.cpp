#include "RenderingEngine.hpp"
// glad + glfw
#include "../../../external/glad/include/glad/glad.h"
#include "../../../external/glfw-3.5.1/include/GLFW/glfw3.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


bool RenderingInitialized = BLOCK_SUCCESS_FALSE;


BlockResult InitializeRenderingEngine()
{
    if (RenderingInitialized == BLOCK_SUCCESS_FALSE)
    {
        #pragma region load glad and glfw

        if (!glfwInit())
        {
            error("Failed to initialize GLFW");
            RenderingInitialized = BLOCK_SUCCESS_FALSE;
            return BLOCK_ERR_INIT_FAILED;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #pragma endregion

        rendering("Rendering engine initialized!");
        RenderingInitialized = BLOCK_SUCCESS_TRUE;
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        warning("Cannot initialize the engine because the engine is already initialized");
        return BLOCK_FAILURE;
    }
}


BlockResult RenderingShutdown()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        RenderingInitialized = BLOCK_SUCCESS_FALSE;
        rendering("Rendering engine shutdown!");
        glfwTerminate();
        rendering("Shutingdown the Rendering Engine!");
        return BLOCK_SUCCESS_TRUE;
    }
    else 
    {
        RenderingInitialized = BLOCK_SUCCESS_FALSE;
        warning("Cannot close the ENgine because the rendering engine is not Initialized");
        return BLOCK_FAILURE;
    }

}

