#include "mpi.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Status status;
    int vector_x[12];
    int vector_y[12];
    int summ = 0;
    int final_summ;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        for (int i = 0; i < 12; i++)
        {
            vector_x[i] = rand() % 100;
            vector_y[i] = rand() % 100;
        }
        printf("vector_x:\n");
        for (int i = 0; i < 12; i++)
            printf("%d, ", vector_x[i]);
        printf("\n");
        printf("vector_y:\n");
        for (int i = 0; i < 12; i++)
            printf("%d, ", vector_y[i]);
        printf("\n");
    }
    summ = 0;
    int *vector_result_x = new int[12 / size];
    int *vector_result_y = new int[12 / size];

    MPI_Scatter(vector_x, 12 / size, MPI_INT, vector_result_x, 12 / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector_y, 12 / size, MPI_INT, vector_result_y, 12 / size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < 12 / size; i++)
        summ += vector_result_x[i] * vector_result_y[i];
    
    MPI_Reduce(&summ , &final_summ, 1, MPI_INT, MPI_SUM , 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Final summ: %d\n", final_summ);

    MPI_Finalize();
    return 0;
}
