#include <stdio.h>
#include <stdlib.h>
#include "../include/singly-linked-list.h"

static int int_cmp(int a, int b)
{
    return a - b;
}

static void print_list(const SinglyLinkedList* list)
{
    if (sl_size(list) == 0)
    {
        printf("[ ]\n");
        return;
    }

    int* arr = malloc(sizeof(int) * sl_size(list));
    if (!arr)
    {
        printf("malloc failed\n");
        return;
    }

    sl_to_array(list, &arr);

    printf("[ ");
    for (int i = 0; i < sl_size(list); ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");

    free(arr);
}

int main(void)
{
    SinglyLinkedList list;
    SinglyLinkedList other;
    SL_Result res;
    int out;

    printf("=== INIT ===\n");
    res = sl_init(&list);
    if (res != SL_OK) return 1;
    res = sl_init(&other);
    if (res != SL_OK) return 1;

    printf("list empty=%d size=%d\n", sl_is_empty(&list), sl_size(&list));

    printf("\n=== PUSH FRONT / BACK ===\n");
    sl_push_front(&list, 3);
    sl_push_front(&list, 2);
    sl_push_front(&list, 1);
    sl_push_back(&list, 4);
    sl_push_back(&list, 5);
    print_list(&list);

    printf("\n=== FRONT ===\n");
    if (sl_front(&list, &out) == SL_OK)
        printf("front = %d\n", out);

    printf("\n=== AT ===\n");
    for (int i = 0; i < sl_size(&list); ++i)
    {
        if (sl_at(&list, i, &out) == SL_OK)
            printf("at[%d] = %d\n", i, out);
    }

    printf("\n=== INSERT ===\n");
    sl_insert(&list, 0, 1, 100);  // insert 1 x 100 at index 0
    sl_insert(&list, 3, 2, 200);  // insert 2 x 200 at index 3
    print_list(&list);

    printf("\n=== ERASE ===\n");
    sl_erase(&list, 0, &out);
    printf("erased = %d\n", out);
    print_list(&list);

    printf("\n=== POP FRONT / BACK ===\n");
    sl_pop_front(&list, &out);
    printf("pop_front = %d\n", out);
    sl_pop_back(&list, &out);
    printf("pop_back = %d\n", out);
    print_list(&list);

    printf("\n=== REMOVE value=200 ===\n");
    sl_remove(&list, 200, int_cmp, &out);
    printf("removed count = %d\n", out);
    print_list(&list);

    
    printf("\n=== REVERSE ===\n");
    sl_reverse(&list);
    print_list(&list);

    printf("\n=== SORT ===\n");
    sl_sort(&list, int_cmp);
    print_list(&list);

    printf("\n=== MERGE ===\n");
    sl_clear(&other);
    sl_push_back(&other, 1);
    sl_push_back(&other, 2);
    sl_push_back(&other, 3);
    sl_sort(&other, int_cmp);
    sl_merge(&list, &other, int_cmp);
    print_list(&list);

    printf("\n=== CLEAR ===\n");
    sl_clear(&list);
    print_list(&list);
    printf("size=%d empty=%d\n", sl_size(&list), sl_is_empty(&list));

    printf("\n=== DESTROY ===\n");
    sl_destroy(&list);
    sl_destroy(&other);

    printf("ALL TESTS DONE\n");
    return 0;
}