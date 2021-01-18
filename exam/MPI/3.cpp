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
        printf("Отправленный с процесса 0 - Исходный массив a[10]:\n");
        for (int i = 0; i < 10; i++)
            printf("%d, ", a[i]);
        printf("\n");   
        for (int i = 1; i < size; i++)
            MPI_Send(a, 10, MPI_INT, i, 10, MPI_COMM_WORLD);
     
    } else if (rank != 0)
    {
        int temp;
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &temp);
        int *b = (int *)malloc(sizeof(int) * temp);
        MPI_Recv(b , 10 , MPI_INT, 0, 10, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            printf("Полученный массив на процессе = %d\n", rank);
            for (int i = 0; i < 10; i++)
                printf("%d, ", b[i]);
            printf("\n");
        free(b);
    }
    MPI_Finalize();
    return 0;
}