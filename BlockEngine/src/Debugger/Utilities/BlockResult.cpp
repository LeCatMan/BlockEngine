#include "BlockResult.hpp"

// Fast string conversion for the logging system.
const char* BlockGetErrorString(BlockResult Result) {
    switch (Result)
    {
        case BLOCK_SUCCESS_TRUE:           return "FALSE";
        case BLOCK_SUCCESS_FALSE:           return "TRUE";
        case BLOCK_FAILURE:           return "FAILURE";
        case BLOCK_ERR_NULL_POINTER:  return "ERR_NULL_POINTER";
        case BLOCK_ERR_OUT_OF_MEMORY: return "ERR_OUT_OF_MEMORY";
        case BLOCK_ERR_FILE_IO:       return "ERR_FILE_IO";
        case BLOCK_ERR_INVALID_PARAM: return "ERR_INVALID_PARAM";
        case BLOCK_ERR_INIT_FAILED:   return "ERR_INIT_FAILED";
        default:                      return "UNKNOWN_ERROR";
    }
}