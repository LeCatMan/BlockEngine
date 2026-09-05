#pragma once

typedef enum BlockResult {
    BLOCK_SUCCESS_TRUE      =  1,  // Operation succeeded, result is TRUE
    BLOCK_SUCCESS_FALSE     =  0,  // Operation succeeded, result is FALSE
    BLOCK_FAILURE           = -1,  // General failure
    BLOCK_ERR_NULL_POINTER  = -2,
    BLOCK_ERR_OUT_OF_MEMORY = -3,
    BLOCK_ERR_FILE_IO       = -4,
    BLOCK_ERR_INVALID_PARAM = -5,
    BLOCK_ERR_INIT_FAILED   = -6
} BlockResult;

// Fast string conversion for the logging system
const char* BlockGetErrorString(BlockResult Result);
