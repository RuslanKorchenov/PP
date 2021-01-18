// 1. Написать программу где каждый поток печатает свой идентификатор, количество потоков всего и строчку «Hello World». Запустить программу с 8 потоками. Всегда ли вывод идентичен? Почему?


#include <stdio.h>
#include "omp.h"
int main()
{
   	omp_set_num_threads(8);
#pragma omp parallel
   	{
        printf("Total threads - %d\n", omp_get_num_threads());
        printf("Current thread id : %d\nHello world!\n", omp_get_thread_num());
   	}
}
// Вывод программы не всегда будет идентичным, потому что при каждом новом запуске программы потоки будут вызываться в случайном порядке.
