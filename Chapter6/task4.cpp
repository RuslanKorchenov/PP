#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char buffer[1000];
    int position = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int ints[10];
        double doubles[8];
        for (int i = 0; i < 10; i++)
        {
            ints[i] = i;
            if (i < 8)
                doubles[i] = i + 0.1;
        }
        MPI_Pack(ints, 10, MPI_INT, buffer, 1000, &position, MPI_COMM_WORLD);
        MPI_Pack(doubles, 8, MPI_DOUBLE, buffer, 1000, &position, MPI_COMM_WORLD);
        MPI_Send(buffer, position, MPI_PACKED, 1, 1, MPI_COMM_WORLD);
    }

    if (rank == 1)
    {
        int new_ints[10];
        double new_doubles[8];
        MPI_Recv(buffer, 1000, MPI_PACKED, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Unpack(buffer, 1000, &position, new_ints, 10, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, 1000, &position, new_doubles, 8, MPI_DOUBLE, MPI_COMM_WORLD);
        printf("Unpack result:\nInt array:\n");
        for (int i = 0; i < 10; i++)
            printf("%d ", new_ints[i]);
        printf("\nDouble array:\n");
        for (int i = 0; i < 8; i++)
            printf("%f ", new_doubles[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}