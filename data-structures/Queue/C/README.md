# Circular Queue Implementation in C

## Overview

This repository contains a **C implementation of a circular queue** using arrays.
A **Queue** is a linear data structure that follows the **FIFO (First In, First Out)** principle.

- Elements are added at the **rear** and removed from the **front**.
- This implementation uses a **circular array** to efficiently utilize all allocated memory.
- It supports constant-time operations for **enqueue**, **dequeue**, and **peek**.
- Proper **error handling** is included to detect **overflow** and **underflow**.

**Use Cases:**

- Task scheduling in operating systems
- BFS (Breadth-First Search) in graphs
- Printer job queues
- Buffer management in data streaming systems

---

## Features

- Circular array implementation
- Constant-time operations (O(1)) for enqueue, dequeue, and peek
- Overflow and underflow detection using **error codes**
- Easy-to-use API: `queue.h` and `queue.c`

---

## Queue Operations

| Operation        | Description                              | Time Complexity |
| ---------------- | ---------------------------------------- | --------------- |
| `queue_init`     | Initialize a queue with a given capacity | O(1)            |
| `queue_destroy`  | Free allocated memory                    | O(1)            |
| `queue_enqueue`  | Add element at rear                      | O(1)            |
| `queue_dequeue`  | Remove element from front                | O(1)            |
| `queue_peek`     | Return front element without removing    | O(1)            |
| `queue_is_empty` | Check if queue is empty                  | O(1)            |
| `queue_is_full`  | Check if queue is full                   | O(1)            |

## Error Codes

| Code                       | Meaning                  |
| -------------------------- | ------------------------ |
| `QUEUE_OK`                 | Operation successful     |
| `QUEUE_ERROR_ALLOCATION`   | Memory allocation failed |
| `QUEUE_ERROR_OVERFLOW`     | Queue is full            |
| `QUEUE_ERROR_UNDERFLOW`    | Queue is empty           |
| `QUEUE_ERROR_NULL_POINTER` | NULL pointer passed      |

---

## Example Usage

```c
#include "queue.h"
#include <stdio.h>

int main() {
    Queue q;
    queue_init(&q, 5);

    queue_enqueue(&q, 10);
    queue_enqueue(&q, 20);
    queue_enqueue(&q, 30);

    int value;
    queue_dequeue(&q, &value);
    printf("Dequeued: %d\n", value);

    queue_destroy(&q);
    return 0;
}
```