#include "mpi.h"
#include <cstdlib>
#include <string.h>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Status status;
    int received[6];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        MPI_Datatype triangle_type;
        int a[3][3];
        printf("Матрица 3х3:\n");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j < i)
                    a[i][j] = 0;
                else
                    a[i][j] = rand() % 10;
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        int lengths[3] = {3, 2, 1};
        int displacements[3] = {0, 4, 8};
        MPI_Type_indexed(3, lengths, displacements, MPI_INT, &triangle_type);
        MPI_Type_commit(&triangle_type);
        MPI_Send(a, 1, triangle_type, 1, 0, MPI_COMM_WORLD);
    }
    if (rank == 1)
        MPI_Recv(&received, 6, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Bcast(received, 6, MPI_INT, 1, MPI_COMM_WORLD);

    if (rank > 1)
    {
        printf("Rank = %d received:\n", rank);
        for (int i = 0; i < 6; i++)
            printf("%d ", received[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
