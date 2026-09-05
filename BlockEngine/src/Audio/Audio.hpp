#pragma once
#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <new>


#define DEFAULT_VOLUME 1.0f
#define DEFAULT_PITCH 1.0f

/* Sound flags. */
typedef enum BlockSoundFlags
{
/* Resource Handling & Memory Strategy */

/* Read in small chunks during playback. Saves RAM. Best for long BGM/Music tracks. */
BLOCK_SOUND_FLAG_STREAM         = 0x00000001, 

/* Uncompress entire sound into RAM at load time. Instant playback, 0 CPU delay. Best for SFX (clicks, gunshots). */
BLOCK_SOUND_FLAG_DECODE         = 0x00000002, 

/* Load sound in the background on another thread so the main game loop doesn't freeze or stutter. */
BLOCK_SOUND_FLAG_ASYNC          = 0x00000004, 

/* Block/pause execution until background loading completes (used with ASYNC to force game to wait before playing). */
BLOCK_SOUND_FLAG_WAIT_INIT      = 0x00000008, 

/* For dynamic or generated audio feeds where total time/duration isn't known ahead of time. */
BLOCK_SOUND_FLAG_UNKNOWN_LENGTH = 0x00000010, 

/* Automatically restart playback from the beginning when it reaches the end. */
BLOCK_SOUND_FLAG_LOOPING        = 0x00000020, 


/* Playback & Audio Pipeline */

/* Load sound into memory silently without plugging it into speakers yet (useful for manual channel routing). */
BLOCK_SOUND_FLAG_NO_ATTACHMENT  = 0x00001000, 

/* Lock pitch changes to save CPU (sound pitch/speed cannot be altered dynamically). */
BLOCK_SOUND_FLAG_NO_PITCH       = 0x00002000, 

/* Turn off 3D positional audio, distance fade, and stereo panning. Best for 2D UI clicks or master background music. */
BLOCK_SOUND_FLAG_NO_SPATIAL     = 0x00004000

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