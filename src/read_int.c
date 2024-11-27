#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "input_sanitizer.h"

#define BUFFER_SIZE 1024

/* Reads an integer from stdin with built-in, optional validity check for non-ints and (also) optionally negative ints,
   safe(er maybe) replacement for scanf. */

/* int read_int(int* var, int validity_check_enabled, int allow_negative)

where validity_check_enabled checks for the input's validity if true and allow_negative (applicable only when
validity_check_enabled is true) specifies whether to let negative integers pass the check or not */

// ReSharper disable once CppNotAllPathsReturnValue
int read_int(int* var, ...) {
    va_list args;
    va_start(args, var);

    char buffer[BUFFER_SIZE];

    // If read fails, stop
    if(!fgets(buffer, BUFFER_SIZE, stdin))
       return EXIT_FAILURE;

    int validity_check_enabled = va_arg(args, int);
    if(validity_check_enabled) {
        int allow_negative = va_arg(args, int);
        char *str = "n";

        if (!allow_negative)
            str = " non-negative";

        va_end(args);

        while (!input_sanitizer(buffer, allow_negative)) {
            printf("\n\033[3;31mInvalid, must be a%s integer! Retry...\033[0m\n", str);
            fgets(buffer, BUFFER_SIZE, stdin);
        }
    }

    const int val = (int) strtol(buffer, NULL, 10);
    *var = val;
}
