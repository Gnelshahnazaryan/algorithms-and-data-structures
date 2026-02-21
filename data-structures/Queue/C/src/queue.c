#include "../include/queue.h"

#include <stdlib.h>

QueueStatus queue_init(Queue* q, size_t capacity)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    q->data = (int*)malloc(capacity * sizeof(int));
    if (q->data == NULL)
    {
        return QUEUE_ERROR_ALLOCATION;
    }

    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->rear = -1;

    return QUEUE_OK;
}

QueueStatus queue_destroy(Queue* q)
{
    if (q == NULL)
    {
        return QUEUE_OK;
    }

    free(q->data);
    q->data = NULL;
    q->capacity = 0;
    q->size = 0;
    q->front = 0;
    q->rear = -1;

    return QUEUE_OK;
}

/* ================================
    Core Operations
   ================================ */

QueueStatus queue_enqueue(Queue* q, int value)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    int result;
    queue_is_full(q, &result);
    if (result)
    {
        return QUEUE_ERROR_OVERFLOW;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    ++q->size;

    return QUEUE_OK;
}

QueueStatus queue_dequeue(Queue* q, int* removed_value)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    int result;
    queue_is_empty(q, &result);
    if (result)
    {
        return QUEUE_ERROR_UNDERFLOW;
    }

    *removed_value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    --q->size;

    return QUEUE_OK;
}

QueueStatus queue_peek(const Queue* q, int* value)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    int result;
    queue_is_empty(q, &result);
    if (result)
    {
        return QUEUE_ERROR_UNDERFLOW;
    }

    *value = q->data[q->front];
    return QUEUE_OK;
}

QueueStatus queue_is_empty(const Queue* q, int* result)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    *result = q->size == 0 ? 1 : 0;

    return QUEUE_OK;
}

QueueStatus queue_is_full(const Queue* q, int* result)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    *result = q->size == q->capacity ? 1 : 0;

    return QUEUE_OK;
}

QueueStatus queue_size(const Queue* q, size_t* size)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    *size = q->size;

    return QUEUE_OK;
}

QueueStatus queue_capacity(const Queue* q, size_t* capacity)
{
    if (q == NULL)
    {
        return QUEUE_ERROR_NULL_POINTER;
    }

    *capacity = q->capacity;

    return QUEUE_OK;
}