#include <iostream>

void printArray(int *array, int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << array[i] << std::endl;
}

void quickSort(int *array, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}

int main(int argc, char **argv)
{
    int *array;

    array = (int *)malloc(sizeof(int) * atoi(argv[3]));
    for (int i = 0; i < atoi(argv[3]); i++)
        array[i] = rand() % 100;
    FILE *file = NULL;
    file = fopen(argv[1], "w");
    fprintf(file, "%d\n", atoi(argv[3]));
    for (int i = 0; i < atoi(argv[3]); i++)
        fprintf(file, "%d\n", array[i]);
    fclose(file);
    
    int n = sizeof(array) / sizeof(array[0]);

    std::cout << "Before Quick Sort :" << std::endl;
    printArray(array, n);

    quickSort(array, 0, n);

    std::cout << "After Quick Sort :" << std::endl;
    printArray(array, n);
    return (0);
}