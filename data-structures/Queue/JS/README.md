# Circular Queue Implementation in JavaScript

## Overview

A **Queue** is a linear data structure that follows the **FIFO (First In, First Out)** principle:

- Elements are added at the **rear** and removed from the **front**.
- This implementation uses a **circular array** to efficiently utilize all allocated space.
- Supports **constant-time operations**: enqueue, dequeue, and peek.
- Handles **overflow** and **underflow** errors properly.

**Use Cases:**

- Task scheduling in JavaScript applications
- Event handling and asynchronous queues
- BFS (Breadth-First Search) in algorithms
- Job or message processing systems

---

## Features

- Circular array for efficient memory usage
- Constant-time enqueue, dequeue, and peek operations
- Overflow and underflow detection using JavaScript `Error`
- Easy-to-use API: `enqueue`, `dequeue`, `peek`, `isEmpty`, `isFull`, `print`

---

## Queue Methods

| Method           | Description                                 | Complexity |
| ---------------- | ------------------------------------------- | ---------- |
| `enqueue(value)` | Add element at the rear                     | O(1)       |
| `dequeue()`      | Remove element from the front and return it | O(1)       |
| `peek()`         | Return front element without removing       | O(1)       |
| `isEmpty()`      | Check if queue is empty                     | O(1)       |
| `isFull()`       | Check if queue is full                      | O(1)       |
| `print()`        | Print all queue elements in order           | O(n)       |

---

## Example Usage

```js
// Create a queue with capacity 5
const q = new Queue(5);

q.enqueue(1);
q.enqueue(2);
q.enqueue(3);
q.enqueue(4);

q.print();
// Output:
// 1
// 2
// 3
// 4

console.log('Dequeued:', q.dequeue()); // Dequeued: 1
q.enqueue(5);
q.print();
// Output:
// 2
// 3
// 4
// 5
```