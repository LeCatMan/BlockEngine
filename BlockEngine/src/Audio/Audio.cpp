#define MINIAUDIO_IMPLEMENTATION
#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "Audio.hpp"
#include <vector>

ma_engine engine;
bool init = false;

// File-scoped tracker: completely hidden from the header and individual Audio objects
static std::vector<ma_sound*> s_ActiveOverlappingSounds;

void InitializeAudio(float volume)
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

// Global system update function called once per frame
void UpdateAudio()
{
    for (auto it = s_ActiveOverlappingSounds.begin(); it != s_ActiveOverlappingSounds.end(); )
    {
        ma_sound* pSound = *it;
        if (pSound)
        {
            if (!ma_sound_is_playing(pSound))
            {
                ma_sound_uninit(pSound);
                delete pSound;
                it = s_ActiveOverlappingSounds.erase(it);
                continue;
            }
        }
        ++it;
    }
}

void Audio::LoadSound(const char *filename, float volume, bool looping, float pitch)
{
    ma_result result = ma_sound_init_from_file(&engine, filename, MA_SOUND_FLAG_DECODE, NULL, NULL, &sound);

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

void Audio::NoneOverlappingSound()
{
    if (!sound_loaded)
    {
        warning("Sound is unloaded cannot play sound.");
        return;
    }

    ma_sound_seek_to_pcm_frame(&sound, 0);
    ma_sound_start(&sound);
}

void Audio::OverlappingSound()
{
    if (!sound_loaded)
    {
        warning("Sound is unloaded cannot play sound.");
        return;
    }

    ma_sound* clonedSound = new ma_sound();
    if (ma_sound_init_copy(&engine, &sound, MA_SOUND_FLAG_DECODE, NULL, clonedSound) == MA_SUCCESS)
    {
        ma_sound_start(clonedSound);
        s_ActiveOverlappingSounds.push_back(clonedSound); // Pushes to the hidden backend tracker
    }
    else
    {
        warning("Couldn't copy sound into RAM!");
        delete clonedSound;
    }
}

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

void AudioShutdown()
{
    if (init)
    {
        // Clean up any remaining overlapping sounds safely
        for (ma_sound* pSound : s_ActiveOverlappingSounds)
        {
            if (pSound)
            {
                ma_sound_stop(pSound);
                ma_sound_uninit(pSound);
                delete pSound;
            }
        }
        s_ActiveOverlappingSounds.clear();

        init = false;
        ma_engine_uninit(&engine);
        info("Audio engine shutdown!");
    }
    else
    {
        error("Failed to shutdown audio engine the engine is not initialized or is already shutdown!");
    }
}

// Audio callback & ResourceManager remain the same
void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_data_source* pDataSource = (ma_data_source*)pDevice->pUserData;
    ma_data_source_read_pcm_frames(pDataSource, pOutput, frameCount, NULL);
    (void)pInput;
}

int ResourceManager::InitializeResourceManger(const char* sound)
{
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.dataCallback = data_callback;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
    {
        error("Failed to initialize audio device.");
        return 1;
    }

    ma_resource_manager_config rmConfig = ma_resource_manager_config_init();
    rmConfig.decodedFormat     = device.playback.format;
    rmConfig.decodedChannels   = device.playback.channels;
    rmConfig.decodedSampleRate = device.sampleRate;

    if (ma_resource_manager_init(&rmConfig, &resourceManager) != MA_SUCCESS)
    {
        error("Failed to initialize resource manager.");
        ma_device_uninit(&device);
        return 1;
    }

    if (ma_resource_manager_data_source_init(&resourceManager, sound, MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_DECODE | MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_STREAM, NULL, &dataSource) != MA_SUCCESS)
    {
        error("Failed to initialize resource manager data source.");
        ma_resource_manager_uninit(&resourceManager);
        ma_device_uninit(&device);
        return 1;
    }

    ma_data_source_set_looping(&dataSource, MA_TRUE);
    device.pUserData = &dataSource;

    if (ma_device_start(&device) != MA_SUCCESS)
    {
        error("Failed to start audio device!");
        return 1;
    }

    is_initialized = true;
    return 0;
}

int ResourceManager::ResourceManagerShutdown()
{
    if (!is_initialized) return 0;

    ma_device_uninit(&device);
    ma_resource_manager_data_source_uninit(&dataSource);
    ma_resource_manager_uninit(&resourceManager);
    
    is_initialized = false;
    return 0;
}


