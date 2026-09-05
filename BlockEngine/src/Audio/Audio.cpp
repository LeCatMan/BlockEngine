#define MINIAUDIO_IMPLEMENTATION
#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "Audio.hpp"

ma_engine Engine;
bool Initialized = BLOCK_SUCCESS_FALSE;

// File-scoped tracker: completely hidden from the header and individual Audio objects
static std::vector<ma_sound*> ActiveOverlappingSounds;


// Initialize the audio engine.
BlockResult InitializeAudioEngine(float volume)
{

    #pragma region Initialize audio Engine
    if (ma_engine_init(NULL, &Engine) != MA_SUCCESS)
    {
        error("Failed to initialize audio engine!");
        Initialized = BLOCK_SUCCESS_FALSE;
        return BLOCK_ERR_INIT_FAILED;
    }
    #pragma endregion

    #pragma region Set audio engine variables
    if (ma_engine_set_volume(&Engine, volume) != MA_SUCCESS)
    {
        error("Failed to set master volume!");
        Initialized = BLOCK_SUCCESS_FALSE;
        return BLOCK_FAILURE;
    }
    
    Initialized = BLOCK_SUCCESS_TRUE;
    audio("Audio engine initialized!");
    return BLOCK_SUCCESS_TRUE;
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
BlockResult AudioShutdown()
{

    if (Initialized)
    {
        // Clean up any remaining overlapping sounds safely
        for (ma_sound* CopySound : ActiveOverlappingSounds)
        {
            if (CopySound)
            {
                ma_sound_stop(CopySound);
                ma_sound_uninit(CopySound);
                delete CopySound;
            }
        }
        ActiveOverlappingSounds.clear();

        Initialized = BLOCK_SUCCESS_FALSE;
        ma_engine_uninit(&Engine);
        audio("Audio engine shutdown!");
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        error("Failed to shutdown audio engine the engine is not initialized or is already shutdown!");
        return BLOCK_FAILURE;
    }

}


// Load the sound.
BlockResult Audio::LoadSound(const char *Path, BlockSoundFlags Flag)
{

    if (Initialized == BLOCK_SUCCESS_TRUE)
    {
        if (SoundLoaded == BLOCK_SUCCESS_FALSE)
        {        
            #pragma region Load sound
            if (ma_sound_init_from_file(&Engine, Path, Flag, NULL, NULL, &sound) != MA_SUCCESS)
            {
                error("Failed to load sound!");
                SoundLoaded = BLOCK_SUCCESS_FALSE;
                return BLOCK_SUCCESS_FALSE;
            }
            #pragma endregion
            
            #pragma region Print the name
            SoundLoaded = BLOCK_SUCCESS_TRUE;

            FileName = strrchr(Path, '/');
            FileName = FileName ? FileName + 1 : Path;

            audio("Loaded Sound : %s!", FileName);
            return BLOCK_SUCCESS_TRUE;
            #pragma endregion
        }
        else
        {
            warning("Cannot load sound because the sound is already loaded!");
            return BLOCK_SUCCESS_FALSE;
        }
    }
    else
    {
        warning("Cannot load sound because the engine is not loaded!");
        return BLOCK_SUCCESS_FALSE;
    }

}


BlockResult Audio::LoadEmbeddedSound(const unsigned char* Data, size_t DataSize)
{
    if (Initialized == BLOCK_SUCCESS_TRUE)
    {
        if (SoundLoaded == BLOCK_SUCCESS_FALSE)
        {   
            #pragma region Initialize decoder
            if (Data == nullptr || DataSize == 0)
            {
                warning("Cannot load sound because the data is invalid!");
                return BLOCK_ERR_NULL_POINTER;
            }

            // Initialize decoder from byte array into memory.
            ma_decoder_config config = ma_decoder_config_init_default();
            if (ma_decoder_init_memory(Data, DataSize, &config, &decoder) != MA_SUCCESS)
            {
                error("Failed to initialize decoder!");
                return BLOCK_ERR_FILE_IO;
            }
            #pragma endregion

            #pragma region Initialize sound
            // Initialize sound using the decoder as a data source.
            if (ma_sound_init_from_data_source(&Engine, &decoder, 0, NULL, &sound) != MA_SUCCESS)
            {
                error("Failed to load sound!");
                ma_decoder_uninit(&decoder);
                return BLOCK_FAILURE;
            }

            SoundLoaded = BLOCK_SUCCESS_TRUE;
            return BLOCK_SUCCESS_TRUE;
            #pragma endregion
        }
        else
        {
            warning("Cannot load sound because the sound is already loaded!");
            return BLOCK_SUCCESS_FALSE;
        }
    }
    else
    {
        warning("Cannot load sound because the engine is not loaded!");
        return BLOCK_SUCCESS_FALSE;
    }
}


// Plays the sound from the beginning, restarting it if it's already playing.
BlockResult Audio::PlaySound()
{
    // Ensure the sound asset is loaded before attempting playback
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }

    if (ma_sound_seek_to_pcm_frame(&sound, 0) != MA_SUCCESS)
    {
        error("Cannot rewind the sound!");
        return BLOCK_FAILURE;
    }

    if (ma_sound_start(&sound) != MA_SUCCESS)
    {
        error("Cannot start the sound!");
        return BLOCK_FAILURE;
    }

    return BLOCK_SUCCESS_TRUE;
}


