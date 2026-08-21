#define MINIAUDIO_IMPLEMENTATION
#include "../../external/miniaudio-0.11.25/miniaudio.h"

#include "Audio.hpp"

ma_engine engine;
bool init = false;

void Audio::LoadSound(const char *filename)
{
    ma_result result = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS)
    {
        error("Failed to load sound!");
        sound_loaded = MA_FALSE;
        return;
    }
    sound_loaded = MA_TRUE;
    trace("Loaded Sound!");
}

void Audio::PlaySound()
{
    if (!sound_loaded)
    {
        warning("Sound is unloaded connot play sound.");
        return;
    }
    ma_sound_start(&sound);
}

void Audio::UnloadSound()
{
    if (!sound_loaded)
    {
        sound_loaded = MA_FALSE;
        warning("Sound is already unloaded.");
        return;
    }
    sound_loaded = MA_FALSE;
    trace("Unloaded Sound!");
}

Audio::~Audio()
{
    if (!sound_loaded)
    {
        sound_loaded = MA_FALSE;
        return;
    }
    ma_sound_uninit(&sound);
    info("Unloaded Sound!");
}
