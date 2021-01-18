#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int d[6][8];
    
    int sum = 0;
    int cnt_3 = 0;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++)
            d[i][j] = rand() % 100;
    
    int min = d[0][0];
    int max = d[0][0];
#pragma omp parallel sections num_threads(3)
{
    #pragma omp section
    {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 8; j++)
                sum += d[i][j];
        printf("Thread num: %d\n", omp_get_thread_num());
        printf("Avg: %f\n", (double)(sum / (6 * 8)));
    }
    #pragma omp section
    {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 8; j++)
            {
                if (d[i][j] > max)
                    max = d[i][j];
                if (d[i][j] < min)
                    min = d[i][j];
            }
        printf("Thread num: %d\n", omp_get_thread_num());
        printf("Max: %d\nMin:%d\n", max, min);
    }
    #pragma omp section
    {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 8; j++)
                if (d[i][j] % 3 == 0)
                    cnt_3++;
        printf("Thread num: %d\n", omp_get_thread_num());
        printf("Cnt_3: %d\n", cnt_3);
    }
}
}