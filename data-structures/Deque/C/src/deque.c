#include "../include/deque.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================
 *  Static Helpers
 * ======================== */

static void resize(Deque* deque)
{
    if (deque->size < deque->capacity)
    {
        return;
    }

    int* tmp = (int*)malloc(deque->capacity * 2 * sizeof(int));
    assert(tmp != NULL);

    for (size_t i = 0; i < deque->size; ++i)
    {
        size_t idx = (deque->front + i) % deque->capacity;
        tmp[i] = deque->data[idx];
    }

    free(deque->data);
    deque->front = 0;
    deque->data = tmp;
    deque->capacity *= 2;
}

/* =========================
 *  Lifecycle
 * ========================= */

DequeResult deque_init(Deque* deque, size_t capacity)
{
    if (deque == NULL)
    {
        return DEQUE_ERR_NULL;
    }

    deque->size = 0;
    deque->front = 0;
    deque->capacity = capacity;
    deque->data = (int*)malloc(capacity * sizeof(int));
    if (deque->data == NULL)
    {
        return DEQUE_ERR_ALLOC;
    }

    return DEQUE_OK;
}

void deque_destroy(Deque** deque)
{
    if (deque == NULL || *deque == NULL)
    {
        return;
    }

    free((*deque)->data);
    (*deque)->data = NULL;

    (*deque)->size = 0;
    (*deque)->capacity = 0;
    (*deque)->front = 0;

    free(*deque);
    *deque = NULL;
}

/* =========================
 *  Capacity / State
 * ========================= */

size_t deque_size(const Deque* deque)
{
    assert(deque != NULL);
    return deque->size;
}

size_t deque_capacity(const Deque* deque)
{
    assert(deque != NULL);
    return deque->capacity;
}

int deque_is_empty(const Deque* deque)
{
    assert(deque != NULL);
    return deque->size == 0;
}

int deque_is_full(const Deque* deque)
{
    assert(deque != NULL);
    return deque->capacity == deque->size;
}

/* =========================
 *  Push / Pop
 * ========================= */

DequeResult deque_push_back(Deque* deque, int value)
{
    if (deque == NULL)
    {
        return DEQUE_ERR_NULL;
    }

    resize(deque);

    size_t idx = (deque->front + deque->size) % deque->capacity;
    deque->data[idx] = value;
    ++deque->size;

    return DEQUE_OK;
}

DequeResult deque_push_front(Deque* deque, int value)
{
    if (deque == NULL)
    {
        return DEQUE_ERR_NULL;
    }

    resize(deque);

    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    deque->data[deque->front] = value;
    ++deque->size;

    return DEQUE_OK;
}

DequeResult deque_pop_back(Deque* deque, int* out_value)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    size_t idx = (deque->front + deque->size - 1) % deque->capacity;
    *out_value = deque->data[idx];
    --deque->size;

    return DEQUE_OK;
}

DequeResult deque_pop_front(Deque* deque, int* out_value)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    *out_value = deque->data[deque->front];
    deque->front = deque->front + 1 == deque->capacity ? 0 : ++deque->front;
    --deque->size;

    return DEQUE_OK;
}

/* =========================
 *  Element Access
 * ========================= */

DequeResult deque_back(const Deque* deque, int* out_value)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    size_t idx = (deque->front + deque->size - 1) % deque->capacity;
    *out_value = deque->data[idx];

    return DEQUE_OK;
}

DequeResult deque_front(const Deque* deque, int* out_value)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    *out_value = deque->data[deque->front];

    return DEQUE_OK;
}

DequeResult deque_at(const Deque* deque, size_t index, int* out_value)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    if (index >= deque->size)
    {
        return DEQUE_ERR_NOT_FOUND;
    }

    size_t idx = (deque->front + index) % deque->capacity;
    *out_value = deque->data[idx];

    return DEQUE_OK;
}

/* =========================
 *  Rotation / Swaping
 * ========================= */

DequeResult deque_rotate_right(Deque* deque, size_t k)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    k %= deque->size;
    while (k--)
    {
        int value;
        deque_pop_back(deque, &value);
        deque_push_front(deque, value);
    }

    return DEQUE_OK;
}

DequeResult deque_rotate_left(Deque* deque, size_t k)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    k %= deque->size;
    while (k--)
    {
        int value;
        deque_pop_front(deque, &value);
        deque_push_back(deque, value);
    }

    return DEQUE_OK;
}

DequeResult deque_swap(Deque* deque, size_t i, size_t j)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return DEQUE_ERR_EMPTY;
    }

    if (i >= deque->size || j >= deque->size)
    {
        return DEQUE_ERR_NOT_FOUND;
    }

    size_t idxI = (deque->front + i) % deque->capacity;
    size_t idxJ = (deque->front + j) % deque->capacity;

    deque->data[idxI] ^= deque->data[idxJ];
    deque->data[idxJ] ^= deque->data[idxI];
    deque->data[idxI] ^= deque->data[idxJ];

    return DEQUE_OK;
}

