#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Queue Data Structure (Circular Array Implementation)
 * FIFO - First In, First Out
 */

typedef struct
{
    int* data;       // pointer to dynamically allocated array
    size_t capacity; // maximum number of elements
    size_t size;     // current number of elements
    int front;    // index of first element
    int rear;     // index of last element
} Queue;

typedef enum
{
    QUEUE_OK = 0,
    QUEUE_ERROR_ALLOCATION,
    QUEUE_ERROR_NULL_POINTER,
    QUEUE_ERROR_OVERFLOW,
    QUEUE_ERROR_UNDERFLOW
} QueueStatus;

/* ================================
   Constructor / Destructor
   ================================ */

/* Initialize queue with given capacity */
QueueStatus queue_init(Queue* q, size_t capacity);

/* Free allocated memory */
QueueStatus queue_destroy(Queue* q);

/* ================================
    Core Operations
   ================================ */

/* Insert element at rear */
QueueStatus queue_enqueue(Queue* q, int value);

/* Remove element from front */
QueueStatus queue_dequeue(Queue* q, int* removed_value);

/* Get front element without removing */
QueueStatus queue_peek(const Queue* q, int* value);

/* ================================
   Utility Functions
   ================================ */

QueueStatus queue_is_empty(const Queue* q, int* result);

QueueStatus queue_is_full(const Queue* q, int* result);

QueueStatus queue_size(const Queue* q, size_t* size);

QueueStatus queue_capacity(const Queue* q, size_t* capacity);

#endif /* QUEUE_H */