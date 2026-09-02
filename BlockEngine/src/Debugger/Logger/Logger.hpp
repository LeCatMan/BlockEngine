#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../../Debugger/Utilities/Utilities.hpp"
#include "../../Debugger/Math/MathUtilities/MathUtilities.hpp"

int LoggerInit(void);
int LoggerShutdown(void);
int Error(const char* Message, const char* File, int Line);
int Trace(const char* Message, const char* File, int Line);
int Info(const char* Message, const char* File, int Line);
int Warning(const char* Message, const char* File, int Line);
int Special(const char* Message, const char* File, int Line);
int Debug(const char* Message, const char* File, int Line);
int AudioLog(const char* Message, const char* File, int Line);
int Rendering(const char* Message, const char* File, int Line);

// Log error with the file and line location and time.
#pragma region error
#define error(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    Error(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log trace with the file and line location and time.
#pragma region trace
#define trace(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    Trace(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log info with the file and line location and time.
#pragma region info
#define info(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    Info(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log warning with the file and line location and time.
#pragma region warning
#define warning(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    Warning(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log debug with the file and line location and time.
#pragma region debug
#define debug(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    Debug(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log audio with the file and line location and time.
#pragma region audio
#define audio(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    AudioLog(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log rendering with the file and line location and time.
#pragma region rendering
#define rendering(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    Rendering(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


#pragma region special
#define special(Message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), Message, ##__VA_ARGS__); \
    \
    /* Log message was truncated due to exceeding 1024 bytes */ \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        Error("Message is bigger than : 1024 bytes", __FILE__, __LINE__); \
    } \
    else \
    { \
    Special(Buffer, __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


