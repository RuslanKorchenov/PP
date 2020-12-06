#include "mpi.h"
#include <cstdlib>

int main(int argc, char **argv) {
    int rank, size;
    int a[10];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        for (int i = 0; i < 10; i++)
            a[i] = rand() % 100;
        printf("a[10]:\n");
        for (int i = 0; i < 10; i++)
            printf("%d\n", a[i]);   
        MPI_Send(a, 10, MPI_INT, 1, 10, MPI_COMM_WORLD);
     
    } else if (rank == 1)
    {
        printf("b[10]:\n");
        int b[10];
        MPI_Recv(b , 10 , MPI_INT, 0, 10, MPI_COMM_WORLD , &status);
            for (int i = 0; i < 10; i++)
                printf("%d\n", b[i]);
    }
    MPI_Finalize();
    return 0;
}