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
#define LocationC "38;2;30;255;30"


// ########################
// #       Examples       #
// ########################
// "\x1b[1m"  Bold
// "\x1b[2m"  Dim
// "\x1b[3m"  Italic
// "\x1b[4m"  Underline
// "\x1b[5m"  Slow blink
// "\x1b[6m"  Fast blink
// "\x1b[7m"  Reverse Cs
// "\x1b[8m"  Hidden
// "\x1b[9m"  Strikethrough

//\x1b[1;3;4;38;2;255;0;255m
//     │ │ │  └────── RGB ──────┘
//     │ │ └─ Underline
//     │ └─── Italic
//     └───── Bold
//printf("\x1b[1;3;4;38;2;255;0;255mHello\x1b[0m\n");


// "\x1b[38;2;255;0;0m"                       Foreground RGB
// "\x1b[48;2;0;0;0m"                         Background RGB
// "\x1b[38;2;255;0;0;48;2;0;0;0m"           Red foreground + black background
// "\x1b[1;38;2;255;255;255;48;2;0;100;200m" Bold + white foreground + blue background







// ########################
// #        Logger        #
// ########################

// Global file pointer for the error log
static FILE* G_error_file = NULL;

// Initialize logger at the programs start.
int LoggerInit() {
    
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
    char mkdir_cmd[1024];
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", FolderName);
    if (system(mkdir_cmd) != 0) {
        printf("[\033[1mINFO\033[0m] -> Info in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1mLogger initialized: %s\033[0m>\n", __FILE__, __LINE__, "Logger Failed to create directory!");
    }
    #pragma endregion

    #pragma region Creates the folder if it doesnt exist
    while (true)
    {
        snprintf(FileName, sizeof(FileName), "%s/Log-%03d.txt", FolderName, Number);
        if(sizeof(FileName) == 1024)
        {
            snprintf(FailSafe, sizeof(FailSafe), "rm %s/*", FolderName);
            system(FailSafe);
        }
        FILE* f = fopen(FileName, "r");
        if (!f) break; // file doesn't exist then use it
        fclose(f);
        Number++;
    }
    #pragma endregion

    #pragma region Opens the file
    G_error_file = fopen(FileName, "w");
    if (!G_error_file) 
    {
        printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1mCannot open:%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, Bold ";" SlowBlink ";" "31", "ERROR", "Error", __FILE__, __LINE__, FileName);
        return 1;
    }
    #pragma endregion

    #pragma region Init message
    printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1mLogger initialized: %s\033[0m>\n", TimeBuffer, Bold, "INFO", "Info", __FILE__, __LINE__, FileName);
    fprintf(G_error_file, "[%s] [INFO] -> Info in <%s> at line <%d>: <Logger initialized: %s>\n", TimeBuffer, __FILE__, __LINE__, FileName);
    fflush(G_error_file);
    #pragma endregion

    return 0;
}


// Close logger end.
int LoggerShutdown() {
    // 
    #pragma region Timestamp Setup
    // those are just to put the time to the hard-coded logs.
    char TimeBuffer[64];
    time_t Time = time(NULL);
    strftime(TimeBuffer, sizeof(TimeBuffer), "%Ih %Mm %Ss %p", localtime(&Time));
    #pragma endregion

    // Check if the error file is true if it is, it will continue as is and if not it will return 1
    #pragma region Close the error file
    if (G_error_file) {
        fclose(G_error_file);
        G_error_file = NULL;
        return 0;
    }
    else
    {
        printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", TimeBuffer, Bold ";" SlowBlink ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Failed to shutdown logger!");
        return 1;
    }
    #pragma endregion
}



int Template(const char* msg, const char* file, int line, const char* Ctype, const char* type, const char* C)
{
    time_t currentTime;
    struct tm *localTime;
    // Get the current time
    currentTime = time(NULL);
    // Convert to local time
    localTime = localtime(&currentTime);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Ih %Mm %Ss %p", localTime);

    // Console output
    printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", buffer, C, Ctype, type, file, line, msg);

    // File output
    if (G_error_file) {
        fprintf(G_error_file, "[%s] -> %s in <%s> at line <%d>: <%s>\n", Ctype, type, file, line, msg);
        fflush(G_error_file); // ensure it's written immediately
        return 0;
    }
    
    printf("[\033[1m%s\033[0m] [\033[%sm%s\033[0m] -> %s in <\033[1m%s\033[0m> at line <\033[1m%d\033[0m>: <\033[1m%s\033[0m>\n", buffer, Bold ";" SlowBlink ";" "31", "ERROR", "Error", __FILE__, __LINE__, "Failed to output an error to file!");
    return 1;
}


// Log error with the file and line location.
int Error(const char* msg, const char* file, int line)
{
    return Template(msg, file, line, "ERROR", "Error", Bold ";" SlowBlink ";" "31");
}


// ------------------------
// Log trace with the file and line location.
int Trace(const char* msg, const char* file, int line)
{
    return Template(msg, file, line, "TRACE", "Trace", Bold ";" Foreground ";44;135;255");
}

// ------------------------
// Log info with the file and line location.
int Info(const char* msg, const char* file, int line)
{
    return Template(msg, file, line, "INFO", "Info", Bold);
}

// ------------------------
// Log warning with the file and line location.
int Warning(const char* msg, const char* file, int line)
{
    return Template(msg, file, line, "WARNING", "Warning", Bold ";" SlowBlink ";" Foreground ";255;170;50");
}

// ------------------------
// Log debug with the file and line location.
int Debug(const char* msg, const char* file, int line)
{
    return Template(msg, file, line, "DEBUG", "Debug", Bold ";" Foreground ";255;0;255");
}