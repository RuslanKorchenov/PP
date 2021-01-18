#include <stdio.h>
#include <math.h>
#include <omp.h>
 
 
int main() {
   	const int n = 1000;
   	int a[n][n];
   	int b[n];
   	int c[n];
   	for (int i = 0; i < n; i++) {
         	b[i] = i;
         	for (int j = 0; j < n; j++) {
                	a[i][j] = rand() % 100;
         	}
   	}
   	double start = omp_get_wtime();
   	for (int i = 0; i < n; i++) {
         	c[i] = 0;
         	for (int j = 0; j < n; j++) {
                	c[i] += a[i][j] * b[j];
         	}
   	}
   	double time = omp_get_wtime() - start;
    printf("W/o parallel : %f\n", time);

   	start = omp_get_wtime();
#pragma omp parallel for schedule(static) num_threads(4)
   	for (int i = 0; i < n; i++) {
         	c[i] = 0;
         	for (int j = 0; j < n; j++) {
                	c[i] += a[i][j] * b[j];
         	}
   	}
   	time = omp_get_wtime() - start;
    printf("With parallel : %f\n", time);
}
