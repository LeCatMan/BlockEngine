#pragma once
#include "Rendering/RenderingUtilities/RenderingUtilities.hpp"
#include "Debugger/Debugger.hpp"
#include "Audio/Audio.hpp"
#include "Inputs/Inputs.hpp"


/**
 * Initialize Block Engine
 * -----------------------
 * Initializes the Logger, Window, Input, and Audio systems,
 * and sets the key used to exit the engine.
 *
 * @param width Window width.
 * @param height Window height.
 * @param title Window title.
 * @param exit_key Key used to exit the engine.
 * @param volume Master volume.
 *
 * Example:
 *     InitializeBlockEngine(800, 600, "Test", BLOCK_KEY_ESCAPE);
 */
inline void InitializeBlockEngine(int WindowWidth, int WindowHeight, const char *WindowTitle, int ExitKey, float volume)
{
    LoggerInit();
    info("Launching BlockEngine");
    InitializeWindow(WindowWidth,WindowHeight, WindowTitle);
    InitializeInput();
    SetExitKey(ExitKey);
    InitializeAudio(volume);
}

/**
 * Shutdown Block Engine
 * ---------------------
 * Shuts down the Block Engine systems and closes the program.
 *
 * Example:
 *     ShutdownBlockEngine();
 */
inline void ShutdownBlockEngine()
{
    info("Closing Program");

    RenderingShutDown();
    AudioShutdown();

    info("Closed Program");

    LoggerShutdown();
}