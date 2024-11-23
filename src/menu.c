#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "read_int.h"

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