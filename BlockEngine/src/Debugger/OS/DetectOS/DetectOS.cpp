#include <stdio.h>
/**
 * @brief Detects and prints the current operating system.
 *
 * Prints a colored message indicating Linux, MacOS, or unknown OS.
 */
void DetectOS() {
#include <stdio.h>
#if defined(_WIN32)
    printf("\033[1;36mDetected OS: Windows\033[0m\n");
#elif defined(__APPLE__) && defined(__MACH__)
    printf("\033[1;36mDetected OS: macOS\033[0m\n");
#elif defined(__linux__)
    printf("\033[1;36mDetected OS: Linux\033[0m\n");
#else
    printf("\033[1;31mDetected OS: Unknown\033[0m\n");
#endif
}