# Priority Queue (Heap-based)

- A **Priority Queue** is a data structure where elements are processed based on **priority**, not insertion order.

- It is most efficiently implemented using a **Binary Heap**.

- There are two main types:
  - **Min Heap** → smallest element has highest priority
  - **Max Heap** → largest element has highest priority

- Key internal operations:
  - **shiftUp** → used after insertion
  - **shiftDown** → used after deletion

- Widely used in:
  - Graph algorithms (Dijkstra, A*)
  - Scheduling systems
  - Top-K problems

---

## Features

- Efficient insertion and deletion
- Maintains sorted priority implicitly
- Supports dynamic data
- Works in **O(log n)** time for key operations

---

## Types

| Type     | Behavior                     |
| -------- | ---------------------------- |
| Min Heap | Smallest element comes first |
| Max Heap | Largest element comes first  |

---

## How Heap Works

A **Binary Heap** is a complete binary tree:

- Stored in an array
- Parent-child relationships:
  - `parent = Math.floor((i - 1) / 2)`
  - `left = 2*i + 1`
  - `right = 2*i + 2`

### Heap Property

- **Min Heap:** parent ≤ children
- **Max Heap:** parent ≥ children

---

## Time & Space Complexity

| Operation | Time Complexity |
| --------- | --------------- |
| add       | O(log n)        |
| pop       | O(log n)        |
| peek      | O(1)            |
| remove    | O(n)            |
| size      | O(1)            |
| isEmpty   | O(1)            |
| clear     | O(1)            |

---
