#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


char *CurrentRunningPath();
char *GetFileText(const char *filename);

#endif