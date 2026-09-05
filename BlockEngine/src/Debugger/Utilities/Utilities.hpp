#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "../Logger/Logger.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

extern char RunningPath[1024];


void GetCurrentRunningPath();
char *GetFileText(const char *FileName);