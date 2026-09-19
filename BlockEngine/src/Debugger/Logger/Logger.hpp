#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <cstdio>
#include "../Math/MathUtilities/MathUtilities.hpp"
#include "../Utilities/BlockResult.hpp"
#include "../Utilities/Utilities.hpp"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

BlockResult LoggerInit(void);
BlockResult LoggerShutdown(void);
BlockResult Error(const char* Message, const char* File, int Line);
BlockResult Trace(const char* Message, const char* File, int Line);
BlockResult Info(const char* Message, const char* File, int Line);
BlockResult Warning(const char* Message, const char* File, int Line);
BlockResult Special(const char* Message, const char* File, int Line);
BlockResult Debug(const char* Message, const char* File, int Line);
BlockResult AudioLog(const char* Message, const char* File, int Line);
BlockResult Rendering(const char* Message, const char* File, int Line);

// Log error with the file and line location and time.
#pragma region error
#define error(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        Error(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log trace with the file and line location and time.
#pragma region trace
#define trace(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        Trace(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log info with the file and line location and time.
#pragma region info
#define info(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        Info(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log warning with the file and line location and time.
#pragma region warning
#define warning(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        Warning(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log debug with the file and line location and time.
#pragma region debug
#define debug(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        Debug(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log audio with the file and line location and time.
#pragma region audio
#define audio(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        AudioLog(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


// Log rendering with the file and line location and time.
#pragma region rendering
#define rendering(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        Rendering(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


#pragma region special
#define special(Message, ...) do { \
    int size = snprintf(nullptr, 0, Message, ##__VA_ARGS__); \
    if (size < 0) { \
        Error("Failed to format message", __FILE__, __LINE__); \
    } \
    else { \
        std::vector<char> Buffer(size + 1); \
        snprintf(Buffer.data(), Buffer.size(), Message, ##__VA_ARGS__); \
        Special(Buffer.data(), __FILE__, __LINE__); \
    } \
} while(0)
#pragma endregion


