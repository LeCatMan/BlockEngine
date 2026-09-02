#include "Utilities.hpp"

char CurrentRunningPath[1024];

// It get the current running path and adds it as a global.
// You can use it by including Utilities.hpp and call CurrentRunningPath.
void GetCurrentRunningPath()
{

    if (getcwd(CurrentRunningPath, sizeof(CurrentRunningPath)) == NULL) 
    {
        if (errno == ERANGE)
        {
            error("Path is too long! Buffer size of %zu bytes is not enough.", sizeof(CurrentRunningPath));
        }
        else
        {
            error("Failed to get current working directory: %s", strerror(errno));
        }
        return;
    }
    else
    {
        info("The current running path is: %s", CurrentRunningPath);
        return;
    }
    

}

// Get text that is in a file.
char *GetFileText(const char *FileName)
{

    #pragma region Open the file
    FILE *File = fopen(FileName, "rb");
    if (File == NULL)
        return NULL;
    #pragma endregion

    #pragma region Allocate space for the text
    fseek(File, 0, SEEK_END);
    long Sizw = ftell(File);
    rewind(File);

    char *Text = (char *)malloc(Sizw + 1);

    if (Text == NULL)
    {
        fclose(File);
        return NULL;
    }
    #pragma endregion

    #pragma region Get the text
    fread(Text, 1, Sizw, File);
    Text[Sizw] = '\0';
    fclose(File);
    #pragma endregion
    
    return Text;

}

// Fast string conversion for the logging system.
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

