#define MINIAUDIO_IMPLEMENTATION
#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "Audio.hpp"

ma_engine Engine;
bool Initialized = BLOCK_FALSE;

// File-scoped tracker: completely hidden from the header and individual Audio objects
static std::vector<ma_sound*> ActiveOverlappingSounds;


// Initialize the audio engine.
int InitializeAudioEngine(float volume)
{

    #pragma region Initialize audio Engine
    if (ma_engine_init(NULL, &Engine) != MA_SUCCESS)
    {
        error("Failed to initialize audio engine!");
        Initialized = BLOCK_FALSE;
        return BLOCK_ERR_INIT_FAILED;
    }
    #pragma endregion

    #pragma region Set audio engine variables
    ma_engine_set_volume(&Engine, volume);
    Initialized = BLOCK_TRUE;
    audio("Audio engine initialized!");
    return BLOCK_SUCCESS;
    #pragma endregion

}


// Global system update function called once per frame.
void UpdateAudio()
{

    // get through every cloned sound if it's there then see if it's playing if it's not playing delete it from memory.
    for (auto IndexSound = ActiveOverlappingSounds.begin(); IndexSound != ActiveOverlappingSounds.end(); )
    {
        ma_sound* Sound = *IndexSound;
        if (Sound)
        {
            if (!ma_sound_is_playing(Sound))
            {
                ma_sound_uninit(Sound);
                delete Sound;
                IndexSound = ActiveOverlappingSounds.erase(IndexSound);
                continue;
            }
        }
        ++IndexSound;
    }

}


// Shutdown audio engine.
void AudioShutdown()
{

    if (Initialized)
    {
        // Clean up any remaining overlapping sounds safely
        for (ma_sound* pSound : ActiveOverlappingSounds)
        {
            if (pSound)
            {
                ma_sound_stop(pSound);
                ma_sound_uninit(pSound);
                delete pSound;
            }
        }
        ActiveOverlappingSounds.clear();

        Initialized = BLOCK_FALSE;
        ma_engine_uninit(&Engine);
        audio("Audio engine shutdown!");
    }
    else
    {
        error("Failed to shutdown audio engine the engine is not initialized or is already shutdown!");
    }

}


// Load the sound.
void Audio::LoadSound(const char *Path, BlockSoundFlags Flag, float Volume, bool Looping, float Pitch)
{

    #pragma region Load sound

    if (ma_sound_init_from_file(&Engine, Path, Flag, NULL, NULL, &sound) != MA_SUCCESS)
    {
        error("Failed to load sound!");
        SoundLoaded = BLOCK_FALSE;
        return;
    }
    #pragma endregion
    
    #pragma region Set sound properties
    ma_sound_set_volume(&sound, Volume);
    ma_sound_set_looping(&sound, Looping);
    ma_sound_set_pitch(&sound, Pitch);
    SoundLoaded = BLOCK_TRUE;

    const char *FileName = strrchr(Path, '/') + 1;

    audio("Loaded Sound : %s!", FileName);
    #pragma endregion

}





void Audio::NoneOverlappingSound()
{
    if (!SoundLoaded)
    {
        warning("Sound is unloaded cannot play sound.");
        return;
    }

    ma_sound_seek_to_pcm_frame(&sound, 0);
    ma_sound_start(&sound);
}


/**
 * Adds a fade effect to the sound.
 *
 * @param VolumeBegin Volume at the beginning of the fade.
 * @param VolumeEnd Volume at the end of the fade.
 * @param FadeLengthInMilliseconds Duration of the fade in milliseconds.
 * @param StartTimeInMilliseconds Time in milliseconds when the fade starts.
 */
void Audio::Fade(float VolumeBegin, float VolumeEnd, ma_uint64 FadeLengthInMilliseconds, ma_uint64 StartTimeInMilliseconds)
{
    ma_sound_set_fade_start_in_milliseconds(&sound, VolumeBegin, VolumeEnd, FadeLengthInMilliseconds, StartTimeInMilliseconds);
}


/**
 * Checks whether the sound has reached its end.
 *
 * @return true if the sound has finished; otherwise false.
 */
bool Audio::IsSoundFinished()
{
    return ma_sound_get_at_end(&sound);
}


/**
 * Sets the sound's position using a FloatVector3.
 *
 * Can be used for both 2D and 3D audio.
 * For 2D audio, only the X and Y components are used.
 *
 * @param XYZ Position of the sound.
 */
void Audio::SetSoundPosition(FloatVector3 XYZ)
{
    ma_sound_set_position(&sound, XYZ.x, XYZ.y, XYZ.z);
}

/**
 * Gets the sound's position using a FloatVector3.
 *
 * Can be used for both 2D and 3D audio.
 * For 2D audio, only the X and Y components are used.
 *
 */
FloatVector3 Audio::GetSoundPosition()
{
    ma_vec3f Buffer = ma_sound_get_position(&sound);
    return {Buffer.x, Buffer.y, Buffer.z};
}



void Audio::OverlappingSound()
{
    if (!SoundLoaded)
    {
        warning("Sound is unloaded cannot play sound.");
        return;
    }

    ma_sound* clonedSound = new ma_sound();
    if (ma_sound_init_copy(&Engine, &sound, BLOCK_SOUND_FLAG_DECODE, NULL, clonedSound) == MA_SUCCESS)
    {
        ma_sound_start(clonedSound);
        ActiveOverlappingSounds.push_back(clonedSound); // Pushes to the hidden backend tracker
    }
    else
    {
        warning("Couldn't copy sound into RAM!");
        delete clonedSound;
    }
}


void Audio::UnloadSound()
{
    if (!SoundLoaded)
    {
        SoundLoaded = BLOCK_FALSE;
        warning("Sound is already unloaded.");
        return;
    }

    ma_sound_uninit(&sound);
    SoundLoaded = BLOCK_FALSE;

    audio("Unloaded Sound!");
}

Audio::~Audio()
{
    if (!SoundLoaded)
    {
        SoundLoaded = BLOCK_FALSE;
        return;
    }

    ma_sound_uninit(&sound);
    SoundLoaded = BLOCK_FALSE;

    audio("Unloaded Sound!");
}




