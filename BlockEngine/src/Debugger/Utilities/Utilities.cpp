#include "Utilities.hpp"



char *CurrentRunningPath()
{
    char RunningPath[1024];
    char *err_msg = strerror(errno);

    if (getcwd(RunningPath, sizeof(RunningPath)) == NULL) 
    {
        if (errno == ERANGE)
        {
            error("Path is too long! Buffer size of %zu bytes is not enough.", sizeof(RunningPath));
        }
        else
        {
            error("Failed to get current working directory: %s", strerror(errno));
        }
        return NULL;
    }
    else
    {
        return RunningPath;
        printf("%s\n", RunningPath);
    }
}

char *GetFileText(const char *FileName)
{
    FILE *file = fopen(FileName, "rb");

    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *text = (char *)malloc(size + 1);

    if (text == NULL)
    {
        fclose(file);
        return NULL;
    }

    fread(text, 1, size, file);

    text[size] = '\0';

    fclose(file);

    return text;
}

const char* BlockGetErrorString(BlockResult Result) {
    switch (Result) {
        case BLOCK_SUCCESS:           return "SUCCESS";
        case BLOCK_FAILURE:           return "FAILURE";
        case BLOCK_ERR_NULL_POINTER:  return "ERR_NULL_POINTER";
        case BLOCK_ERR_OUT_OF_MEMORY: return "ERR_OUT_OF_MEMORY";
        case BLOCK_ERR_FILE_IO:       return "ERR_FILE_IO";
        case BLOCK_ERR_INVALID_PARAM: return "ERR_INVALID_PARAM";
        case BLOCK_ERR_INIT_FAILED:   return "ERR_INIT_FAILED";
        default:                      return "UNKNOWN_ERROR";
    }
}

