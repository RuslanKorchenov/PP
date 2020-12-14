#include "mpi.h"
#include <cstdlib>
#include <string.h>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int a[8][8];

        printf("a[8][8]:\n");
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                a[i][j] = rand() % 100;
                printf("%d, ", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        MPI_Datatype columns;
        MPI_Type_vector(4, 8, 16, MPI_INT, &columns);
        MPI_Type_commit(&columns);
        MPI_Send(&a[0][0], 1, columns, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&a[1][0], 1, columns, 1, 2, MPI_COMM_WORLD);
    }
    if (rank == 1)
    {
        int b[4][8];
        int c[4][8];

        // Получение массива b - c четными строками
        MPI_Recv(b, 4 * 8, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("b[4][8]:\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%d, ", b[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        // Получение массива с - c нечетными строками
        MPI_Recv(c, 4 * 8, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("c[4][8]:\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%d, ", c[i][j]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
