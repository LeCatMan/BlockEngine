#define MINIAUDIO_IMPLEMENTATION
#include "../../external/miniaudio-0.11.25/miniaudio.h"

#include "Audio.hpp"

ma_engine engine;
bool init = false;


/**
 * Loads a sound into the audio object.
 *
 * @param filename Path to the sound file.
 * @param volume Sound volume.
 * @param looping Whether the sound loops.
 * @param pitch Playback pitch.
 */
void Audio::LoadSound(const char *filename, float volume, bool looping, float pitch)
{
    ma_result result = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS)
    {
        error("Failed to load sound!");
        sound_loaded = MA_FALSE;
        return;
    }
    ma_sound_set_volume(&sound, volume);
    ma_sound_set_looping(&sound, looping);
    ma_sound_set_pitch(&sound, pitch);
    sound_loaded = MA_TRUE;
    trace("Loaded Sound!");
}

/**
 * Play Sound
 * ----------
 * Plays the sound loaded into the audio object.
 *
 * Example:
 *     AudioObject[0].PlaySound();
 */
void Audio::PlaySound()
{
    if (!sound_loaded)
    {
        warning("Sound is unloaded connot play sound.");
        return;
    }
    ma_sound_seek_to_pcm_frame(&sound, 0);
    ma_sound_start(&sound);   
}

/**
 * Unload Sound
 * ------------
 * Manually unloads the sound from the audio object.
 *
 * The sound is also unloaded automatically when
 * the Audio object's lifetime ends.
 *
 * Example:
 *     AudioObject[0].UnloadSound();
 */
void Audio::UnloadSound()
{
    if (!sound_loaded)
    {
        sound_loaded = MA_FALSE;
        warning("Sound is already unloaded.");
        return;
    }
    ma_sound_uninit(&sound);
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
    sound_loaded = MA_FALSE;
    info("Unloaded Sound!");
}
