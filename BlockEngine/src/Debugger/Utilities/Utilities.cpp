#include "Utilities.hpp"

char CurrentRunningPath[1024];

// It get the current running path and adds it as a global.
// You can use it by including Utilities.hpp and call CurrentRunningPath.
void GetCurrentRunningPath()
{

    #pragma region Timestamp Setup
    // those are just to put the time to the hard-coded logs.
    char TimeBuffer[64];
    time_t Time = time(NULL);
    strftime(TimeBuffer, sizeof(TimeBuffer), "%Ih %Mm %Ss %p", localtime(&Time));
    #pragma endregion

    if (getcwd(CurrentRunningPath, sizeof(CurrentRunningPath)) == NULL) 
    {
        if (errno == ERANGE)
        {
            printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1mCannot open:%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, "1" ";" "5" ";" "31", "ERROR", "Error", __FILE__, __LINE__, ("Path is too long!"));
        }
        else
        {
            printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1mCannot open:%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, "1" ";" "5" ";" "31", "ERROR", "Error", __FILE__, __LINE__, ("Failed to get current working directory: %s", strerror(errno)));
        }
        return;
    }
    else
    {
        printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, "1", "INFO", "Info", __FILE__, __LINE__, ("The current running path is: %s", CurrentRunningPath));
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


