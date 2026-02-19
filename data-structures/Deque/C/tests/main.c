#include "../include/deque.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Map function example
int double_value(int value, size_t index, const Deque* deque)
{
    (void)index;
    (void)deque;
    return value * 2;
}

// Reduce function example
int sum_values(int acc, int value, size_t index, const Deque* deque)
{
    (void)index;
    (void)deque;
    return acc + value;
}

// Utility to print deque
void print_deque(const Deque* dq)
{
    printf("[");
    for (size_t i = 0; i < deque_size(dq); ++i)
    {
        int val;
        deque_at(dq, i, &val);
        printf("%d", val);
        if (i + 1 < deque_size(dq))
            printf(", ");
    }
    printf("]\n");
}

int main(void)
{
    // --------------------------
    // 1. Heap-allocated deque
    // --------------------------
    Deque* dq = malloc(sizeof(Deque));
    if (!dq || deque_init(dq, 5) != DEQUE_OK)
    {
        fprintf(stderr, "Failed to init deque\n");
        return 1;
    }

    // Push elements
    deque_push_back(dq, 1);
    deque_push_back(dq, 2);
    deque_push_front(dq, 0); // deque: [0,1,2]
    printf("After pushes: ");
    print_deque(dq);

    // Peek
    int front, back, at1;
    deque_front(dq, &front);
    deque_back(dq, &back);
    deque_at(dq, 1, &at1);
    printf("Front: %d, Back: %d, At index 1: %d\n", front, back, at1);

    // Rotate
    deque_rotate_right(dq, 1);
    printf("After rotate_right(1): ");
    print_deque(dq);

    deque_rotate_left(dq, 2);
    printf("After rotate_left(2): ");
    print_deque(dq);

    // Swap
    deque_swap(dq, 0, 1);
    printf("After swap(0,1): ");
    print_deque(dq);

    // Search / includes
    printf("Includes 2? %s\n", deque_includes(dq, 2) ? "Yes" : "No");
    printf("Find 1 index: %d\n", deque_find(dq, 1));

    // Clone
    Deque* clone = malloc(sizeof(Deque));
    if (!clone || deque_init(clone, dq->capacity) != DEQUE_OK)
    {
        fprintf(stderr, "Failed to init clone\n");
        deque_destroy(&dq);
        return 1;
    }

    if (deque_clone(dq, clone) == DEQUE_OK)
    {
        printf("Cloned deque: ");
        print_deque(clone);
        printf("Equals clone? %s\n", deque_equals(dq, clone) ? "Yes" : "No");
    }

    // Map
    Deque* mapped = deque_map(dq, double_value);
    printf("Mapped (doubled) deque: ");
    print_deque(mapped);

    // Reduce
    int sum = deque_reduce(dq, sum_values, 0);
    printf("Reduce sum: %d\n", sum);

    // Pop
    int val;
    deque_pop_back(dq, &val);
    printf("Pop back: %d\n", val);
    deque_pop_front(dq, &val);
    printf("Pop front: %d\n", val);
    printf("After pops: ");
    print_deque(dq);

    // Capacity / resize
    printf("Size: %zu, Capacity: %zu\n", deque_size(dq), deque_capacity(dq));
    deque_reserve(dq, 10);
    printf("After reserve(10) Capacity: %zu\n", deque_capacity(dq));
    deque_shrink_to_fit(dq);
    printf("After shrink_to_fit Capacity: %zu\n", deque_capacity(dq));

    // Clear
    deque_clear(dq);
    printf("After clear: ");
    print_deque(dq);

    // --------------------------
    // 2. Destroy deques
    // --------------------------
    deque_destroy(&dq);
    deque_destroy(&clone);
    deque_destroy(&mapped);

    printf("All deques destroyed safely.\n");

    return 0;
}
