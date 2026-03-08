#include <stdio.h>

int linear_search_itr(int*, int, int);
int linear_search_rec(int*, int, int, int);

int main() {}

int linear_search_itr(int* arr, int size, int target)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}

int linear_search_rec(int* arr, int target, int index, int size)
{
    if (index >= size)
    {
        return -1;
    }

    if (arr[index] == target)
    {
        return index;
    }

    return linear_search_rec(arr, target, index + 1, size);
}