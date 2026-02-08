# Dynamic Array (C)

**Dynamic Array** is a flexible, resizable array in C, inspired by `std::vector` and JS arrays.  
Supports dynamic resizing, safe element access, and high-order functions like `map`, `filter`, `reduce`.

---

## Summary

- **Resizable:** Grows automatically when full, can shrink to fit.
- **Safe Access:** All element access checks for invalid pointers and out-of-bounds indices.
- **High-order Functions:** `map`, `filter`, `reduce` with optional context (`void* ctx`).
- **Memory Management:** Functions returning new arrays require the caller to free memory.
- **Error Handling:** All functions return consistent `DA_Result` codes.

---

## Table of Contents

1. [Lifecycle](#lifecycle)
2. [Capacity](#capacity)
3. [Modifiers](#modifiers)
4. [Element Access](#element-access)
5. [High-Order / Algorithms](#high-order--algorithms)
6. [Utilities](#utilities)
7. [Time & Space Complexity](#time--space-complexity)
8. [Quick Start Example](#quick-start-example)

---

## Lifecycle

| Function                 |   Return    | Notes                       |
| :----------------------- | :---------: | :-------------------------- |
| `da_init(arr, capacity)` | `DA_Result` | Initialize array            |
| `da_destroy(arr)`        | `DA_Result` | Free memory and reset array |

---

## Capacity

| Function                        |   Return    | Notes                           |
| :------------------------------ | :---------: | :------------------------------ |
| `da_empty(arr)`                 |   `bool`    | True if empty                   |
| `da_capacity(arr)`              |  `size_t`   | Allocated capacity              |
| `da_clear(arr)`                 | `DA_Result` | Reset size to 0                 |
| `da_reserve(arr, new_capacity)` | `DA_Result` | Ensure minimum capacity         |
| `da_shrink_to_fit(arr)`         | `DA_Result` | Reduce capacity to current size |

---

## Modifiers

| Function                            |   Return    | Notes                       |
| :---------------------------------- | :---------: | :-------------------------- |
| `da_push_back(arr, value)`          | `DA_Result` | Append element              |
| `da_pop_back(arr, *out)`            | `DA_Result` | Remove last element         |
| `da_insert(arr, pos, value, count)` | `DA_Result` | Insert elements at position |
| `da_erase(arr, pos)`                | `DA_Result` | Remove element at index     |
| `da_resize(arr, new_size)`          | `DA_Result` | Resize array                |
| `da_set(arr, index, value)`         | `DA_Result` | Set element at index        |
| `da_swap(arr, i, j)`                | `DA_Result` | Swap two elements           |

---

## Element Access

| Function                  |   Return    | Notes                                |
| :------------------------ | :---------: | :----------------------------------- |
| `da_at(arr, index, *out)` | `DA_Result` | Get element at index                 |
| `da_front(arr, *out)`     | `DA_Result` | First element                        |
| `da_back(arr, *out)`      | `DA_Result` | Last element                         |
| `da_to_array(arr)`        |   `int*`    | Returns copy of array (caller frees) |

---

## High-Order / Algorithms

| Function                        |  Return   | Notes                 |
| :------------------------------ | :-------: | :-------------------- |
| `da_includes(arr, value)`       |  `bool`   | Check if value exists |
| `da_filter(arr, pred, ctx)`     | `DArray*` | Filter elements       |
| `da_map(arr, fn, ctx)`          | `DArray*` | Map elements          |
| `da_reduce(arr, fn, init, ctx)` |   `int`   | Reduce values         |

---

## Utilities

| Function                |   Return    | Notes                   |
| :---------------------- | :---------: | :---------------------- |
| `da_reverse(arr)`       |   `void`    | Reverse array           |
| `da_clone(arr, out)`    | `DA_Result` | Deep copy, caller frees |
| `da_equals(a, b, *out)` | `DA_Result` | Compare arrays          |
| `da_sort(arr, cmp)`     | `DA_Result` | Sort array              |

---

## Time & Space Complexity

| Operation                      |      Time      | Space            | Notes                      |
| :----------------------------- | :------------: | :--------------- | :------------------------- |
| Push back                      | O(1) amortized | O(n) if resizing | Doubles capacity when full |
| Pop back                       |      O(1)      | O(1)             |                            |
| Insert                         |      O(n)      | O(n) if resizing | Shifts elements right      |
| Erase                          |      O(n)      | O(1)             | Shifts elements left       |
| Access (`at`, `front`, `back`) |      O(1)      | O(1)             |                            |
| Map / Filter                   |      O(n)      | O(n)             | Allocates new array        |
| Reduce                         |      O(n)      | O(1)             | Accumulates value          |
| Sort                           |   O(n log n)   | O(log n)         | QuickSort + insertion sort |

---

## Quick Start Example

```c
#include "dynamic-array.h"
#include <stdio.h>

bool is_even(int val, int idx, const DArray *arr, void *ctx) {
    return val % 2 == 0;
}

int main() {
    DArray arr;
    da_init(&arr, 5);

    for(int i=1;i<=5;i++) da_push_back(&arr, i);

    DArray *evens = da_filter(&arr, is_even, NULL);

    for(size_t i=0;i<evens->size;i++)
        printf("%d ", evens->data[i]); // prints 2 4

    da_destroy(&arr);
    da_destroy(evens);
    return 0;
}
```
