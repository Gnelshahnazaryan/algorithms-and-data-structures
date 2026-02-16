# Singly Linked List in JavaScript

A fully featured **Singly Linked List** implemented in JavaScript with a clean object-oriented API.

---

## Features

- Node-based linked list structure
- Push / Pop operations (front & back)
- Insert and erase by index
- Remove elements by value with optional comparator
- Reverse list in-place
- Merge two sorted lists
- Merge Sort implemented for linked lists
- Full iteration support with `for...of`
- Error handling via exceptions or contract-based returns

---

## Lifecycle

| Function                         | Description                                           | Time Complexity                 | Space Complexity                |
| -------------------------------- | ----------------------------------------------------- | ------------------------------- | ------------------------------- |
| `new SinglyLinkedList(iterable)` | Creates a new empty list or initializes from iterable | O(n) if iterable, O(1) if empty | O(n) if iterable, O(1) if empty |
| `clear()`                        | Removes all nodes from the list                       | O(n)                            | O(1)                            |

---

## Size & State

| Function    | Description                 | Time Complexity | Space Complexity |
| ----------- | --------------------------- | --------------- | ---------------- |
| `size()`    | Returns the number of nodes | O(1)            | O(1)             |
| `isEmpty()` | Checks if the list is empty | O(1)            | O(1)             |

---

## Element Access

| Function    | Description                         | Time Complexity | Space Complexity |
| ----------- | ----------------------------------- | --------------- | ---------------- |
| `front()`   | Returns the value of the first node | O(1)            | O(1)             |
| `at(index)` | Returns value at a specific index   | O(n)            | O(1)             |

---

## Modifiers

| Function                | Description                      | Time Complexity | Space Complexity |
| ----------------------- | -------------------------------- | --------------- | ---------------- |
| `push_front(val)`       | Insert a new node at the head    | O(1)            | O(1)             |
| `push_back(val)`        | Insert a new node at the tail    | O(n)            | O(1)             |
| `insert(index, val)`    | Insert node at specific index    | O(n)            | O(1)             |
| `pop_front()`           | Remove the first node            | O(1)            | O(1)             |
| `pop_back()`            | Remove the last node             | O(n)            | O(1)             |
| `erase(index)`          | Remove node at specific index    | O(n)            | O(1)             |
| `remove(value, equals)` | Remove all nodes matching value  | O(n)            | O(1)             |
| `reverse()`             | Reverse the linked list in place | O(n)            | O(1)             |

---

## Algorithms

| Function           | Description                     | Time Complexity | Space Complexity     |
| ------------------ | ------------------------------- | --------------- | -------------------- |
| `sort(cmp)`        | Sorts the list using merge sort | O(n log n)      | O(log n) (recursion) |
| `merge(list, cmp)` | Merges two sorted lists         | O(n + m)        | O(1)                 |

_Notes:_

- `n` = size of current list, `m` = size of second list in `merge()`.
- `sort()` preserves node objects, does not copy values.

---

## 🔄 Iteration

- Supports `[Symbol.iterator]()`
