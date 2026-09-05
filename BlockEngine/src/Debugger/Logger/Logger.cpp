#include "Logger.hpp"

typedef struct {
    int r;
    int g;
    int b;
} LColor;

// ########################
// #       Colors         #
// ########################

const LColor LIGHTGRAY = {144,144,144};
const LColor DARKGRAY = {80,80,80};
const LColor BLACK = {0,0,0};
const LColor RED = {255,0,0};
const LColor PINK = {255,0,255};
const LColor LIGHTPURPLE = {180,0,255};
const LColor PURPLE = {120,0,0};
const LColor BLUE = {0,0,255};
const LColor LIGHTBLUE = {44,135,255};
const LColor CYAN = {0,255,255};
const LColor BLUEGREEN = {0,255,100};
const LColor GREEN = {180,0,255};
const LColor YELLOWGREEN = {120,255,0};
const LColor YELLOW = {255,255,0};
const LColor ORANGE = {255,130,0};

// ########################
// #      Text Styles     #
// ########################
#define Bold "1"
#define Dim "2"
#define Italic "3"	
#define Underline "4"
#define SlowBlink "5"
#define FastBlink "6"
#define ReverseCs "7"
#define Hidden "8"
#define Strikethrough "9"

#define Reset "\x1b[0m"

// Reset specific styles.
#define NormalIntensity "22"
#define NotItalic "23"
#define NoUnderline "24"
#define NoBlink "25"
#define NoReverse "27"
#define RevealText "28"
#define NoStrikeThrough "29"

// Reset Foreground and BackGround.
#define ResetForeground "39"
#define ResetBackground "49"
#define Background "48;2"
#define Foreground "38;2"

// ########################
// #   Basic ANSI Cs  #
// ########################

// Foreground
#define Black   "30"
#define Red     "31"
#define Green   "32"
#define Yellow  "33"
#define Blue    "34"
#define Magenta "35"
#define Cyan    "36"
#define White   "37"

// Bright Foreground
#define BrightBlack   "90"
#define BrightRed     "91"
#define BrightGreen   "92"
#define BrightYellow  "93"
#define BrightBlue    "94"
#define BrightMagenta "95"
#define BrightCyan    "96"
#define BrightWhite   "97"

// Background
#define BlackBackground   "40"
#define RedBackground     "41"
#define GreenBackground   "42"
#define YellowBackground  "43"
#define BlueBackground    "44"
#define MagentaBackground "45"
#define CyanBackground    "46"
#define WhiteBackground   "47"

// Bright Background
#define BrightBlackBackground   "100"
#define BrightRedBackground     "101"
#define BrightGreenBackground   "102"
#define BrightYellowBackground  "103"
#define BrightBlueBackground    "104"
#define BrightMagentaBackground "105"
#define BrightCyanBackground    "106"
#define BrightWhiteBackground   "107"

// Default
#define DefaultForeground "39"
#define DefaultBackground "49"

// ########################
// #        Logger        #
// ########################

// Global file pointer for the error log
static FILE* GlobalErrorFile = NULL;

// Initialize logger at the programs start.
BlockResult LoggerInit()
{
    
    #pragma region Timestamp Setup
    // those are just to put the time to the hard-coded logs.
    char TimeBuffer[64];
    time_t Time = time(NULL);
    strftime(TimeBuffer, sizeof(TimeBuffer), "%Ih %Mm %Ss %p", localtime(&Time));
    #pragma endregion

    #pragma region Log File and Output Configuration
    char FailSafe[1124];         // Overflow protection for huge log strings
    const char* FolderName = "Logs"; // the folder name.
    char FileName[1024];         // The file location.
    int Number = 1;                 // Index used for auto-incrementing log filenames
    #pragma endregion

    #pragma region Makes sure folder exists
    char MakeDir_cmd[1024];
    snprintf(MakeDir_cmd, sizeof(MakeDir_cmd), "mkdir -p %s", FolderName);
    if (system(MakeDir_cmd) == 0)
    {
        #pragma region Creates the folder if it doesnt exist
        while (true)
        {
            int FilePath = snprintf(FileName, sizeof(FileName), "%s/Log-%03d.txt", FolderName, Number);

            if(FilePath < 0 || FilePath >= sizeof(FileName))
            {
                snprintf(FailSafe, sizeof(FailSafe), "rm %s/*", FolderName);
                system(FailSafe);
            }

            snprintf(FileName, sizeof(FileName), "%s/Log-%03d.txt", FolderName, Number);
            FILE* f = fopen(FileName, "r");
            if (!f) break; // file doesn't exist then use it
            fclose(f);
            Number++;
        }
        #pragma endregion
    }
    else
    {
        printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, Bold ";" SlowBlink ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Logger Failed to create directory!");
        return BLOCK_ERR_FILE_IO;
    }
    #pragma endregion

    #pragma region Opens the file
    GlobalErrorFile = fopen(FileName, "w");
    if (!GlobalErrorFile) 
    {
        printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1mCannot open:%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, Bold ";" SlowBlink ";" "31", "ERROR", "Error", __FILE__, __LINE__, FileName);
        return BLOCK_ERR_FILE_IO;
    }
    #pragma endregion

    #pragma region Init message
    printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1mLogger initialized: %s\033[0m>\n", TimeBuffer, Bold, "INFO", "Info", __FILE__, __LINE__, FileName);
    fprintf(GlobalErrorFile, "[%s] [INFO] -> Info in <%s> at line <%d>: <Logger initialized: %s>\n", TimeBuffer, __FILE__, __LINE__, FileName);
    fflush(GlobalErrorFile);
    // completely innocent startup code
    // absolutely nothing suspicious here
    // definitely just starting the logger
    dont_find_out_what_i_do();
    return BLOCK_SUCCESS_TRUE;
    #pragma endregion

}


