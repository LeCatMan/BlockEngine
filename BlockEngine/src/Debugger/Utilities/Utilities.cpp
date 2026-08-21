#include "Utilities.hpp"

char RunningPath[4096];

char *CurrentRunningPath()
{

    if (getcwd(RunningPath, sizeof(RunningPath)) == NULL) {
        perror("getcwd");
    } else {
        printf("%s\n", RunningPath);
    }
    
    return RunningPath;
}


char *GetFileText(const char *filename)
{
    FILE *file = fopen(filename, "rb");

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
