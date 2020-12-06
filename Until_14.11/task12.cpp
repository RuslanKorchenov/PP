#include "mpi.h"
#include <cstdlib>

const int n = 4;
int main(int argc, char **argv)
{
    int rank, size;
    MPI_Status status;
    int array[n][n];
    int *vector = (int *)malloc(sizeof(int) * n);
    int summ = 0;
    int final_summ;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("array[n][n]:\n");
        for (int i = 0; i < n; i++)
        {
            vector[i] = 0;
            for (int j = 0; j < n; j++)
            {
                array[i][j] = rand() % 100;
                vector[i] += array[i][j];
                printf("%d, ", array[i][j]);
            }
            printf("\n");
        }
        
    }
    summ = 0;
    int cnt = n * n / size > n ? 2*n : n;
    int *result = new int[cnt];
    MPI_Scatter(array, cnt, MPI_INT, result, cnt, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < 12 / size; i++)
        summ += result[i];

    MPI_Reduce(&summ , &final_summ, 1, MPI_INT, MPI_MAX , 0, MPI_COMM_WORLD);

    printf("result[n] on %d:\n", rank);
    for (int i = 0; i < cnt; i++)
    {
        printf("%d, ", result[i]);
    }
    printf("\n");
    if (rank == 0)
        printf("Final summ: %d\n", final_summ);
    MPI_Finalize();
    return 0;
}
