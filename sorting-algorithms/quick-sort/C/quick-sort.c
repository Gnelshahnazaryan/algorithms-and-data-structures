#include <stdio.h>

void swap(int *, int *);
int partition(int *, int, int);
void quickSort(int *, int, int);

int main()
{

    int arr[5] = {5, 4, 3, 2, 1};
    quickSort(arr, 0, 4);

    for (int i = 0; i < 5; ++i)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *arr, int low, int high)
{
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i <= j)
    {
        while (arr[i] <= pivot)
            ++i;
        while (arr[j] > pivot)
            --j;

        if (i < j)
        {
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[low], &arr[j]);

    return j;
}

void quickSort(int *arr, int low, int high)
{
    if (low >= high)
        return;

    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}