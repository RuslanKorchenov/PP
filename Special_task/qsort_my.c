/*
   qsort.c - Parallel sorting algorithm based on quicksort

   compile: mpicc -Wall -o qsort qsort.c
   run:     mpirun -np num_procs qsort in_file out_file
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

double startTime;

void swap(int *array, int i, int j)
{
    int t = array[i];
    array[i] = array[j];
    array[j] = t;
}

void quicksort(int *array, int start, int n)
{
    int x, p, i;
    if (n <= 1)
        return;
    x = array[start + n / 2];
    swap(array, start, start + n / 2);
    p = start;
    for (i = start + 1; i < start + n; i++)
        if (array[i] < x)
        {
            p++;
            swap(array, i, p);
        }
    swap(array, start, p);
    quicksort(array, start, p - start);
    quicksort(array, p + 1, start + n - p - 1);
}

int *merge(int *left, int left_len, int *right, int right_len)
{
    int *result = (int *)malloc((left_len + right_len) * sizeof(int));
    int i = 0;
    int j = 0;
    int k;
    for (k = 0; k < left_len + right_len; k++)
    {
        if (i >= left_len)
        {
            result[k] = right[j];
            j++;
        }
        else if (j >= right_len)
        {
            result[k] = left[i];
            i++;
        }
        else if (left[i] < right[j])
        {
            result[k] = left[i];
            i++;
        }
        else
        {
            result[k] = right[j];
            j++;
        }
    }
    return result;
}

void create_array(char *file1, long size)
{
    int *array;

    array = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        array[i] = rand() % 100;
    FILE *file = NULL;
    file = fopen(file1, "w");
    fprintf(file, "%ld\n", size);
    for (int i = 0; i < size; i++)
        fprintf(file, "%d\n", array[i]);
    fclose(file);
}

int main(int argc, char **argv)
{
    int *array = NULL, *chunk, *temp;
    int chunk_size, s, length, temp_len, step;
    int size, rank;
    double time;
    FILE *file = NULL;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        create_array(argv[1], atoi(argv[3]));
        file = fopen(argv[1], "r");
        fscanf(file, "%d", &length);
        chunk_size = (length % size != 0) ? length / size + 1 : length / size;
        array = (int *)malloc(size * chunk_size * sizeof(int));
        for (int i = 0; i < length; i++)
            fscanf(file, "%d", &(array[i]));
        fclose(file);
        for (int i = length; i < size * chunk_size; i++)
            array[i] = 0;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    time = -MPI_Wtime();

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    chunk_size = (length % size != 0) ? length / size + 1 : length / size;

    chunk = (int *)malloc(chunk_size * sizeof(int));
    MPI_Scatter(array, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    free(array);
    array = NULL;

    s = (length >= chunk_size * (rank + 1)) ? chunk_size : length - chunk_size * rank;
    quicksort(chunk, 0, s);

    for (step = 1; step < size; step = 2 * step)
    {
        if (rank % (2 * step) != 0)
        {
            MPI_Send(chunk, s, MPI_INT, rank - step, 0, MPI_COMM_WORLD);
            break;
        }
        if (rank + step < size)
        {
            temp_len = (length >= chunk_size * (rank + 2 * step)) ? chunk_size * step : length - chunk_size * (rank + step);
            temp = (int *)malloc(temp_len * sizeof(int));
            MPI_Recv(temp, temp_len, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status);
            array = merge(chunk, s, temp, temp_len);
            free(chunk);
            free(temp);
            chunk = array;
            s = s + temp_len;
        }
    }
    time += MPI_Wtime();

    if (rank == 0)
    {
        file = fopen(argv[2], "w");
        fprintf(file, "%d\n", s);
        for (int i = 0; i < s; i++)
            fprintf(file, "%d\n", chunk[i]);
        fclose(file);
        printf("Quicksort %d ints on %d procs: %f secs\n", length, size, time);
    }

    MPI_Finalize();
    return 0;
}



// int main(int argc, char **argv)
// {
//     int n;
//     int *array = NULL;
//     int chunk_size, s;
//     int *chunk;
//     int o;
//     int *temp;
//     int step;
//     int size, rank;
//     MPI_Status status;
//     double time;
//     FILE *file = NULL;
//     int i;

//     if (argc != 4)
//     {
//         fprintf(stderr, "Usage: mpirun -np <num_procs> %s <in_file> <out_file>\n", argv[0]);
//         exit(1);
//     }

//     MPI_Init(&argc, &argv);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//     if (rank == 0)
//     {
//         create_array(argv[1], atoi(argv[3]));
//         file = fopen(argv[1], "r");
//         fscanf(file, "%d", &n);
//         chunk_size = (n % size != 0) ? n / size + 1 : n / size;
//         array = (int *)malloc(size * chunk_size * sizeof(int));
//         for (i = 0; i < n; i++)
//             fscanf(file, "%d", &(array[i]));
//         fclose(file);c
//     }

//     MPI_Barrier(MPI_COMM_WORLD);
//     time = -MPI_Wtime();
//     MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
//     chunk_size = (n % size != 0) ? n / size + 1 : n / size;
//     chunk = (int *)malloc(chunk_size * sizeof(int));
//     MPI_Scatter(array, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
//     free(array);
//     array = NULL;
//     s = (n >= chunk_size * (rank + 1)) ? chunk_size : n - chunk_size * rank;
//     quicksort(chunk, 0, s);
//     for (step = 1; step < size; step = 2 * step)
//     {
//         if (rank % (2 * step) != 0)
//         {
//             MPI_Send(chunk, s, MPI_INT, rank - step, 0, MPI_COMM_WORLD);
//             break;
//         }
//         if (rank + step < size)
//         {
//             o = (n >= chunk_size * (rank + 2 * step)) ? chunk_size * step : n - chunk_size * (rank + step);
//             temp = (int *)malloc(o * sizeof(int));
//             MPI_Recv(temp, o, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status);
//             array = merge(chunk, s, temp, o);
//             free(chunk);
//             free(temp);
//             chunk = array;
//             s = s + o;
//         }
//     }

//     time += MPI_Wtime();

//     if (rank == 0)
//     {
//         file = fopen(argv[2], "w");
//         fprintf(file, "%d\n", s);
//         for (i = 0; i < s; i++)
//             fprintf(file, "%d\n", temp[i]);
//         fclose(file);
//         printf("Quicksort %d ints on %d procs: %f secs\n", n, size, time);
//     }

//     MPI_Finalize();
//     return 0;
// }