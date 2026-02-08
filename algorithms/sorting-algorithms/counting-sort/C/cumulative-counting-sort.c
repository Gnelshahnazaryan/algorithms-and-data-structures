#include <stdio.h>
#include <stdlib.h>

int findMax(int *arr, int size);
int findMin(int *arr, int size);
int *countingSort(int *arr, int size);

int main()
{

    int arr[8] = {6, 1, 3, 3, 4, 1, 2, 1};

    int *sorted = countingSort(arr, 8);

    for (int i = 0; i < 8; ++i)
    {
        printf("%d ", sorted[i]);
    }

    free(sorted);

    return 0;
}

int findMax(int *arr, int size)
{
    int max = arr[0];

    for (int i = 1; i < size; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

int findMin(int *arr, int size)
{
    int min = arr[0];

    for (int i = 1; i < size; ++i)
    {
        if (min > arr[i])
        {
            min = arr[i];
        }
    }

    return min;
}

int *countingSort(int *arr, int size)
{
    int max = findMax(arr, size);
    int min = findMin(arr, size);

    int *count = (int *)calloc(max + 1, sizeof(int));
    int *sorted = (int *)calloc(size, sizeof(int));

    for (int i = 0; i < size; ++i)
    {
        count[arr[i] - min]++;
    }

    for (int i = 1; i < size; ++i)
    {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; --i)
    {
        int val = arr[i];
        int index = val - min;
        int pos = count[index] - min;
        sorted[pos] = val;
        count[index]--;
    }

    free(count);
    return sorted;
}