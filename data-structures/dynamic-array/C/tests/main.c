#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dynamic-array.h"

/* ===== callbacks ===== */

bool is_even(int value, int index, const DArray *arr, void *ctx)
{
    (void)index;
    (void)arr;
    (void)ctx;
    return value % 2 == 0;
}

int square(int value, int index, const DArray *arr, void *ctx)
{
    (void)index;
    (void)arr;
    (void)ctx;
    return value * value;
}

int sum_reduce(int acc, int value, int index, const DArray *arr, void *ctx)
{
    (void)index;
    (void)arr;
    (void)ctx;
    return acc + value;
}

int cmp_int(int a, int b)
{
    return a - b;
}

/* ===== main ===== */

int main(void)
{
    DArray arr;

    /* lifecycle */
    assert(da_init(&arr, 4) == DA_OK);
    assert(da_empty(&arr) == true);

    /* push_back */
    da_push_back(&arr, 1);
    da_push_back(&arr, 2);
    da_push_back(&arr, 3);
    da_push_back(&arr, 4);
    da_push_back(&arr, 5);

    assert(arr.size == 5);
    assert(da_empty(&arr) == false);

    /* element access */
    int x;
    da_front(&arr, &x);
    assert(x == 1);

    da_back(&arr, &x);
    assert(x == 5);

    da_at(&arr, 2, &x);
    assert(x == 3);

    /* set */
    da_set(&arr, 2, 10);
    da_at(&arr, 2, &x);
    assert(x == 10);

    /* swap */
    da_swap(&arr, 0, 4);
    da_front(&arr, &x);
    assert(x == 5);

    /* includes */
    assert(da_includes(&arr, 10) == true);
    assert(da_includes(&arr, 99) == false);

    /* filter */
    DArray *evens = da_filter(&arr, is_even, NULL);
    assert(evens != NULL);
    assert(evens->size == 3);

    /* map */
    DArray *squares = da_map(&arr, square, NULL);
    assert(squares != NULL);
    da_at(squares, 0, &x);
    assert(x == 25);

    /* reduce */
    int sum = da_reduce(&arr, sum_reduce, 0, NULL);
    assert(sum == 5 + 2 + 10 + 4 + 1);

    /* sort */
    da_sort(&arr, cmp_int);
    da_front(&arr, &x);
    assert(x == 1);

    /* reverse */
    da_reverse(&arr);
    da_front(&arr, &x);
    assert(x == 10 || x == 5);

    /* clone */
    DArray clone;
    bool flag;
    da_clone(&arr, &clone);
    da_equals(&arr, &clone, &flag);
    assert(flag == true);

    /* erase */
    da_erase(&arr, 0);
    assert(arr.size == 4);

    /* pop_back */
    da_pop_back(&arr, &x);
    assert(arr.size == 3);

    /* to_array */
    int *raw = da_to_array(&arr);
    assert(raw != NULL);
    free(raw);

    /* capacity ops */
    da_reserve(&arr, 100);
    assert(da_capacity(&arr) >= 100);

    da_shrink_to_fit(&arr);
    assert(arr.capacity == arr.size);

    /* cleanup */
    da_destroy(evens);
    da_destroy(squares);
    da_destroy(&clone);
    da_destroy(&arr);

    printf("All tests passed successfully \n");
    return 0;
}
