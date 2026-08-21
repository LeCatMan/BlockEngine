#ifndef BLOCKENGINE_HPP
#define BLOCKENGINE_HPP
#include "Rendering/RenderingUtilities/RenderingUtilities.hpp"
#include "Debugger/Debugger.hpp"
#include "Audio/Audio.hpp"
#include "Inputs/Inputs.hpp"


/*
here we initialize the (Logger, Window, Input, Audio) and set the exit key
InitializeBlockEngine(800, 600, "Test", BLOCK_KEY_ESCAPE);
*/
inline void InitializeBlockEngine(int WindowWidth, int WindowHeight, const char *WindowTitle, int ExitKey)
{
    LoggerInit();
    info("Launching BlockEngine");
    InitializeWindow(WindowWidth,WindowHeight, WindowTitle);
    InitializeInput();
    SetExitKey(ExitKey);
    InitializeAudio();
}

inline void ShutdownBlockEngine()
{
    info("Closing Program");
    RenderingShutDown();
    AudioShutdown();
    info("Closed Program");
    LoggerShutdown();
}

#endif
