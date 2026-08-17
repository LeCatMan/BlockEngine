#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>

// miniaudio engine object
static ma_engine engine;
static char buffer[256];
static bool init = false;

// Initialize the Audio engine with default settings
static inline void AudioInit()
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        error("Failed to initialize audio engine!");
    }
    else{init = true;}
}

// Play a sound. Non-blocking.
static inline void AudioPlay(const char* filename)
{
    if (ma_engine_play_sound(&engine, filename, NULL) != MA_SUCCESS) {
        snprintf(buffer, sizeof(buffer),"Failed to play audio file: %s",filename);
        error(buffer);
    }
}

// Clean up and shutdown engine.
static inline void AudioShutdown()
{
    if (init)
    {
        ma_engine_uninit(&engine);
        init = false;
    }
    else
    {
       error("Failed to shutdown audio engine the engine is not initialized or is already shutdown!");
    }
}

#endif
