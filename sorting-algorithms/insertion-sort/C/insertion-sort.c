#include <stdio.h>

void insertionSort(int[], int);

int main()
{

    int arr[4] = {8, 6, 3, 2};

    insertionSort(arr, 4);

    for (int i = 0; i < 4; ++i)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}

void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}