// Make an insistence of the sound each time you play it.
BlockResult Audio::PlayOverlappingSound()
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }

    ma_sound* clonedSound;
    try
    {
        clonedSound = new ma_sound();
    }
    catch (const std::bad_alloc&)
    {
        error("Cannot allocate memory for cloned overlapping sounds!");
        return BLOCK_SUCCESS_FALSE;
    }

    if (ma_sound_init_copy(&Engine, &sound, BLOCK_SOUND_FLAG_DECODE, NULL, clonedSound) == MA_SUCCESS)
    {
        if (ma_sound_start(clonedSound) != MA_SUCCESS)
        {
            warning("Couldn't start overlapping sound!");
            ma_sound_uninit(clonedSound);
            delete clonedSound;
            return BLOCK_SUCCESS_FALSE;
        }
        ActiveOverlappingSounds.push_back(clonedSound); // Pushes to the hidden backend tracker
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        warning("Couldn't copy sound into RAM!");
        delete clonedSound;
        return BLOCK_SUCCESS_FALSE;
    }
}


// ########################
// #       Playback       #
// ########################


/**
 * Checks whether the sound is playing.
 *
 * @return true if the sound is playing; otherwise false.
 */
BlockResult Audio::IsSoundPlaying()
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }
    
    if (ma_sound_is_playing(&sound) == MA_TRUE)
    {
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        return BLOCK_SUCCESS_FALSE;
    }
}


/**
 * Checks whether the sound has reached its end.
 *
 * @return true if the sound has finished; otherwise false.
 */
BlockResult Audio::IsSoundFinished()
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }

    if (ma_sound_get_at_end(&sound) == MA_TRUE)
    {
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        return BLOCK_SUCCESS_FALSE;
    }
}


BlockResult Audio::StopSound()
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }
    
    if (ma_sound_stop(&sound) == MA_SUCCESS)
    {
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        error("Failed to stop sound!");
        return BLOCK_SUCCESS_FALSE;
    }
}


BlockResult Audio::StartSound()
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }
    
    if (ma_sound_start(&sound) == MA_SUCCESS)
    {
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        error("Failed to continue sound!");
        return BLOCK_SUCCESS_FALSE;
    }
}


BlockResult Audio::SetLooping(bool State)
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }
    
    ma_sound_set_looping(&sound,State);
    return BLOCK_SUCCESS_TRUE;
    
}


BlockResult Audio::IsSoundLooping()
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }
    
    if (ma_sound_is_looping(&sound) == MA_TRUE)
    {
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        return BLOCK_SUCCESS_FALSE;
    }
}



// ########################
// #        Fading        #
// ########################


/**
 * Adds a fade effect to the sound.
 *
 * @param VolumeBegin Volume at the beginning of the fade.
 * @param VolumeEnd Volume at the end of the fade.
 * @param FadeLengthInMilliseconds Duration of the fade in milliseconds.
 * @param StartTimeInMilliseconds Time in milliseconds when the fade starts.
 */
BlockResult Audio::Fade(float VolumeBegin, float VolumeEnd, int FadeLengthInMilliseconds, int StartTimeInMilliseconds)
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }

    ma_sound_set_fade_start_in_milliseconds(&sound, VolumeBegin, VolumeEnd, FadeLengthInMilliseconds, StartTimeInMilliseconds);
    return BLOCK_SUCCESS_TRUE;
}


// ########################
// #     3D Position      #
// ########################


/**
 * Sets the sound's position using a FloatVector3.
 *
 * Can be used for both 2D and 3D audio.
 * For 2D audio, only the X and Y components are used.
 *
 * @param XYZ Position of the sound.
 */
BlockResult Audio::SetSoundPosition(FloatVector3 XYZ)
{
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }
    ma_sound_set_position(&sound, XYZ.x, XYZ.y, XYZ.z);
    return BLOCK_SUCCESS_TRUE;
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
    if (!SoundLoaded)
    {
        warning("Sound is unloaded cannot get sound position.");
        return {0.0f, 0.0f, 0.0f};
    }
    ma_vec3f Buffer = ma_sound_get_position(&sound);
    return {Buffer.x, Buffer.y, Buffer.z};
}


// Deletes the sound from memory.
BlockResult Audio::UnloadSound()
{
    if (Initialized == BLOCK_SUCCESS_TRUE)
    {
    if (!SoundLoaded)
    {
        warning("The sound is unloaded cannot stop sound.");
        return BLOCK_FAILURE;
    }

        ma_sound_uninit(&sound);
        SoundLoaded = BLOCK_SUCCESS_FALSE;

        audio("Unloaded sound!");
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        warning("Cannot unload sound because the audio engine is not initialized!");
        return BLOCK_SUCCESS_FALSE;
    }
}


Audio::~Audio()
{
    if (Initialized == BLOCK_SUCCESS_TRUE)
    {
        if (!SoundLoaded)
        {
            return;
        }

        ma_sound_uninit(&sound);
        SoundLoaded = BLOCK_SUCCESS_FALSE;

        audio("Unloaded Sound!");
    }
    else
    {
        warning("Cannot unload sound because the audio engine is not initialized!");
    }
}




