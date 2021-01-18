#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
 
 
int main() {
   	int sumA = 0;
   	int sumB = 0;
   	const int n = 10;
   	int a[n] = { 456, 134, 648, 652, 243, 234, 986, 333, 235, 777 };
   	int b[n] = { 3456, 1234, 122, 6565, 7565, 344, 4535, 9874, 2345, 555 };
#pragma omp parallel for reduction(+: sumA)
   	for (int i = 0; i <  n; i++) {
         	sumA += a[i];
   	}
#pragma omp parallel for reduction(+: sumB)
   	for (int i = 0; i < 10; i++) {
         	sumB += b[i];
   	}
   	if (sumA / n > sumB / n) {
         	printf("Average of a (%d) is bigger than average of b (%d)\n", sumA / n, sumB / n);
   	}
   	else if (sumA / n < sumB / n) {
         	printf("Average of a (%d) is less than average of b (%d)\n", sumA / n, sumB / n);
   	}
   	else {
         	printf("Average of a (%d) is equal than average of b (%d)\n", sumA / n, sumB / n);
   	}
}
