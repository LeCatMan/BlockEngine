#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../Debugger/Debugger.hpp"

int LoggerInit(void);
int LoggerShutdown(void);
int Error(const char* msg, const char* file, int line);
int Trace(const char* msg, const char* file, int line);
int Info(const char* msg, const char* file, int line);
int Warning(const char* msg, const char* file, int line);
int Debug(const char* msg, const char* file, int line);

// Log error with the file and line location.
#define error(message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), message, ##__VA_ARGS__); \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        /* Log message was truncated due to exceeding 1024 bytes */ \
    } \
    Error(Buffer, __FILE__, __LINE__); \
} while(0)

// Log trace with the file and line location.
#define trace(message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), message, ##__VA_ARGS__); \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        /* Log message was truncated due to exceeding 1024 bytes */ \
    } \
    Trace(Buffer, __FILE__, __LINE__); \
} while(0)

// Log info with the file and line location.
#define info(message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), message, ##__VA_ARGS__); \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        /* Log message was truncated due to exceeding 1024 bytes */ \
    } \
    Info(Buffer, __FILE__, __LINE__); \
} while(0)

// Log warning with the file and line location.
#define warning(message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), message, ##__VA_ARGS__); \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        /* Log message was truncated due to exceeding 1024 bytes */ \
    } \
    Warning(Buffer, __FILE__, __LINE__); \
} while(0)

// Log debug with the file and line location.
#define debug(message, ...) do { \
    char Buffer[1024]; \
    int written = snprintf(Buffer, sizeof(Buffer), message, ##__VA_ARGS__); \
    if (written < 0 || (size_t)written >= sizeof(Buffer)) { \
        /* Log message was truncated due to exceeding 1024 bytes */ \
    } \
    Debug(Buffer, __FILE__, __LINE__); \
} while(0)


