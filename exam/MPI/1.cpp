#include <mpi.h>
#include <stdio.h>
 
int main(int argc, char** argv) {
 
   	MPI_Init(&argc, &argv);
 
   	int rank;
   	int size;
 
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
 
   	printf("The number of the process is: %d, number of common processes is: %d\n", rank, size);
 
   	MPI_Finalize();
}
