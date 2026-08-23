#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>

#define DEFAULT_MASTER_VOLUME 1.0f
#define DEFAULT_VOLUME 1.0f
#define DEFAULT_PITCH 1.0f

extern ma_engine engine;
extern bool init;

/**
 * Audio Object
 *
 * Audio objects provide sound for entities and other objects.
 *
 * Example:
 * Audio AudioObject[2];
 */
class Audio
{
protected:
    ma_sound sound;
    bool sound_loaded = false;
public:
    void LoadSound(const char *filename, float volume, bool looping, float pitch);
    void PlaySound();
    void UnloadSound();
    ~Audio();
};


// Initialize the Audio engine with default settings
inline void InitializeAudio(float volume)
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
    {
        error("Failed to initialize audio engine!");
        init = false;
        return;
    }
    ma_engine_set_volume(&engine, volume);
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
