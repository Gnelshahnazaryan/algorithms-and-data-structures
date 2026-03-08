#include <stdio.h>

int binary_search_itr(int*, int, int);
int binary_search_rec(int*, int, size_t, size_t);

int main()
{
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int size = sizeof(arr) / sizeof(arr[0]);

    int targets[] = {23, 2, 91, 50};
    int tsize = sizeof(targets) / sizeof(targets[0]);

    printf("=== Binary Search Tests ===\n\n");

    for (int i = 0; i < tsize; i++)
    {
        int target = targets[i];

        int itr_result = binary_search_itr(arr, size, target);
        int rec_result = binary_search_rec(arr, target, 0, size - 1);

        printf("Target: %d\n", target);
        printf("Iterative Result: %d\n", itr_result);
        printf("Recursive Result: %d\n\n", rec_result);
    }

    return 0;
}

int binary_search_itr(int* arr, int size, int target)
{
    size_t left = 0;
    size_t right = size - 1;

    while (left <= right)
    {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

int binary_search_rec(int* arr, int target, size_t left, size_t right)
{
    if (left > right)
    {
        return -1;
    }
    size_t mid = left + (right - left) / 2;

    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] < target)
    {
        return binary_search_rec(arr, target, mid + 1, right);
    }
    
    return binary_search_rec(arr, target, left, mid - 1);
}