// Shutdown logger at the programs end.
BlockResult LoggerShutdown()
{

    #pragma region Timestamp Setup
    // those are just to put the time to the hard-coded logs.
    char TimeBuffer[64];
    time_t Time = time(NULL);
    strftime(TimeBuffer, sizeof(TimeBuffer), "%Ih %Mm %Ss %p", localtime(&Time));
    #pragma endregion

    // Check if the error file is true if it is, it will continue as is and if not it will return BLOCK_FAILURE
    #pragma region Close the error file
    if (GlobalErrorFile)
    {
        Info("Logger shutdown!", __FILE__, __LINE__);
        fclose(GlobalErrorFile);
        GlobalErrorFile = NULL;
        return BLOCK_SUCCESS_TRUE;
    }
    else
    {
        printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, Bold ";" SlowBlink ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Failed to shutdown logger!");
        return BLOCK_FAILURE;
    }
    #pragma endregion

}


// A template function to make other logger function
BlockResult Template(const char* Message, const char* File, int Line, const char* CapitalType, const char* Type, const char* Color)
{

    #pragma region Timestamp Setup
    // those are just to put the time to the hard-coded logs.
    char TimeBuffer[64];
    time_t Time = time(NULL);
    strftime(TimeBuffer, sizeof(TimeBuffer), "%Ih %Mm %Ss %p", localtime(&Time));
    #pragma endregion

    #pragma region Printing to the Console
    // Console output
    printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, Color, CapitalType, Type, File, Line, Message);
    #pragma endregion

    #pragma region Printing to the File
    // File output
    if (GlobalErrorFile) {
        fprintf(GlobalErrorFile, "[%s] [%s] -> %s in <%s> at line <%d>: <%s>\n", TimeBuffer, CapitalType, Type, File, Line, Message);
        fflush(GlobalErrorFile); // ensure it's written immediately
        return BLOCK_SUCCESS_TRUE;
    }
    
    printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, Bold ";" SlowBlink ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Failed to output an error to file!");
    #pragma endregion
    
    return BLOCK_ERR_FILE_IO;

}


// Log error with the file and line location and time.
BlockResult Error(const char* Message, const char* File, int Line)
{
    return Template(Message, File, Line, "ERROR", "Error", Bold ";" SlowBlink ";" "31");
}


// Log trace with the file and line location and time.
BlockResult Trace(const char* Message, const char* File, int Line)
{
    return Template(Message, File, Line, "TRACE", "Trace", Bold ";" Foreground ";44;135;255");
}


// Log info with the file and line location and time.
BlockResult Info(const char* Message, const char* File, int Line)
{
    return Template(Message, File, Line, "INFO", "Info", Bold);
}


// Log warning with the file and line location and time.
BlockResult Warning(const char* Message, const char* File, int Line)
{
    return Template(Message, File, Line, "WARNING", "Warning", Bold ";" SlowBlink ";" Foreground ";255;170;50");
}


// Log debug with the file and line location and time.
BlockResult Debug(const char* Message, const char* File, int Line)
{
    return Template(Message, File, Line, "DEBUG", "Debug", Bold ";" Foreground ";255;0;255");
}


// Log audio with the file and line location and time.
BlockResult AudioLog(const char* Message, const char* File, int Line)
{
    return Template(Message, File, Line, "AUDIO", "Audio", Bold ";" Foreground ";36;226;120");
}


// Log rendering with the file and line location and time.
BlockResult Rendering(const char* Message, const char* File, int Line)
{
    return Template(Message, File, Line, "RENDERING", "Rendering", Bold ";" Foreground ";150;79;217");
}


// Special ... ;)
BlockResult Special(const char* Message, const char* File, int Line)
{
    const char* Colors[] = {
        "255;0;0",
        "255;130;0",
        "255;255;0",
        "180;255;0",
        "0;255;100",
        "0;255;255",
        "44;135;255",
        "120;0;255",
        "255;0;255"
    };

    size_t Length = strlen(Message);

    for (int Cycle = 0; Cycle < 3; Cycle++)
    {
        for (int Frame = 0; Frame < 30; Frame++)
        {
            printf("\r\033[K");

            for (size_t i = 0; i < Length; i++)
            {
                if ((rand() % 5) == 0)
                    printf(" ");
                else
                    printf("\033[38;2;%sm%c\033[0m", Colors[(i + Frame) % 9], Message[i]);
            }

            fflush(stdout);
            usleep(50000);
        }
    }

    printf("\r\033[K");

    for (size_t i = 0; i < Length; i++)
        printf("\033[38;2;%sm%c\033[0m", Colors[i % 9], Message[i]);

    printf("\n");
    fflush(stdout);

    if (GlobalErrorFile)
    {
        fprintf(GlobalErrorFile, "[SPECIAL] -> <%s>\n", Message);
        fflush(GlobalErrorFile);
    }

    return BLOCK_SUCCESS_TRUE;
}


