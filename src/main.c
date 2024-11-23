#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "read_int.h"

int main(int argc, char* argv[]) {
    // Initialize MPI.
    MPI_Init(&argc, &argv);

    // Get process ID.
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    // Get number of MPI tasks.
    int process_count;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    // If main process.
    if(process_rank == 0) {
        int sequence_length;
        puts("Input sequence length: ");
        read_int(&sequence_length);

        int* sequence = (int*) calloc(sequence_length , sizeof(int));

        for(int i = 0; i < sequence_length; i++) {
            printf("Input number (%d/%d): ", i + 1, sequence_length);
            read_int(&sequence[i]);
            putc('\n', stdout);
        }

        // Iterator starts from 1 since process 0 isn't responsible for handling the sort verification.
        for(int i = 1; i < process_count; i++) {
            // Send the sequence length to processes.
            MPI_Send(&sequence_length, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

            // Send the sequence to processes.
            MPI_Send(&sequence_length, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        int index;
        int order_breaks_after = -1;
        for(int i = 1; i < process_count; i++) {
            MPI_Recv(&index, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if(index >= 0)
                order_breaks_after = index;
        }

        if(order_breaks_after == -1) {
            puts("Array is in ascending order\n");
        }
        else
            printf("Sequence is not in ascending order, breakpoint at: %d\n", order_breaks_after);

        free(sequence);
        sequence = NULL;
    }
    else {
        int order_breaks_after = -1;
        int* sequence = NULL;
        int sequence_length;

        // Receive sequence length.
        MPI_Recv(&sequence_length, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sequence = (int*) calloc(sequence_length , sizeof(int));

        // Receive the sequence
        MPI_Recv(sequence, sequence_length, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Distribute the workload to the processes.
        for(int i = process_rank - 1; i < sequence_length - 1; i += (process_count - 1)) {
            // if nth element is less than n+1th element (aka not in ascending order).
            if(sequence[i] > sequence[i + 1]) {
                order_breaks_after = i;
            }
        }

        // Send back (to process 0) the index of the sequence at which the ascending order is no longer adhered to.
        MPI_Send(&order_breaks_after, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        free(sequence);
        sequence = NULL;
    }

    // Done.
    MPI_Finalize();
    return EXIT_SUCCESS;
}