/* =========================
 *  Search / Compare
 * ========================= */

int deque_find(const Deque* deque, int value)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return -1;
    }

    for (size_t i = 0; i < deque->size; ++i)
    {
        int out_val;
        deque_at(deque, i, &out_val);
        if (out_val == value)
        {
            return i;
        }
    }

    return -1;
}

bool deque_includes(const Deque* deque, int value)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return false;
    }

    if (deque_find(deque, value) >= 0)
    {
        return true;
    }

    return false;
}

bool deque_equals(const Deque* a, const Deque* b)
{
    if (a == NULL || b == NULL)
    {
        return false;
    }

    if (a->size != b->size)
    {
        return false;
    }

    for (size_t i = 0; i < a->size; ++i)
    {
        size_t idxA = (a->front + i) % a->capacity;
        size_t idxB = (b->front + i) % b->capacity;
        if (a->data[idxA] != b->data[idxB])
        {
            return false;
        }
    }

    return true;
}

/* =========================
 *  Functional-style Operations
 * ========================= */

Deque* deque_map(const Deque* deque,
                 int (*fn)(int value, size_t index, const Deque* deque))
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return NULL;
    }

    Deque* result = (Deque*)malloc(sizeof(Deque));
    if (result == NULL)
    {
        return result;
    }

    result->capacity = deque->capacity;
    result->data = (int*)malloc(result->capacity * sizeof(int));
    if (result->data == NULL)
    {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < deque->size; ++i)
    {
        size_t idx = (deque->front + i) % deque->capacity;
        deque_push_back(result, fn(deque->data[idx], i, deque));
    }

    return result;
}

int deque_reduce(const Deque* deque,
                 int (*fn)(int acc, int value, size_t index,
                           const Deque* deque),
                 int initial)
{
    if (deque == NULL || deque_is_empty(deque))
    {
        return initial;
    }

    int acc = initial;

    for (size_t i = 0; i < deque->size; ++i)
    {
        size_t idx = (deque->front + i) % deque->capacity;
        acc = fn(acc, deque->data[idx], i, deque);
    }

    return acc;
}

/* =========================
 *  Memory Utilities
 * ========================= */

DequeResult deque_reserve(Deque* deque, size_t new_capacity)
{
    if (deque == NULL)
    {
        return DEQUE_ERR_NULL;
    }

    if (new_capacity <= deque->capacity)
    {
        return DEQUE_ERR_NULL;
    }

    int* tmp = (int*)malloc(new_capacity * sizeof(int));
    if (tmp == NULL)
    {
        return DEQUE_ERR_ALLOC;
    }

    for (size_t i = 0; i < deque->size; ++i)
    {
        size_t idx = (deque->front + i) % deque->capacity;
        tmp[i] = deque->data[idx];
    }

    deque->data = tmp;
    deque->capacity = new_capacity;
    deque->front = 0;

    return DEQUE_OK;
}

DequeResult deque_shrink_to_fit(Deque* deque)
{
    if (deque == NULL)
    {
        return DEQUE_ERR_NULL;
    }

    if (deque->size == deque->capacity)
    {
        return DEQUE_OK;
    }

    int* tmp = (int*)malloc(deque->size * sizeof(int));
    if (tmp == NULL)
    {
        return DEQUE_ERR_ALLOC;
    }

    for (size_t i = 0; i < deque->size; ++i)
    {
        size_t idx = (deque->front + i) % deque->capacity;
        tmp[i] = deque->data[idx];
    }

    deque->capacity = deque->size;
    deque->front = 0;
    deque->data = tmp;

    return DEQUE_OK;
}

void deque_clear(Deque* deque)
{
    if (deque == NULL)
    {
        return;
    }

    if (deque_is_empty(deque))
    {
        return;
    }

    deque->size = 0;
    deque->front = 0;
}

/* =========================
 *  Copy
 * ========================= */

DequeResult deque_clone(const Deque* src, Deque* dest)
{
    if (src == NULL || dest == NULL)
    {
        return DEQUE_ERR_NULL;
    }

    dest->front = 0;
    dest->size = src->size;
    dest->capacity = src->capacity;
    dest->data = (int*)malloc(dest->capacity * sizeof(int));
    if (dest->data == NULL)
    {
        return DEQUE_ERR_ALLOC;
    }

    if (src->size == 0)
    {
        return DEQUE_OK;
    }

    for (size_t i = 0; i < src->size; ++i)
    {
        size_t idx = (src->front + i) % src->capacity;
        dest->data[i] = src->data[idx];
    }

    return DEQUE_OK;
}