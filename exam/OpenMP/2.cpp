#include <iostream>
#include <omp.h>
#include <stdio.h>
 
 
int main()
{
   	omp_set_num_threads(3);
#pragma omp parallel if ((int)omp_get_num_threads > 1)
   	{
        printf("Total threads - %d\n", omp_get_num_threads());
        printf("Current thread id : %d\nHello world!\n", omp_get_thread_num());
   	}
   	printf("First block has been completed \n");

   	omp_set_num_threads(1);
#pragma omp parallel if ((int)omp_get_num_threads > 1)
   	{
        printf("Total threads - %d\n", omp_get_num_threads());
        printf("Current thread id : %d\nHello world!\n", omp_get_thread_num());
   	}
}
