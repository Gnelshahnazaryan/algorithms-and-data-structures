# Circular Deque (C Implementation)

## Description

**Circular Deque** is a dynamic double-ended queue implemented in C using a **circular buffer** technique.

It allows efficient insertion and removal of elements from **both the front and back** in constant time **O(1)**.

This implementation includes:

- Safe error handling via result codes
- Rotation operations
- Functional-style utilities (`map`, `reduce`)
- Memory management utilities
- Search & comparison operations
- Deep copy support

---

## What Is a Deque?

A **Deque (Double-Ended Queue)** is a linear data structure that allows:

- `push_front`
- `push_back`
- `pop_front`
- `pop_back`

Unlike a stack or queue, a deque supports operations on **both ends**.

This implementation uses a **circular array**, meaning:

- No shifting of elements
- Constant-time insertions/removals
- Efficient memory usage

---

# Error Codes Meaning

| Code                  | Meaning                  |
| --------------------- | ------------------------ |
| `DEQUE_OK`            | Operation successful     |
| `DEQUE_ERR_NULL`      | Null pointer passed      |
| `DEQUE_ERR_EMPTY`     | Operation on empty deque |
| `DEQUE_ERR_ALLOC`     | Memory allocation failed |
| `DEQUE_ERR_NOT_FOUND` | Element not found        |

# Function Overview

| Category             | Function              | Description                    | Complexity |
| -------------------- | --------------------- | ------------------------------ | ---------- |
| **Lifecycle**        | `deque_init`          | Initialize deque with capacity | O(n)       |
|                      | `deque_destroy`       | Free allocated memory          | O(1)       |
| **Capacity / State** | `deque_size`          | Get current size               | O(1)       |
|                      | `deque_capacity`      | Get allocated capacity         | O(1)       |
|                      | `deque_is_empty`      | Check if empty                 | O(1)       |
|                      | `deque_is_full`       | Check if full                  | O(1)       |
| **Push**             | `deque_push_back`     | Insert at back                 | O(1)       |
|                      | `deque_push_front`    | Insert at front                | O(1)       |
| **Pop**              | `deque_pop_back`      | Remove from back               | O(1)       |
|                      | `deque_pop_front`     | Remove from front              | O(1)       |
| **Access**           | `deque_front`         | Get first element              | O(1)       |
|                      | `deque_back`          | Get last element               | O(1)       |
|                      | `deque_at`            | Get element at index           | O(1)       |
| **Modify**           | `deque_swap`          | Swap two elements              | O(1)       |
|                      | `deque_rotate_left`   | Rotate left by k               | O(k)       |
|                      | `deque_rotate_right`  | Rotate right by k              | O(k)       |
| **Search**           | `deque_find`          | Find element index             | O(n)       |
|                      | `deque_includes`      | Check if value exists          | O(n)       |
|                      | `deque_equals`        | Compare two deques             | O(n)       |
| **Functional**       | `deque_map`           | Transform elements             | O(n)       |
|                      | `deque_reduce`        | Reduce to single value         | O(n)       |
| **Memory**           | `deque_reserve`       | Increase capacity              | O(n)       |
|                      | `deque_shrink_to_fit` | Reduce capacity to size        | O(n)       |
|                      | `deque_clear`         | Remove all elements            | O(1)       |
| **Copy**             | `deque_clone`         | Deep copy deque                | O(n)       |

### Notes

- `n` = number of elements
- `k` = number of rotation steps
- `O(1)*` = Best case when element is found at first position
- `O(1)**` = If rotation implemented by adjusting `front` index only

---

# Overview

The **Circular Deque** is a double-ended queue implementation in C based on a **circular buffer** design.

It provides efficient insertion and removal of elements from both the front and the back in constant time **O(1)**, without shifting elements in memory.

Unlike a simple array-based queue, this implementation uses modular arithmetic to wrap indices around the buffer, allowing full utilization of allocated memory.

---

## Key Characteristics

- Circular indexing (no element shifting)
- Constant-time push and pop operations
- Safe error handling via result codes
- Supports rotation and swapping
- Includes search and comparison utilities
- Functional-style operations (`map`, `reduce`)
- Manual memory management
- Deep copy support