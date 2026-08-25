#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int LoggerInit(void);
int LoggerShutdown(void);
int Error(const char* msg, const char* file, int line);
int Trace(const char* msg, const char* file, int line);
int Info(const char* msg, const char* file, int line);
int Warning(const char* msg, const char* file, int line);
int Debug(const char* msg, const char* file, int line);

// Log error with the file and line location.
#define error(msg) Error(msg, __FILE__, __LINE__)
// Log trace with the file and line location.
#define trace(msg) Trace(msg, __FILE__, __LINE__)
// Log info with the file and line location.
#define info(msg) Info(msg, __FILE__, __LINE__)
// Log warning with the file and line location.
#define warning(msg) Warning(msg, __FILE__, __LINE__)
// Log debug with the file and line location.
#define debug(msg) Debug(msg, __FILE__, __LINE__)