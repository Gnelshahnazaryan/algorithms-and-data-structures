#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <stddef.h> /* size_t */

/* =========================
 *  Result Codes
 * ========================= */
typedef enum
{
    DEQUE_OK = 0,
    DEQUE_ERR_NULL,
    DEQUE_ERR_EMPTY,
    DEQUE_ERR_ALLOC,
    DEQUE_ERR_NOT_FOUND
} DequeResult;

/* =========================
 *  Deque Structure
 * ========================= */
typedef struct
{
    int* data;       /* circular buffer */
    size_t size;     /* number of elements */
    size_t capacity; /* allocated capacity */
    size_t front;    /* index of first element */
} Deque;

/* =========================
 *  Lifecycle
 * ========================= */

DequeResult deque_init(Deque* deque, size_t capacity);
void deque_destroy(Deque** deque);

/* =========================
 *  Capacity / State
 * ========================= */

size_t deque_size(const Deque* deque);
size_t deque_capacity(const Deque* deque);

int deque_is_empty(const Deque* deque);
int deque_is_full(const Deque* deque);

/* =========================
 *  Push / Pop
 * ========================= */

DequeResult deque_push_back(Deque* deque, int value);
DequeResult deque_push_front(Deque* deque, int value);

DequeResult deque_pop_back(Deque* deque, int* out_value);
DequeResult deque_pop_front(Deque* deque, int* out_value);

/* =========================
 *  Element Access
 * ========================= */

DequeResult deque_back(const Deque* deque, int* out_value);
DequeResult deque_front(const Deque* deque, int* out_value);
DequeResult deque_at(const Deque* deque, size_t index, int* out_value);

/* =========================
 *  Rotation / Swaping
 * ========================= */

DequeResult deque_rotate_right(Deque* deque, size_t k);
DequeResult deque_rotate_left(Deque* deque, size_t k);
DequeResult deque_swap(Deque* deque, size_t i, size_t j);

/* =========================
 *  Search / Compare
 * ========================= */

int deque_find(const Deque* deque, int value);
bool deque_includes(const Deque* deque, int value);
bool deque_equals(const Deque* a, const Deque* b);

/* =========================
 *  Functional-style Operations
 * ========================= */

Deque* deque_map(const Deque* deque, int (*fn)(int value, size_t index, const Deque* deque));
int deque_reduce(const Deque* deque,
                 int (*fn)(int acc, int value, size_t index, const Deque* deque),
                 int initial);

/* =========================
 *  Memory Utilities
 * ========================= */

DequeResult deque_reserve(Deque* deque, size_t new_capacity);
DequeResult deque_shrink_to_fit(Deque* deque);
void deque_clear(Deque* deque);

/* =========================
 *  Copy
 * ========================= */

DequeResult deque_clone(const Deque* src, Deque* dest);

#endif /* DEQUE_H */