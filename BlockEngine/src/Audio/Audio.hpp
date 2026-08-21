#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>


// miniaudio engine object

extern ma_engine engine;
extern bool init;

class Audio
{
protected:
    ma_sound sound;
    bool sound_loaded = false;
public:
    void LoadSound(const char *filename);
    void PlaySound();
    void UnloadSound();
    ~Audio();
};


// Initialize the Audio engine with default settings
inline void InitializeAudio()
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
    {
        error("Failed to initialize audio engine!");
        init = false;
        return;
    }

    init = true;
    info("Audio engine initialized!");
}


// Clean up and shutdown engine.
inline void AudioShutdown()
{
    if (init)
    {
        ma_engine_uninit(&engine);
        init = false;
        info("Audio engine shutdown!");
    }
    else
    {
       error("Failed to shutdown audio engine the engine is not initialized or is already shutdown!");
    }
}

#endif
