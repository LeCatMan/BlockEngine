#pragma once


#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>

#define DEFAULT_VOLUME 1.0f
#define DEFAULT_PITCH 1.0f

/* Sound flags. */
typedef enum BlockSoundFlags
{
    /* Resource handling. */
    BLOCK_SOUND_FLAG_STREAM         = 0x00000001, /* Stream audio directly from its source. */
    BLOCK_SOUND_FLAG_DECODE         = 0x00000002, /* Decode the audio data when loading it. */
    BLOCK_SOUND_FLAG_ASYNC          = 0x00000004, /* Load the audio resource asynchronously. */
    BLOCK_SOUND_FLAG_WAIT_INIT      = 0x00000008, /* Wait for the audio resource to finish initializing. */
    BLOCK_SOUND_FLAG_UNKNOWN_LENGTH = 0x00000010, /* Allow the audio length to remain unknown. */
    BLOCK_SOUND_FLAG_LOOPING        = 0x00000020, /* Loop the sound when playback reaches its end. */

    /* Playback. */
    BLOCK_SOUND_FLAG_NO_ATTACHMENT  = 0x00001000, /* Do not attach the sound to the audio endpoint automatically. */
    BLOCK_SOUND_FLAG_NO_PITCH       = 0x00002000, /* Disable pitch control for the sound. */
    BLOCK_SOUND_FLAG_NO_SPATIAL     = 0x00004000  /* Disable 3D spatialization for the sound. */

} BlockSoundFlags;

class Audio
{
private:
    ma_sound sound;
    bool SoundLoaded = BLOCK_FALSE;

public:
    void LoadSound(const char* Path, BlockSoundFlags Flag, float volume, bool looping, float pitch = 1.0f);
    void Fade(float volumeBeg, float volumeEnd, ma_uint64 fadeLengthInMilliseconds, ma_uint64 absoluteGlobalTimeInMilliseconds);
    bool IsSoundFinished();
    void SetSoundPosition(FloatVector3 XYZ);
    FloatVector3 GetSoundPosition();
    void NoneOverlappingSound();
    void OverlappingSound();
    void UnloadSound();
    ~Audio();
};

// Global Audio System Functions

int InitializeAudioEngine(float volume);
void UpdateAudio();
void AudioShutdown();