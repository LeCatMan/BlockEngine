#pragma once
#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <new>


#define BLOCK_DEFAULT_VOLUME 1.0f
#define BLOCK_DEFAULT_PITCH 1.0f

#ifdef PlaySound
#undef PlaySound
#endif


/* Sound flags. */
typedef enum BlockSoundFlags
{
/* Resource Handling & Memory Strategy */

/* Read in small chunks during playback. Saves RAM. Best for long BGM/Music tracks. */
BLOCK_SOUND_FLAG_STREAM         = MA_SOUND_FLAG_STREAM, 

/* Uncompress entire sound into RAM at load time. Instant playback, 0 CPU delay. Best for SFX (clicks, gunshots). */
BLOCK_SOUND_FLAG_DECODE         = MA_SOUND_FLAG_DECODE, 

/* Load sound in the background on another thread so the main game loop doesn't freeze or stutter. */
BLOCK_SOUND_FLAG_ASYNC          = MA_SOUND_FLAG_ASYNC, 

/* Block/pause execution until background loading completes (used with ASYNC to force game to wait before playing). */
BLOCK_SOUND_FLAG_WAIT_INIT      = MA_SOUND_FLAG_WAIT_INIT, 

/* For dynamic or generated audio feeds where total time/duration isn't known ahead of time. */
BLOCK_SOUND_FLAG_UNKNOWN_LENGTH = MA_SOUND_FLAG_UNKNOWN_LENGTH, 

/* Automatically restart playback from the beginning when it reaches the end. */
BLOCK_SOUND_FLAG_LOOPING        = MA_SOUND_FLAG_LOOPING, 


/* Playback & Audio Pipeline */

/* Load sound into memory silently without plugging it into speakers yet (useful for manual channel routing). */
BLOCK_SOUND_FLAG_NO_ATTACHMENT  = MA_SOUND_FLAG_NO_DEFAULT_ATTACHMENT, 

/* Lock pitch changes to save CPU (sound pitch/speed cannot be altered dynamically). */
BLOCK_SOUND_FLAG_NO_PITCH       = MA_SOUND_FLAG_NO_PITCH, 

/* Turn off 3D positional audio, distance fade, and stereo panning. Best for 2D UI clicks or master background music. */
BLOCK_SOUND_FLAG_NO_SPATIAL     = MA_SOUND_FLAG_NO_SPATIALIZATION

} BlockSoundFlags;


// Overload operator| so bitwise operations return BlockSoundFlags instead of int
inline BlockSoundFlags operator|(BlockSoundFlags a, BlockSoundFlags b) {
    return static_cast<BlockSoundFlags>(static_cast<int>(a) | static_cast<int>(b));
}


class Audio
{
private:
    /* Engine Handles & States */
    ma_sound sound;
    ma_decoder decoder;
    BlockResult SoundLoaded = BLOCK_SUCCESS_FALSE;
    const char *FileName;

public:
    /* Constructors, Destructor & Lifetime Control */

    Audio() = default;
    ~Audio();
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    /* Loading & Unloading */

    BlockResult LoadSound(const char* Path, BlockSoundFlags Flag);
    BlockResult LoadEmbeddedSound(const unsigned char* pData, size_t dataSize);
    BlockResult UnloadSound();

    /* Playback Control */

    BlockResult PlaySound();
    BlockResult StopSound();
    BlockResult StartSound();
    BlockResult PlayOverlappingSound();
    BlockResult Fade(float volumeBeg, float volumeEnd, int fadeLengthInMilliseconds, int absoluteGlobalTimeInMilliseconds);

    /* State Queries */

    BlockResult IsSoundFinished();
    BlockResult IsSoundPlaying();
    BlockResult IsSoundLooping();

    /* 3D Spatialization */

    BlockResult SetSoundPosition(FloatVector3 XYZ);
    FloatVector3 GetSoundPosition();


    BlockResult SetLooping(bool State);
};


// Global Audio System Functions

BlockResult InitializeAudioEngine(float volume);
void UpdateAudio();
BlockResult AudioShutdown();