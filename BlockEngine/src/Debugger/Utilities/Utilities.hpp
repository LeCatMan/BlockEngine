#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../Logger/Logger.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

typedef enum BlockResult {
    BLOCK_SUCCESS = 0,
    BLOCK_FAILURE = -1,          // General or unspecified failure
    BLOCK_ERR_NULL_POINTER = -2, // Defensive check failed
    BLOCK_ERR_OUT_OF_MEMORY = -3,// Allocation failure
    BLOCK_ERR_FILE_IO = -4,      // Asset or file loading failed
    BLOCK_ERR_INVALID_PARAM = -5,// Bad argument passed to function
    BLOCK_ERR_INIT_FAILED = -6   // Subsystem initialization failed
} BlockResult;

// Fast string conversion for the logging system
const char* BlockGetErrorString(BlockResult Result);

char *CurrentRunningPath();
char *GetFileText(const char *FileName);