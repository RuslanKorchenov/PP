#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(2);
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int min = a[0];
    int max = b[0];

#pragma omp parallel num_threads(2)
{
    if (omp_get_thread_num() == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (a[i] < min)
                min = a[i];
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (b[i] > max)
                max = b[i];
        }
    }
}
    printf("Min = %d\nMax = %d\n", min, max);
}