#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

/* ================= Error codes ================= */
typedef enum
{
    DA_OK = 0,
    DA_ERR_NULL,         // passed NULL pointer
    DA_ERR_EMPTY,        // empty array
    DA_ERR_NO_MEMORY,    // allocation failed
    DA_ERR_OUT_OF_BOUNDS // invalid index
} DA_Result;

/* ================= Dynamic Array Struct ================= */
typedef struct
{
    int *data;       // pointer to underlying array
    size_t size;     // number of valid elements
    size_t capacity; // allocated capacity
} DArray;

/* ================= Lifecycle ================= */
DA_Result da_destroy(DArray *arr);               // free array memory
DA_Result da_init(DArray *arr, size_t capacity); // initialize array

/* ================= Capacity ================= */
DA_Result da_clear(DArray *arr);                        // reset size to 0
bool da_empty(const DArray *arr);                       // check if empty
size_t da_capacity(const DArray *arr);                  // get allocated capacity
DA_Result da_shrink_to_fit(DArray *arr);                // reduce capacity to size
DA_Result da_reserve(DArray *arr, size_t new_capacity); // increase capacity

/* ================= Modifiers ================= */
DA_Result da_erase(DArray *arr, size_t pos);  // remove element at pos
DA_Result da_pop_back(DArray *arr, int *out); // remove last element
DA_Result da_push_back(DArray *arr, int value);
DA_Result da_resize(DArray *arr, size_t new_size);                  // change array size
DA_Result da_swap(DArray *arr, size_t i, size_t j);                 // swap elements
DA_Result da_set(DArray *arr, size_t index, int value);             // set element
DA_Result da_insert(DArray *arr, size_t pos, int value, int count); // insert elements

/* ================= Element Access ================= */
int *da_to_array(const DArray *arr);                        // return raw copy
DA_Result da_back(const DArray *arr, int *out);             // get last element
DA_Result da_front(const DArray *arr, int *out);            // get first element
DA_Result da_at(const DArray *arr, size_t index, int *out); // get element

/* ================= High-order / Algorithms ================= */
bool da_includes(const DArray *arr, int value);

DArray *da_filter(const DArray *arr,
                  bool (*predicate)(int value, int index, const DArray *arr, void *ctx),
                  void *ctx);

DArray *da_map(const DArray *arr,
               int (*map_fn)(int value, int index, const DArray *arr, void *ctx),
               void *ctx);

int da_reduce(const DArray *arr,
              int (*reduce_fn)(int acc, int value, int index, const DArray *arr, void *ctx),
              int initial,
              void *ctx);

/* ================= Utilities ================= */

void da_reverse(DArray *arr);
DA_Result da_clone(const DArray *arr, DArray *out);
DA_Result da_sort(DArray *arr, int (*cmp)(int a, int b));
DA_Result da_equals(const DArray *a, const DArray *b, bool *out);

#endif /* DYNAMIC_ARRAY_H */