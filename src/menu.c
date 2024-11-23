#include <stdio.h>
#include <stdlib.h>

#include "read_int.h"

void wipe_previous_input() {
	// Regarding VT100 escape codes:
	// https://web.archive.org/web/20121225024852/http://www.climagic.org/mirrors/VT100_Escape_Codes.html

	// Save cursor position
	fputs("\033[s" , stdout);

	// Move 4 characters right
	fputs("\033[4C" , stdout);

	// Clear the rest of the line
	fputs("\033[K" , stdout);

	// Restore cursor to its original position
	fputs("\033[u" , stdout);
	fflush(stdout);
}

void menu() {
	fputs("\n ┌Select option──────────────┐\n"
          " │                           │\n"
          " │        1. Continue        │\n"
          " │        2. Exit            │\n"
          " │                           │\n"
          " └───────────────────────────┘\n"
          "  > ", stdout);

	int option = -1;
	read_int(&option);

	while((option != 1) && (option != 2)) {
		read_int(&option);
		wipe_previous_input();
	}

	if(option == 2) {
		// Terminate program
		exit(0);
	}

	fputs("\033[K",stdout);
	fflush(stdout);
}

