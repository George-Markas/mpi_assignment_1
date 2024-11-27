#include <string.h>
#include <ctype.h>

/* Provides validity checking for read_int() */
int input_sanitizer(const char *buffer, int allow_negative) {

    // In case of empty input, even if NULL macro is not defined
    if(buffer == NULL || *buffer == '\0')
        return 0;

    // Handle sign
    int i = 0;
    if(buffer[0] == '-') {
        if(allow_negative) {
            i++;
        } else {
            return 0;
        }
    }

    // In case input is just a newline
    if(buffer[i] == '\n')
        return 0;

    for(; buffer[i] != '\n'; i++) {
        if(!isdigit(buffer[i]))
            return 0;
    }

    return 1;
}