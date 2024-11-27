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
   	read_int(&option, 0);
	if((option != 1) && (option != 2)) {
        	goto invalid_option;
	}

	if(option == 2) {
		/* Terminating, MPI_Finalize() hangs so MPI_Abort() is required. May or may not show a warning
		based on MPI implementation used */
		MPI_Abort(MPI_COMM_WORLD, 1);
		exit(0);
	}

	system("clear");
}
