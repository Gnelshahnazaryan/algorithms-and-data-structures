#include <stdio.h>
#include <stdlib.h>

int findMax(int *arr, int size);
int findMin(int *arr, int size);
int *countingSort(int *arr, int size);

int main()
{
    int arr[5] = {5, 4, 3, 2, 1};

    int *arr1 = countingSort(arr, 5);

    for (int i = 0; i < 5; ++i)
    {
        printf("%d ", arr1[i]);
    }

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
    if (size <= 1)
        return arr;

    int max = findMax(arr, size);
    int min = findMin(arr, size);

    int *count = (int *)calloc(max - min + 1, sizeof(int));
    int *sorted = (int *)calloc(size, sizeof(int));

    for (int i = 0; i < size; ++i)
    {
        count[arr[i] - min]++;
    }

    int k = 0;
    for (int i = 0; i < max - min + 1; ++i)
    {
        while (count[i]--)
        {
            sorted[k++] = i + min;
        }
    }

    return sorted;
}