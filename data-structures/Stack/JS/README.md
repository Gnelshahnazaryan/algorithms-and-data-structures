# Stack Library (JavaScript)

This is a **Stack** data structure implemented as an **abstraction over a circular Deque** in JavaScript.  
It provides a clean **LIFO (Last In, First Out) interface** while reusing a dynamic circular buffer implementation.

---

## Features

- LIFO behavior (Last In, First Out)
- Dynamic memory allocation via internal array resizing
- Fully encapsulated stack operations
- Works in modern JavaScript (ES Modules)
- Error handling using `throw` statements

---

## Time & Space Complexity

The Stack implemented over a circular Deque in JavaScript has the following complexities:

| Operation     | Time Complexity | Space Complexity | Notes                                                       |
| ------------- | --------------- | ---------------- | ----------------------------------------------------------- |
| `constructor` | O(n)            | O(n)             | Allocates internal array of given capacity                  |
| `push`        | O(1) amortized  | O(1)             | Inserts at rear/top; may trigger resize doubling array size |
| `pop`         | O(1)            | O(1)             | Removes top element                                         |
| `peek`        | O(1)            | O(1)             | Reads top element without removing                          |
| `isEmpty`     | O(1)            | O(1)             | Checks if stack is empty                                    |
| `size`        | O(1)            | O(1)             | Returns current number of elements                          |

### Notes

- All operations are **constant time** except for `push` when dynamic resizing occurs.
- Push is **O(1) amortized** because occasionally the internal array doubles in size.
- Space complexity refers to extra memory used per operation (the main buffer allocation is O(n)).
- Stack operations delegate storage to the underlying Deque, which handles circular indexing internally.
