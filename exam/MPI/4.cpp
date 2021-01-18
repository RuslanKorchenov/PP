#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <cmath>
 
int main(int argc, char** argv) {
 
   	int rank, size, result;
   	MPI_Init(&argc, &argv);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	int* send = new int[400];
   	int* recv = new int[400];
   	if (rank == 0) {
         	for (int i = 0; i < 100; i++) {
                	send[i] = rand() % 100;
         	}
   	}
   	MPI_Scatter(send, 100, MPI_INT, recv, 100, MPI_INT, 0, MPI_COMM_WORLD);
   	MPI_Barrier(MPI_COMM_WORLD); // блокирует вызывающий процесс, пока все процессы группы не вызовут её.
   	int fractionalResult = 0;
   	for (int i = 0; i < 100; i++) {
         	fractionalResult += abs(recv[i]);
   	}
   	MPI_Reduce(&fractionalResult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   	if (rank == 0) printf("result = %i \n", result);
   	MPI_Finalize();
   	return 0;
}
