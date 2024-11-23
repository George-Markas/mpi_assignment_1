#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/* Reads an integer from stdin, safe(er) replacement for scanf. */

// ReSharper disable once CppNotAllPathsReturnValue
int read_int(int *var) {
    char buffer[BUFFER_SIZE];

    // If read fails, stop
    if(!fgets(buffer, BUFFER_SIZE, stdin))
       return EXIT_FAILURE;

    const int val = (int) strtol(buffer, NULL, 10);
    *var = val;
}
