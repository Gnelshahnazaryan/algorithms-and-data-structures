#include "../include/dynamic-array.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* ================= Static Helpers ================= */

static int partition(DArray *arr, int low, int high, int (*cmp)(int a, int b))
{
    int pivot = arr->data[low];
    int i = 0;
    int j = arr->size - 1;

    while (i <= j)
    {
        while (cmp(pivot, arr->data[i]) >= 0)
        {
            ++i;
        }

        while (cmp(arr->data[j], pivot) > 0)
        {
            --j;
        }

        if (i < j)
        {
            da_swap(arr, i, j);
            ++i;
            --j;
        }
    }

    da_swap(arr, low, j);

    return j;
}

static void quickSort(DArray *arr, int low, int high, int (*cmp)(int a, int b))
{
    if (low >= high)
    {
        return;
    }

    int pi = partition(arr, low, high, cmp);

    quickSort(arr, low, pi - 1, cmp);
    quickSort(arr, pi + 1, high, cmp);
}

/* ================= Lifecycle ================= */

DA_Result da_init(DArray *arr, size_t capacity)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    arr->data = (int *)malloc(capacity * sizeof(int));

    if (arr->data == NULL)
    {
        return DA_ERR_NO_MEMORY;
    }

    arr->capacity = capacity;
    arr->size = 0;

    return DA_OK;
}

DA_Result da_destroy(DArray *arr)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    free(arr->data);
    arr->capacity = 0;
    arr->size = 0;

    return DA_OK;
}

/* ================= Capacity ================= */

DA_Result da_clear(DArray *arr)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    arr->size = 0;

    return DA_OK;
}

bool da_empty(const DArray *arr)
{
    return arr != NULL && arr->size == 0;
}

size_t da_capacity(const DArray *arr)
{
    if (arr == NULL)
    {
        return -1;
    }

    return arr->capacity;
}

DA_Result da_shrink_to_fit(DArray *arr)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (arr->capacity == arr->size)
    {
        return DA_OK;
    }

    int *tmp = (int *)realloc(arr->data, arr->size * sizeof(int));

    if (tmp == NULL)
    {
        return DA_ERR_NO_MEMORY;
    }

    arr->data = tmp;
    arr->capacity = arr->size;

    return DA_OK;
}

DA_Result da_reserve(DArray *arr, size_t new_capacity)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (new_capacity <= arr->capacity)
    {
        return DA_OK;
    }

    int *tmp = (int *)realloc(arr->data, new_capacity * sizeof(int));

    if (tmp == NULL)
    {
        return DA_ERR_NO_MEMORY;
    }

    arr->data = tmp;
    arr->capacity = new_capacity;

    return DA_OK;
}

/* ================= Modifiers ================= */

DA_Result da_erase(DArray *arr, size_t pos)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (pos >= arr->size)
    {
        return DA_ERR_OUT_OF_BOUNDS;
    }

    int tmp;

    if (pos == arr->size - 1)
    {
        da_pop_back(arr, &tmp);
    }

    for (size_t i = pos; i < arr->size - 1; ++i)
    {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;

    return DA_OK;
}

DA_Result da_resize(DArray *arr, size_t new_size)
{

    int limit = arr->capacity > new_size ? new_size : arr->capacity;

    int *tmp = (int *)malloc(new_size * sizeof(int));

    if (tmp == NULL)
    {
        return DA_ERR_NO_MEMORY;
    }

    for (int i = 0; i < limit; ++i)
    {
        tmp[i] = arr->data[i];
    }

    arr->data = tmp;
    arr->size = limit;
    arr->capacity = new_size;

    return DA_OK;
}

DA_Result da_pop_back(DArray *arr, int *out)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (da_empty(arr))
    {
        return DA_ERR_EMPTY;
    }

    *out = arr->data[--arr->size];
    return DA_OK;
}

DA_Result da_push_back(DArray *arr, int value)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (arr->data == NULL)
    {
        return DA_ERR_NO_MEMORY;
    }

    if (arr->size == arr->capacity)
    {
        size_t new_cap = arr->capacity == 0 ? 1 : arr->capacity * 2;
        DA_Result res = da_resize(arr, new_cap);
        if (res != DA_OK)
        {
            return res;
        }
    }

    arr->data[arr->size++] = value;

    return DA_OK;
}

DA_Result da_set(DArray *arr, size_t index, int value)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (index >= arr->size)
    {
        return DA_ERR_OUT_OF_BOUNDS;
    }

    arr->data[index] = value;

    return DA_OK;
}

DA_Result da_insert(DArray *arr, size_t pos, int value, int count)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (pos >= arr->size)
    {
        return DA_ERR_OUT_OF_BOUNDS;
    }

    if (pos == arr->size)
    {
        while (count > 0)
        {
            da_push_back(arr, value);
            --count;
        }
        return DA_OK;
    }

    if (arr->size + count > arr->capacity)
    {
        DA_Result res = da_resize(arr, arr->size + count);
        if (res != DA_OK)
        {
            return res;
        }
    }

    for (int i = arr->size - 1; i >= pos; --i)
    {
        arr->data[i + count] = arr->data[i];
    }

    for (int i = 0; i < count; ++i)
    {
        arr->data[pos + i] = value;
    }

    arr->size += count;
    return DA_OK;
}

DA_Result da_swap(DArray *arr, size_t i, size_t j)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (i >= arr->size || j > arr->size)
    {
        return DA_ERR_OUT_OF_BOUNDS;
    }

    int tmp = arr->data[i];
    arr->data[i] = arr->data[j];
    arr->data[j] = tmp;

    return DA_OK;
}

/* ================= Element Access ================= */

