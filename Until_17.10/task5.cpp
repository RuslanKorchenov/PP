#include "mpi.h"
#include <cstdlib>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Status status;
    int temp;
    int *b;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank > 0)
    {
        int cnt;
        MPI_Probe(0, rank, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &cnt);
        b = (int *)malloc(sizeof(int) * cnt);
        MPI_Recv(b, 12 / size + 1, MPI_INT, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Полученный массив на процессе = %d\n", rank);
        for (int j = 0; j < cnt; j++)
            printf("%d, ", b[j]);
        printf("\n");
        free(b);
    }
    if (rank == 0)
    {
        int a[12];
        for (int i = 0; i < 12; i++)
            a[i] = rand() % 100;
        printf("Отправленный с процесса 0 - Исходный массив a[12]:\n");
        for (int i = 0; i < 12; i++)
            printf("%d, ", a[i]);
        printf("\n"); 
        temp = 12 / size + 1; 
        for (int i = 1; i < size; i++)
        {
            if ((temp * i + (12 / size + 1)) > 12)
                temp = 12 - temp * i;
            
            MPI_Send(&a[i * (12 / size + 1)], temp, MPI_INT, i, i, MPI_COMM_WORLD);
        }
        printf("Полученный массив на процессе = %d\n", rank);
        for (int j = 0; j < 12 / size + 1; j++)
            printf("%d, ", a[j]);
        printf("\n"); 
    }
    MPI_Finalize();
    return 0;
}
