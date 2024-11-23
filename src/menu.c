#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "read_int.h"

void wipe_previous_input() {
	// Regarding VT100 escape codes:
	// https://web.archive.org/web/20121225024852/http://www.climagic.org/mirrors/VT100_Escape_Codes.html

	// Save cursor position
	system("echo \033[s");

	// Move 4 characters right
//	system("echo \033[4C");

	// Clear the rest of the line
	system("echo \033[0K");

	// Restore cursor to its original position
	system("echo \033[u");
//	fflush(stdout);
}

void menu() {
  	invalid_option:
  	system("clear");
	fputs("\n ┌Select option──────────────┐\n"
          " │                           │\n"
          " │        1. Continue        │\n"
          " │        2. Exit            │\n"
          " │                           │\n"
          " └───────────────────────────┘\n", stdout);

	int option;
    read_int(&option);
	if((option != 1) && (option != 2)) {
          goto invalid_option;
	}

	if(option == 2) {
		// Terminate program, finalize hangs so abort is used. Run with quiet option to
        // suppress the error.
        MPI_Abort(MPI_COMM_WORLD, 1);
		exit(0);
	}

	system("clear");
}