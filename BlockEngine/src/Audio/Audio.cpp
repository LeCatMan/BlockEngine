#define MINIAUDIO_IMPLEMENTATION
#include "../../external/miniaudio-0.11.25/miniaudio.h"

#include "Audio.hpp"
#include <math.h>

ma_engine engine;
bool init = false;
AudioLimiter limiter;
ma_sound_group AudioGroup;

static void AudioLimiterProcess(ma_node* node, const float** input, ma_uint32* inputFrameCount, float** output, ma_uint32* outputFrameCount);

static ma_node_vtable AudioLimiterVTable =
{
    AudioLimiterProcess,
    NULL,
    1,
    1,
    0
};

/**
 * Allocates and initializes the delay line buffer based on the sample rate and lookahead duration.
 */
void InitAudioLimiterBuffer(AudioLimiter* limiter, ma_uint32 sampleRate, ma_uint32 channels)
{
    limiter->delayBufferLength = (ma_uint32)(sampleRate * limiter->lookaheadSec);
    if (limiter->delayBufferLength == 0) limiter->delayBufferLength = 1;

    limiter->delayBuffer.assign(limiter->delayBufferLength * channels, 0.0f);
    limiter->writeIndex = 0;
}

static void AudioLimiterProcess(ma_node* node, const float** input, ma_uint32* inputFrameCount, float** output, ma_uint32* outputFrameCount)
{
    AudioLimiter* limiter = (AudioLimiter*)node;
    ma_uint32 frameCount = *inputFrameCount;
    ma_uint32 channels = ma_node_get_input_channels(node, 0);

    if (limiter->delayBuffer.empty())
    {
        InitAudioLimiterBuffer(limiter, 48000, channels);
    }

    float sampleRate = 48000.0f; 
    float attackCoeff  = 1.0f - expf(-1.0f / (sampleRate * limiter->attackTimeSec));
    float releaseCoeff = 1.0f - expf(-1.0f / (sampleRate * limiter->releaseTimeSec));

    const float* inSamples = input[0];
    float* outSamples = output[0];

    for (ma_uint32 i = 0; i < frameCount; i++)
    {
        float currentPeak = 0.0f;

        for (ma_uint32 ch = 0; ch < channels; ch++)
        {
            float mag = fabsf(inSamples[i * channels + ch]);
            if (mag > currentPeak) currentPeak = mag;
        }

        float targetGain = 1.0f;
        if (currentPeak > limiter->threshold)
        {
            targetGain = limiter->threshold / currentPeak;
        }

        if (targetGain < limiter->gain)
        {
            limiter->gain += (targetGain - limiter->gain) * attackCoeff;
        }
        else
        {
            limiter->gain += (targetGain - limiter->gain) * releaseCoeff;
        }

        ma_uint32 bufferPos = limiter->writeIndex * channels;

        for (ma_uint32 ch = 0; ch < channels; ch++)
        {
            float delayedSample = limiter->delayBuffer[bufferPos + ch];
            limiter->delayBuffer[bufferPos + ch] = inSamples[i * channels + ch];
            outSamples[i * channels + ch] = delayedSample * limiter->gain;
        }

        limiter->writeIndex = (limiter->writeIndex + 1) % limiter->delayBufferLength;
    }

    *outputFrameCount = frameCount;
}

void InitializeAudio(float volume)
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
    {
        error("Failed to initialize audio engine!");
        init = false;
        return;
    }

    if (ma_sound_group_init(&engine, 0, NULL, &AudioGroup) != MA_SUCCESS)
    {
        error("Failed to initialize audio group!");
        ma_engine_uninit(&engine);
        init = false;
        return;
    }

    ma_engine_set_volume(&engine, volume);

    // Apply headroom attenuation to preventing multiple overlapping sounds from instantly blowing out the bus
    ma_sound_group_set_volume(&AudioGroup, 0.6f);

    ma_node_graph* graph = ma_engine_get_node_graph(&engine);
    ma_node* endpoint = ma_engine_get_endpoint(&engine);

    ma_uint32 channels[1] = { 2 };

    ma_node_config config = ma_node_config_init();

    config.vtable = &AudioLimiterVTable;
    config.pInputChannels = channels;
    config.pOutputChannels = channels;

    ma_result result = ma_node_init(graph, &config, NULL, &limiter.base);

    if (result != MA_SUCCESS)
    {
        error("Failed to initialize audio limiter!");
        ma_sound_group_uninit(&AudioGroup);
        ma_engine_uninit(&engine);
        init = false;
        return;
    }

    InitAudioLimiterBuffer(&limiter, 48000, 2);

    ma_node_attach_output_bus(&AudioGroup, 0, &limiter.base, 0);
    ma_node_attach_output_bus(&limiter.base, 0, endpoint, 0);

    init = true;

    info("Audio engine initialized!");
}

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
    // Added MA_SOUND_FLAG_DECODE to store fully decoded PCM audio in RAM
    ma_result result = ma_sound_init_from_file(&engine, filename, MA_SOUND_FLAG_DECODE, &AudioGroup, NULL, &sound);

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
    OverlappingSoundfilename = filename;

    trace("Loaded Sound!");
}

/**
 * NoneOverlappingSound
 * --------------------
 * Plays the sound loaded into the audio object.
 *
 * Example:
 *     AudioObject[0].NoneOverlappingSound();
 */
void Audio::NoneOverlappingSound()
{
    if (!sound_loaded)
    {
        warning("Sound is unloaded connot play sound.");
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
    if (ma_sound_init_copy(&engine, &sound, MA_SOUND_FLAG_DECODE, &AudioGroup, clonedSound) == MA_SUCCESS)
    {
        // Automatically uninitialize and free memory when the sound finishes playing
        ma_sound_set_end_callback(clonedSound, [](void* pUserData, ma_sound* pSound) {
            ma_sound_uninit(pSound);
            delete pSound;
        }, NULL);

        ma_sound_start(clonedSound);
    }
    else
    {
        warning("Couldn't copy sound into RAM!");
        delete clonedSound;
    }
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

void AudioShutdown()
{
    if (init)
    {
        limiter.delayBuffer.clear();
        ma_node_uninit(&limiter.base, NULL);
        ma_sound_group_uninit(&AudioGroup);
        ma_engine_uninit(&engine);

        init = false;

        info("Audio engine shutdown!");
    }
    else
    {
        error("Failed to shutdown audio engine the engine is not initialized or is already shutdown!");
    }
}