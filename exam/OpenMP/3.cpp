#include <iostream>
#include <omp.h>
#include <stdio.h>
 
 
int main()
{
   	int a = 0;
   	int b = 0;
   	printf("Before first block: a = %d b = %d\n", a, b);
#pragma omp parallel num_threads(2) private(a) firstprivate(b)
   	{
            printf("Current thread id: %d\n", omp_get_thread_num());
         	a = 0; // потому что значение в переменной private не определенно
         	a += omp_get_thread_num();
         	b += omp_get_thread_num();
   	        printf("In first block: a = %d b = %d\n", a, b);
   	}
   	printf("After first block / before second block: a = %d b = %d\n", a, b);
#pragma omp parallel num_threads(4) shared(a) private(b)
   	{
            printf("Current thread id: %d\n", omp_get_thread_num());
         	b = 0;
         	a -= omp_get_thread_num();
         	b -= omp_get_thread_num();
   	        printf("In second block: a = %d b = %d\n", a, b);
   	}
   	printf("After second block a = %d b = %d\n", a, b);
}
