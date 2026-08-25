#pragma once

#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>
#include <vector>

#define DEFAULT_MASTER_VOLUME 1.0f
#define DEFAULT_VOLUME 1.0f
#define DEFAULT_PITCH 1.0f

extern ma_engine engine;
extern bool init;
extern ma_sound_group AudioGroup;

struct AudioLimiter
{
    ma_node_base base;               // Required miniaudio base node structure

    float threshold = 0.95f;        // Ceiling limit (signal magnitude shouldn't cross 0.95)
    float gain = 1.0f;              // Active smooth volume multiplier applied to output

    float attackTimeSec = 0.005f;   // Time constant to pull volume down (5 milliseconds)
    float releaseTimeSec = 0.150f;  // Time constant to return volume back up (150 milliseconds)

    float lookaheadSec = 0.005f;    // Delay time buffer (5 milliseconds)
    std::vector<float> delayBuffer; // Interleaved memory storage to hold raw delayed samples
    ma_uint32 delayBufferLength = 0;// Total frame capacity of the delay ring buffer
    ma_uint32 writeIndex = 0;       // Current write pointer cursor location inside the ring buffer
};

extern AudioLimiter limiter;

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
    const char* OverlappingSoundfilename;

public:
    void LoadSound(const char* filename, float volume, bool looping, float pitch);
    void NoneOverlappingSound();
    void OverlappingSound();
    void UnloadSound();
    ~Audio();
};

void InitializeAudio(float volume);
void AudioShutdown();
void InitAudioLimiterBuffer(AudioLimiter* limiter, ma_uint32 sampleRate, ma_uint32 channels);