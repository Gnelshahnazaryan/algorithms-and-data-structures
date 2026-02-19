# Overview (JavaScript Implementation)

The **Circular Deque** is a double-ended queue implemented in JavaScript using a **circular buffer (ring buffer)** design.

It supports efficient insertion and removal of elements from both the front and the back in constant time **O(1)**, without shifting elements in memory.

Unlike JavaScript's native arrays — where operations like `shift()` and `unshift()` may cost **O(n)** due to element reindexing — this implementation guarantees predictable performance by manually controlling internal indices.

---

## Core Features

- Circular indexing using modular arithmetic
- True O(1) push and pop operations
- Logical indexing independent from physical storage
- Rotation operations (`rotateLeft`, `rotateRight`)
- Search utilities (`find`, `includes`)
- Functional-style methods (`map`, `reduce`)
- Deep copy support
- Predictable and stable performance
- Explicit capacity management

---

## Internal Structure

The deque internally maintains:

- `data` → underlying array (fixed capacity buffer)
- `size` → number of stored elements
- `capacity` → allocated storage size
- `front` → index of the first logical element

Instead of shifting elements when inserting at the front, the structure updates the `front` index using circular arithmetic: