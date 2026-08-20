#ifndef BLOCKENGINE_HPP
#define BLOCKENGINE_HPP

#include <stdio.h>
#include "Rendering/RenderingUtilities/RenderingUtilities.hpp"
#include "Debugger/Debugger.hpp"
#include "Audio/Audio.hpp"
#include "Inputs/Inputs.hpp"


inline void InitializeBlockEngine(int WindowWidth, int WindowHeight, const char *WindowTitle, int ExitKey)
{
    LoggerInit();
    info("Launching BlockEngine");
    InitializeWindow(WindowWidth,WindowHeight, WindowTitle);
    InitializeInput();
    SetExitKey(ExitKey);
    AudioInit();
}

inline void ShutdownBlockEngine()
{
    info("Closing Program");
    RenderingShutDown();
    AudioShutdown();
    info("Closed Program");
}

#endif
