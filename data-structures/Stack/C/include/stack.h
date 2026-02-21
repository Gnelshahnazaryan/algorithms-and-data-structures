#ifndef STACK_H
#define STACK_H

#include "../../../Deque/C/include/deque.h"

/*
 * Stack implemented as abstraction over Deque
 * LIFO behavior:
 *   push  -> deque_push_back
 *   pop   -> deque_pop_back
 *   peek  -> deque_back
 */

typedef DequeResult StackResult;

typedef struct
{
    Deque* dq;
} Stack;

/* Initialization */
StackResult stack_init(Stack* s, size_t capacity);
void stack_free(Stack* s);

/* Core operations */
StackResult stack_push(Stack* s, int value);
StackResult stack_pop(Stack* s, int* out);
StackResult stack_peek(Stack* s, int* out);

/* State */
int stack_is_empty(Stack* s);
int stack_size(Stack* s);

#endif // STACK_H