#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int args, char** argv)
{
   	MPI_Status status;
   	int rank;
   	int size;

   	MPI_Init(&args, &argv);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);

   	if (rank == 0) {
         	int a[10];
         	for (int i = 0; i < 10; i++) {
                	a[i] = rand() % 100;
         	}
         	MPI_Send(a, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
   	}
   	if (rank == 1) {
         	int a[10];
         	MPI_Recv(a, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
         	for (int i = 0; i < 10; i++) {
                	printf("%d ", a[i]);
         	}
   	}
 
   	MPI_Finalize();
}
