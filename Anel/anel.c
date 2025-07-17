#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size, rank, valor = -1;
    int prev, next;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    prev = (rank == 0) ? (size - 1) : (rank - 1);
    next = (rank + 1) % size;

    if (rank == 0) {
        valor = 10;
        MPI_Send(&valor, 1, MPI_INT, next, 0, comm);
    }

    while (valor != 0) {
        MPI_Recv(&valor, 1, MPI_INT, prev, 0, comm, MPI_STATUS_IGNORE);

        if (rank == 0) {
            valor--;
            printf("Processo 0 decrementou o valor para %d\n", valor);
        } else {
            printf("Processo %d recebeu valor %d\n", rank, valor);
        }

        MPI_Send(&valor, 1, MPI_INT, next, 0, comm);
    }

    MPI_Finalize();
    return 0;
}
