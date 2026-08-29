#pragma once

#include "../../external/miniaudio-0.11.25/miniaudio.h"
#include "../Debugger/Debugger.hpp"
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>

#define DEFAULT_VOLUME 1.0f
#define DEFAULT_PITCH 1.0f

class ResourceManager
{
private:
    ma_device device;
    ma_resource_manager resourceManager;
    ma_resource_manager_data_source dataSource;
    bool IsInitialized = false;

public:
    int InitializeResourceManger(const char* sound);
    int ResourceManagerShutdown();
};

class Audio
{
private:
    ma_sound sound;
    bool sound_loaded = false;

public:
    void LoadSound(const char* Path, float volume = 1.0f, bool looping = false, float pitch = 1.0f);
    void NoneOverlappingSound();
    void OverlappingSound();
    void UnloadSound();
    ~Audio();
};

// Global Audio System Functions (Clean & Centralized)
void InitializeAudio(float volume);
void UpdateAudio(); // <--- Clean global system update
void AudioShutdown();