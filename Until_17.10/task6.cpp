#include "mpi.h"
#include <cstdlib>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Status status;
    int a = 1, b = 1;
    int *x, *y;
    int z = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank > 0)
    {
        int cnt;
        MPI_Probe(0, rank, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &cnt);
        x = (int *)malloc(sizeof(int) * cnt);
        y = (int *)malloc(sizeof(int) * cnt);
        MPI_Recv(x, cnt, MPI_INT, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(y, cnt, MPI_INT, 0, rank * 25, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int temp = 0;
        for (int i = 0; i < cnt; i++)
            temp += x[i] * a + y[i] *b; 

        printf("Полученный vector_x на процессе = %d\n", rank);
        for (int j = 0; j < cnt; j++)
            printf("%d, ", x[j]);
        printf("\n");
        printf("Полученный vector_y на процессе = %d\n", rank);
        for (int j = 0; j < cnt; j++)
            printf("%d, ", y[j]);
        printf("\n");
        
        MPI_Send(&temp, 1, MPI_INT, 0, rank*35, MPI_COMM_WORLD);
    }
    if (rank == 0)
    {
        int vector_x[12];
        int vector_y[12];
        int temp = 0;
        int cnt = 12 / size; 
        int tmp_cnt;

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
        printf("Полученный vector_x на процессе = %d\n", rank);
        for (int j = 0; j < cnt; j++)
            printf("%d, ", vector_x[j]);
        printf("\n");
        printf("Полученный vector_y на процессе = %d\n", rank);
        for (int j = 0; j < cnt; j++)
            printf("%d, ", vector_y[j]);
        printf("\n");

        for (int i = 0; i < cnt; i++)
            z += vector_x[i] * a + vector_y[i] *b; 
        for (int i = 1; i < size; i++)
        {
            tmp_cnt = cnt;
            if (i + 1 == size)
                tmp_cnt = 12 - (i * cnt);
            MPI_Send(&vector_x[i * cnt], tmp_cnt, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(&vector_y[i * cnt], tmp_cnt, MPI_INT, i, i * 25, MPI_COMM_WORLD);
        }
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&temp, 1, MPI_INT, i, i*35, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            z += temp;
        }
        printf("z = %d\n", z);
    }
    MPI_Finalize();
    return 0;
}
