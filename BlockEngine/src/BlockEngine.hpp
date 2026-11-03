#pragma once
#include "Rendering/RenderingUtilities.hpp"
#include "Debugger/Debugger.hpp"
#include "Audio/Audio.hpp"
#include "Inputs/Inputs.hpp"


/**
 * Initialize Block Engine
 * 
 * Initializes the Debugger, Rendring, Input, and Audio systems.
 *
 * @param Volume Master volume.
 *
 * Example:
 *     InitializeBlockEngine(1.0f);
 */
inline BlockResult InitializeBlockEngine(float Volume)
{
    if (InitializeLogger() < 0)
    {
        printf("[\033[1m99h 99m 99s AM\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", "1" ";" "5" ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Couldn't initialize logger");
        return BLOCK_ERR_INIT_FAILED;
    }
    info("Launching BlockEngine");
    if (InitializeRenderingEngine() < 0)
    {
        error("Couldn't initialize Rendering Engine");
        return BLOCK_ERR_INIT_FAILED;
    }
    if (InitializeAudioEngine(Volume) < 0)
    {
        error("Couldn't initialize Audio Engine");
        return BLOCK_ERR_INIT_FAILED;
    }
    GetCurrentRunningPath();
    info("Launched BlockEngine");
    return BLOCK_SUCCESS_TRUE;
}

/**
 * Shutdown Block Engine
 * ---------------------
 * Shuts down the Block Engine systems and closes the program.
 */
inline BlockResult ShutDownBlockEngine()
{
    info("Closing Program");
    if (ShutDownRenderingEngine() < 0)
    {
        printf("[\033[1m99h 99m 99s AM\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", "1" ";" "5" ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Couldn't Shutdown rendeing engine");
        return BLOCK_FAILURE;
    }
    if (AudioShutDown() < 0)
    {
        printf("[\033[1m99h 99m 99s AM\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", "1" ";" "5" ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Couldn't Shutdown Audio");
        return BLOCK_FAILURE;
    }
    info("Closed Program");
    if (ShutDownLogger() < 0)
    {
        printf("[\033[1m99h 99m 99s AM\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", "1" ";" "5" ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Couldn't Shutdown logger");
        return BLOCK_FAILURE;
    }
    return BLOCK_SUCCESS_TRUE;
}


