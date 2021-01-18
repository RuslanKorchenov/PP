#include <stdio.h>
#include <math.h>
#include <omp.h>
 
 
int main() {
   	int a[12];
   	int b[12];
   	int c[12];
   	omp_set_num_threads(3);
#pragma omp parallel shared(a,b)
   	{
#pragma omp parallel for schedule(static, 3)
         	for (int i = 0; i < 12; i++) {
                	a[i] = rand() % 100;
         	}
#pragma omp parallel for schedule(static, 3)
         	for (int i = 0; i < 12; i++) {
                	b[i] = rand() % 100;
         	}
        for (int i = 0; i < 12; i++) {
                printf("%d ", a[i]);
        }
        for (int i = 0; i < 12; i++) {
            	printf("%d ", b[i]);
     	}  	

   	}
   	omp_set_num_threads(4);
#pragma omp parallel shared(c) firstprivate(a,b)
   	{
#pragma omp parallel for schedule(dynamic, 3)
         	for (int i = 0; i < 12; i++) {
                	c[i] = a[i] + b[i];
         	}
         	for (int i = 0; i < 12; i++) {
                	printf("%d ", c[i]);
         	}
        printf("Threads: %d current tread: %d\n", omp_get_num_threads(), omp_get_thread_num());

   	}
}
