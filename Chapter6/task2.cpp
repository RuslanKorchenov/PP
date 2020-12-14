#include "mpi.h"
#include <cstdlib>
#include <string.h>

struct array
{
    int column_1[8];
    int column_2[8];
};

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Status status;
    struct array my_array;
    int a[8][8];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            a[i][j] = rand() % 100;
        }
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int lengths[2] = {8, 8};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
    MPI_Datatype columns;

    MPI_Aint address[3];
    MPI_Aint displacements[2];
    MPI_Get_address(&my_array, &address[0]);
    MPI_Get_address(&(my_array.column_1[0]), &address[1]);
    MPI_Get_address(&(my_array.column_2[0]), &address[2]);
    displacements[0] = address[1] - address[0];
    displacements[1] = address[2] - address[0];

    MPI_Type_create_struct(2, lengths, displacements, types, &columns);
    MPI_Type_commit(&columns);

    if (rank == 0)
    {
        printf("a[8][8]:\n");
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                printf("%d, ", a[i][j]);
            printf("\n");
        }
        printf("\n");

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                my_array.column_1[j] = a[i][j];
                my_array.column_2[j] = a[i + 4][j];
            }
            MPI_Send(&my_array, 1, columns, i, i, MPI_COMM_WORLD);
        }
    }
    else
    {
        struct array new_array;
        MPI_Recv(&new_array, 1, columns, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Rank = %d array[2][8]:\n", rank);
        for (int i = 0; i < 8; i++)
            printf("%d, ", new_array.column_1[i]);
        printf("\n");
        for (int i = 0; i < 8; i++)
            printf("%d, ", new_array.column_2[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