DA_Result da_at(const DArray *arr, size_t index, int *out)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    if (index >= arr->size)
    {
        return DA_ERR_OUT_OF_BOUNDS;
    }

    *out = arr->data[index];
    return DA_OK;
}

DA_Result da_back(const DArray *arr, int *out)
{
    if (arr == NULL || out == NULL)
    {
        return DA_ERR_NULL;
    }

    if (da_empty(arr))
    {
        return DA_ERR_OUT_OF_BOUNDS;
    }

    da_at(arr, arr->size - 1, out);
    return DA_OK;
}

DA_Result da_front(const DArray *arr, int *out)
{

    if (arr == NULL || out == NULL)
    {
        return DA_ERR_NULL;
    }

    if (da_empty(arr))
    {
        return DA_ERR_OUT_OF_BOUNDS;
    }

    da_at(arr, 0, out);

    return DA_OK;
}

int *da_to_array(const DArray *arr)
{
    if (arr == NULL || arr->data == NULL)
    {
        return NULL;
    }

    int *tmp = (int *)malloc(arr->size * sizeof(int));

    for (int i = 0; i < arr->size; ++i)
    {
        tmp[i] = arr->data[i];
    }

    return tmp;
}

/* ================= High-order / Algorithms ================= */

bool da_includes(const DArray *arr, int value)
{
    if (arr == NULL)
    {
        return false;
    }

    for (int i = 0; i < arr->size; ++i)
    {
        if (arr->data[i] == value)
        {
            return true;
        }
    }

    return false;
}

DArray *da_filter(const DArray *arr, bool (*predicate)(int value, int index, const DArray *arr, void *ctx), void *ctx)
{
    if (arr == NULL || predicate == NULL)
    {
        return NULL;
    }

    int k = 0;
    size_t new_size = 0;

    DArray *new_arr = (DArray *)malloc(sizeof(DArray));
    if (new_arr == NULL)
    {
        return NULL;
    }

    int *tmp = (int *)malloc(arr->size * sizeof(int));
    if (tmp == NULL)
    {
        free(new_arr);
        return NULL;
    }

    for (int i = 0; i < arr->size; ++i)
    {
        if (predicate(arr->data[i], i, arr, ctx))
        {
            tmp[k++] = arr->data[i];
            new_size++;
        }
    }

    new_arr->data = tmp;
    new_arr->size = new_size;
    new_arr->capacity = arr->size;

    da_shrink_to_fit(new_arr);

    return new_arr;
}

DArray *da_map(const DArray *arr, int (*map_fn)(int value, int index, const DArray *arr, void *ctx), void *ctx)
{
    if (arr == NULL || map_fn == NULL)
    {
        return NULL;
    }

    DArray *new_arr = (DArray *)malloc(sizeof(DArray));
    if (new_arr == NULL)
    {
        return NULL;
    }

    new_arr->data = (int *)malloc(arr->size * sizeof(int));
    if (new_arr->data == NULL)
    {
        free(new_arr);
        return NULL;
    }

    new_arr->size = arr->size;
    new_arr->capacity = arr->size;

    for (int i = 0; i < arr->size; ++i)
    {
        new_arr->data[i] = map_fn(arr->data[i], i, arr, ctx);
    }

    return new_arr;
}

int da_reduce(const DArray *arr, int (*reduce_fn)(int acc, int value, int index, const DArray *arr, void *ctx),
              int initial, void *ctx)
{
    if (arr == NULL || reduce_fn == NULL)
    {
        return INT_MIN;
    }

    int acc = initial;

    for (int i = 0; i < arr->size; ++i)
    {
        acc = reduce_fn(acc, arr->data[i], i, arr, ctx);
    }

    return acc;
}

/* ================= Utilities ================= */

void da_reverse(DArray *arr)
{
    if (arr == NULL)
    {
        return;
    }

    int i = 0;
    int j = arr->size - 1;

    while (i < j)
    {
        da_swap(arr, i++, j--);
    }
}

DA_Result da_clone(const DArray *arr, DArray *out)
{
    if (arr == NULL)
    {
        return DA_ERR_NULL;
    }

    DArray *clone = (DArray *)malloc(sizeof(DArray));
    if (clone == NULL)
    {
        return DA_ERR_NULL;
    }

    clone->data = (int *)malloc(arr->capacity * sizeof(int));
    if (clone->data == NULL)
    {
        return DA_ERR_NULL;
    }

    for (int i = 0; i < arr->size; ++i)
    {
        clone->data[i] = arr->data[i];
    }

    clone->size = arr->size;
    clone->capacity = arr->capacity;

    *out = *clone;

    return DA_OK;
}

DA_Result da_equals(const DArray *a, const DArray *b, bool *out)
{
    if (a == NULL || b == NULL)
    {
        return DA_ERR_NULL;
    }

    if (a->size != b->size)
    {
        *out = false;
    }

    for (int i = 0; i < a->size; ++i)
    {
        if (a->data[i] != b->data[i])
        {
            *out = false;
            return DA_OK;
        }
    }

    *out = true;
    return DA_OK;
}

DA_Result da_sort(DArray *arr, int (*cmp)(int a, int b))
{
    if (arr == NULL || cmp == NULL)
    {
        return DA_ERR_NULL;
    }

    if (arr->size <= 32)
    {
        for (int i = 1; i < arr->size; ++i)
        {
            int key = arr->data[i];
            int j = i - 1;

            while (j >= 0 && cmp(key, arr->data[j]) < 0)
            {
                arr->data[j + 1] = arr->data[j];
                --j;
            }

            arr->data[j + 1] = key;
        }
        return DA_OK;
    }

    quickSort(arr, 0, arr->size - 1, cmp);

    return DA_OK;
}