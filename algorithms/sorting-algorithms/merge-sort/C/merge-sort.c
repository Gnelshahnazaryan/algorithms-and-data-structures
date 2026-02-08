#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *, int, int);
void merge(int *, int, int, int);

int main()
{

    int arr[6] = {1, -5, 3, 10, 0, 18};
    merge_sort(arr, 0, 5);

    for (int i = 0; i < 6; ++i)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}

void merge_sort(int *arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    int size = right - left;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge(int *arr, int left, int mid, int right)
{
    int start1 = left;
    int start2 = mid + 1;
    int end1 = mid;
    int end2 = right;
    int k = 0;
    int *output = (int *)malloc((end2 - start1 + 1) * sizeof(int));

    while (start1 <= end1 && start2 <= end2)
    {
        if (arr[start1] <= arr[start2])
        {
            output[k++] = arr[start1++];
        }
        else
        {
            output[k++] = arr[start2++];
        }
    }

    while (start1 <= end1)
    {
        output[k++] = arr[start1++];
    }

    while (start2 <= end2)
    {
        output[k++] = arr[start2++];
    }

    k = 0;
    for (int i = left; i <= right; ++i)
    {
        arr[i] = output[k++];
    }

    free(output);
}