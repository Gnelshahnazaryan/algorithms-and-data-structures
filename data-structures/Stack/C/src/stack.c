#include "../include/stack.h"
#include "../../../Deque/C/include/deque.h"
#include <stdlib.h>

/* Initialization & Destruction */

StackResult stack_init(Stack *s, size_t capacity) {
    if (!s)
        return DEQUE_ERR_NULL;

    s->dq = malloc(sizeof(Deque));
    if (!s->dq)
        return DEQUE_ERR_ALLOC;

    return deque_init(s->dq, capacity);
}

void stack_free(Stack* s)
{
    if (!s)
    {
        return;
    }

    return deque_destroy(&s->dq);
}

/* Core operations */

StackResult stack_push(Stack* s, int value)
{
    if (!s)
    {
        return DEQUE_ERR_NULL;
    }

    return deque_push_back(s->dq, value);
}

StackResult stack_pop(Stack* s, int* out)
{
    if (!s)
    {
        return DEQUE_ERR_NULL;
    }

    return deque_pop_back(s->dq, out);
}

StackResult stack_peek(Stack* s, int* out)
{
    if (!s)
    {
        return DEQUE_ERR_NULL;
    }

    return deque_back(s->dq, out);
}

/* State */

int stack_is_empty(Stack* s)
{
    if (!s)
    {
        return -1;
    }

    return deque_is_empty(s->dq);
}

int stack_size(Stack* s)
{
    if (!s)
    {
        return -1;
    }

    return deque_size(s->dq);
}