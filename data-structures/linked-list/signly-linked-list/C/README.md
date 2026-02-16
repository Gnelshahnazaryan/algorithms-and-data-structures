# Singly Linked List in C

A clean and safe implementation of a **Singly Linked List** in pure C, designed as an educational and reusable data structure library.

---

## Features

- Dynamic memory management
- Push / Pop operations (front & back)
- Insert and erase by index
- Remove elements by value (with optional comparator)
- Reverse list in-place
- Merge two sorted lists
- Merge Sort (`O(n log n)`) optimized for linked lists
- Accurate size tracking
- Explicit error handling via result codes

---

## Table of Contents

1. [Lifecycle](#lifecycle)
2. [Capacity](#size)
3. [Modifiers](#modifiers)
4. [Element Access](#element-access)
5. [Algorithms](#Algorithms)
6. [Utilities](#utilities)
7. [Time & Space Complexity](#time--space-complexity)
8. [Quick Start Example](#quick-start-example)

## Lifecycle

| Function     | Description           |
| ------------ | --------------------- |
| `sl_init`    | Initialize empty list |
| `sl_destroy` | Free all nodes        |

---

## Size

| Function      | Description            |
| ------------- | ---------------------- |
| `sl_size`     | Get number of elements |
| `sl_is_empty` | Check if list is empty |
| `sl_clear`    | Remove all elements    |

---

## Element Access

| Function   | Description          |
| ---------- | -------------------- |
| `sl_front` | Get first element    |
| `sl_at`    | Get element by index |

---

## Modifiers

| Function        | Description                |
| --------------- | -------------------------- |
| `sl_push_front` | Insert at beginning        |
| `sl_push_back`  | Insert at end              |
| `sl_insert`     | Insert value(s) at index   |
| `sl_pop_front`  | Remove first element       |
| `sl_pop_back`   | Remove last element        |
| `sl_erase`      | Remove element by index    |
| `sl_remove`     | Remove all matching values |
| `sl_reverse`    | Reverse list               |

---

## Algorithms

| Function   | Description                |
| ---------- | -------------------------- |
| `sl_sort`  | Sort list using Merge Sort |
| `sl_merge` | Merge two sorted lists     |

---

## Time & Space Complexity

| Operation  | Complexity |
| ---------- | ---------- |
| Push Front | O(1)       |
| Push Back  | O(n)       |
| Pop Front  | O(1)       |
| Pop Back   | O(n)       |
| Insert     | O(n)       |
| Erase      | O(n)       |
| Remove     | O(n)       |
| Reverse    | O(n)       |
| Sort       | O(n log n) |

---

## Quick Start Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "../include/singly-linked-list.h"

SinglyLinkedList list;
sl_init(&list);

sl_push_back(&list, 3);
sl_push_back(&list, 1);
sl_push_back(&list, 2);

sl_sort(&list, cmp_asc);
// Result: 1 -> 2 -> 3
```
