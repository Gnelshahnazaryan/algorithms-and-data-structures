# Stack Library (C)

This is a **Stack** data structure implemented as an **abstraction over a circular Deque** in C.  
It provides a clean **LIFO interface** while reusing a dynamic circular buffer implementation.

---

## Features

- LIFO behavior (Last In, First Out)
- Dynamic memory allocation for the internal buffer
- Fully encapsulated stack operations
- Error handling via `StackResult` enum
- Easy to extend (Queue, Deque, etc.)

---

## Stack API

```c
#include "include/stack.h"

/* Initialization & Destruction */
StackResult stack_init(Stack *s, int capacity);
void stack_destroy(Stack *s);

/* Core Operations */
StackResult stack_push(Stack *s, int value);
StackResult stack_pop(Stack *s, int *out);
StackResult stack_peek(Stack *s, int *out);

/* State Checks */
StackResult stack_is_empty(Stack *s, int *out);
StackResult stack_size(Stack *s, int *out);
```

## Time & Space Complexity

The Stack implemented over a circular Deque has the following complexities:

| Operation        | Time Complexity | Space Complexity | Notes                                             |
| ---------------- | --------------- | ---------------- | ------------------------------------------------- |
| `stack_init`     | O(n)            | O(n)             | Allocates buffer of capacity n                    |
| `stack_destroy`  | O(1)            | O(1)             | Frees internal buffer                             |
| `stack_push`     | O(1) amortized  | O(1)             | Insert at rear; may require resize if implemented |
| `stack_pop`      | O(1)            | O(1)             | Remove from rear                                  |
| `stack_peek`     | O(1)            | O(1)             | Access rear element without removing              |
| `stack_is_empty` | O(1)            | O(1)             | Check size == 0                                   |
| `stack_size`     | O(1)            | O(1)             | Return current number of elements                 |

### Notes

- All operations are **constant time** except initialization which allocates memory.
- Push is O(1) amortized if dynamic resizing is used.
- Space complexity refers to extra memory per operation (not counting the stack struct itself).
- Stack size grows dynamically if deque supports resizing (optional).
