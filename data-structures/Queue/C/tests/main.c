#include "../include/queue.h"
#include <stdio.h>

int main(void)
{
    Queue q;
    QueueStatus status;

    /* Initialize queue */
    status = queue_init(&q, 5);
    if (status != QUEUE_OK)
    {
        printf("Initialization failed\n");
        return 1;
    }

    printf("Enqueue 1,2,3,4\n");

    queue_enqueue(&q, 1);
    queue_enqueue(&q, 2);
    queue_enqueue(&q, 3);
    queue_enqueue(&q, 4);

    /* Print current elements */
    printf("Current queue:\n");
    for (size_t i = 0; i < q.size; ++i)
    {
        size_t idx = (q.front + i) % q.capacity;
        printf("%d ", q.data[idx]);
    }
    printf("\n");

    /* Dequeue two elements */
    int removed;
    queue_dequeue(&q, &removed);
    printf("Dequeued: %d\n", removed);

    queue_dequeue(&q, &removed);
    printf("Dequeued: %d\n", removed);

    /* Enqueue more elements (test circular behavior) */
    printf("Enqueue 5,6\n");
    queue_enqueue(&q, 5);
    queue_enqueue(&q, 6);

    printf("Queue after circular enqueue:\n");
    for (size_t i = 0; i < q.size; ++i)
    {
        size_t idx = (q.front + i) % q.capacity;
        printf("%d ", q.data[idx]);
    }
    printf("\n");

    /* Test overflow */
    status = queue_enqueue(&q, 7);
    if (status == QUEUE_ERROR_OVERFLOW)
    {
        printf("Overflow detected correctly\n");
    }

    /* Empty the queue completely */
    printf("Emptying queue:\n");
    int is_empty;

    while (1)
    {
        queue_is_empty(&q, &is_empty);

        if (is_empty)
            break;

        queue_dequeue(&q, &removed);
        printf("%d ", removed);
    }
    printf("\n");

    /* Test underflow */
    status = queue_dequeue(&q, &removed);
    if (status == QUEUE_ERROR_UNDERFLOW)
    {
        printf("Underflow detected correctly\n");
    }

    queue_destroy(&q);

    return 0;
}