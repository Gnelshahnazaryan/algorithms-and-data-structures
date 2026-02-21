#include "../include/stack.h"
#include <stdio.h>

static void print_result(StackResult res)
{
    switch (res)
    {
    case DEQUE_OK:
        printf("Result: OK\n");
        break;
    case DEQUE_ERR_NULL:
        printf("Error: NULL pointer\n");
        break;
    case DEQUE_ERR_EMPTY:
        printf("Error: Stack is empty\n");
        break;
    case DEQUE_ERR_ALLOC:
        printf("Error: Allocation failed\n");
        break;
    case DEQUE_ERR_NOT_FOUND:
        printf("Error: Not found\n");
        break;
    default:
        printf("Error: Unknown\n");
    }
}

int main()
{
    Stack s;
    StackResult res;
    int value;

    /* INIT */
    res = stack_init(&s, 5);
    if (res != DEQUE_OK)
    {
        print_result(res);
        return 1;
    }

    printf("Stack initialized\n");

    /* PUSH */
    for (int i = 1; i <= 5; i++)
    {
        res = stack_push(&s, i * 100);
        if (res != DEQUE_OK)
        {
            print_result(res);
            stack_free(&s);
            return 1;
        }
        printf("Pushed: %d\n", i * 100);
    }

    /* PEEK */
    res = stack_peek(&s, &value);
    if (res == DEQUE_OK)
        printf("Top element: %d\n", value);
    else
        print_result(res);

    /* POP ALL */
    printf("\nPopping elements:\n");

    while (1)
    {
        res = stack_pop(&s, &value);

        if (res == DEQUE_ERR_EMPTY)
        {
            printf("Stack is empty\n");
            break;
        }

        if (res != DEQUE_OK)
        {
            print_result(res);
            break;
        }

        printf("Popped: %d\n", value);
    }

    /* TRY POP AGAIN (should error) */
    res = stack_pop(&s, &value);
    print_result(res);

    return 0;
}