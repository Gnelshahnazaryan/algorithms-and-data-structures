#include "../include/singly-linked-list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ================= Static Helpers ================= */

static Node* merge_nodes(Node* a, Node* b, int (*cmp)(int, int))
{
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    while (a && b)
    {
        if (cmp(a->value, b->value) <= 0)
        {
            tail->next = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b = b->next;
        }

        tail = tail->next;
    }

    tail->next = (a != NULL) ? a : b;

    return dummy.next;
}

static Node* mergesort_nodes(Node* head, int (*cmp)(int, int))
{
    if (!head || !head->next)
        return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = NULL;

    Node* left = mergesort_nodes(head, cmp);
    Node* right = mergesort_nodes(mid, cmp);

    return merge_nodes(left, right, cmp);
}

static bool is_sorted(Node* head, int (*cmp)(int, int))
{
    if (!head)
        return true;

    Node* current = head;
    while (current->next)
    {
        if (cmp(current->value, current->next->value) > 0)
            return false;
        current = current->next;
    }

    return true;
}

/* ================= Lifecycle ================= */

SL_Result sl_init(SinglyLinkedList* list)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    list->head = NULL;
    list->size = 0;

    return SL_OK;
}

SL_Result sl_destroy(SinglyLinkedList* list)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    Node* current = list->head;

    while (current != NULL)
    {
        free(current);
        current = current->next;
    }

    return SL_OK;
}

/* ================= Size ================= */

int sl_size(const SinglyLinkedList* list)
{
    if (list == NULL)
    {
        return -1;
    }

    return list->size;
}

bool sl_is_empty(const SinglyLinkedList* list)
{
    if (list == NULL)
    {
        return false;
    }

    return list->size == 0;
}

SL_Result sl_clear(SinglyLinkedList* list)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (sl_is_empty(list))
    {
        return SL_ERR_EMPTY;
    }

    Node* current = list->head;

    while (current != NULL)
    {
        free(current);
        current = current->next;
    }

    list->size = 0;
    list->head = NULL;

    return SL_OK;
}

/* ================= Front Access ================= */

SL_Result sl_front(const SinglyLinkedList* list, int* out)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (out == NULL)
    {
        return SL_ERR_INVALID_ARG;
    }

    if (sl_is_empty(list))
    {
        return SL_ERR_EMPTY;
    }
    *out = list->head->value;

    return SL_OK;
}

/* ================= Push & Pop ================= */

SL_Result sl_push_front(SinglyLinkedList* list, int value)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return SL_ERR_NO_MEMORY;
    }

    new_node->value = value;
    new_node->next = list->head;

    list->head = new_node;
    list->size++;

    return SL_OK;
}

SL_Result sl_push_back(SinglyLinkedList* list, int value)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return SL_ERR_NO_MEMORY;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        Node* current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return SL_OK;
}

SL_Result sl_pop_front(SinglyLinkedList* list, int* out)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (sl_is_empty(list))
    {
        return SL_ERR_EMPTY;
    }

    if (out == NULL)
    {
        return SL_ERR_INVALID_ARG;
    }

    Node* removed = list->head;
    *out = removed->value;
    list->head = removed->next;
    free(removed);
    list->size--;

    return SL_OK;
}

SL_Result sl_pop_back(SinglyLinkedList* list, int* out)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (sl_is_empty(list))
    {
        return SL_ERR_EMPTY;
    }

    if (out == NULL)
    {
        return SL_ERR_INVALID_ARG;
    }

    Node* current = list->head;

    if (current->next == NULL)
    {
        *out = current->value;
        free(current);
        list->head = NULL;
        list->size--;
        return SL_OK;
    }

    while (current->next->next != NULL)
    {
        current = current->next;
    }

    Node* removed = current->next;
    *out = removed->value;
    current->next = NULL;
    free(removed);
    list->size--;

    return SL_OK;
}

/* ================= Random-like Access ================= */

SL_Result sl_at(const SinglyLinkedList* list, size_t index, int* out)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (sl_is_empty(list))
    {
        return SL_ERR_EMPTY;
    }

    if (out == NULL)
    {
        return SL_ERR_INVALID_ARG;
    }

    if (index >= list->size)
    {
        return SL_ERR_OUT_OF_BOUNDS;
    }

    Node* current = list->head;
    size_t i = 0;

    while (i < index)
    {
        current = current->next;
        ++i;
    }

    *out = current->value;

    return SL_OK;
}

SL_Result sl_insert(SinglyLinkedList* list, size_t index, size_t count,
                    int value)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (count == 0)
    {
        return SL_OK;
    }

    if (index > list->size)
    {
        return SL_ERR_OUT_OF_BOUNDS;
    }

    if (index == list->size)
    {
        while (count--)
        {
            SL_Result r = sl_push_back(list, value);
            if (r != SL_OK)
                return r;
        }

        return SL_OK;
    }

    if (index == 0)
    {
        while (count--)
        {
            SL_Result r = sl_push_front(list, value);
            if (r != SL_OK)
                return r;
        }
        return SL_OK;
    }

    size_t i = 0;
    Node* current = list->head;

    while (i < index - 1)
    {
        current = current->next;
        ++i;
    }

    while (count--)
    {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL)
        {
            return SL_ERR_NO_MEMORY;
        }

        new_node->value = value;
        Node* tail = current->next;
        current->next = new_node;
        new_node->next = tail;

        current = new_node;
        list->size++;
    }

    return SL_OK;
}

SL_Result sl_erase(SinglyLinkedList* list, size_t index, int* out)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (sl_is_empty(list))
    {
        return SL_ERR_EMPTY;
    }

    if (out == NULL)
    {
        return SL_ERR_INVALID_ARG;
    }

    if (index >= list->size)
    {
        return SL_ERR_OUT_OF_BOUNDS;
    }

    if (index == 0)
    {
        sl_pop_front(list, out);
        return SL_OK;
    }

    if (index == list->size - 1)
    {
        sl_pop_back(list, out);
        return SL_OK;
    }

    size_t i = 0;
    Node* current = list->head;

    while (i++ < index - 1)
    {
        current = current->next;
    }

    Node* removed = current->next;
    *out = removed->value;
    current->next = removed->next;
    free(removed);
    list->size--;
    return SL_OK;
}

size_t sl_remove(SinglyLinkedList* list, int value, int (*cmp)(int a, int b),
                 int* out)
{
    if (!list || !out)
        return SL_ERR_NULL;

    int count = 0;

    while (list->head && ((cmp && cmp(list->head->value, value) == 0) ||
                          (!cmp && list->head->value == value)))
    {
        Node* tmp = list->head;
        list->head = tmp->next;
        free(tmp);
        list->size--;
        count++;
    }

    Node* current = list->head;
    while (current && current->next)
    {
        if ((cmp && cmp(current->next->value, value) == 0) ||
            (!cmp && current->next->value == value))
        {
            Node* tmp = current->next;
            current->next = tmp->next;
            free(tmp);
            list->size--;
            count++;
        }
        else
        {
            current = current->next;
        }
    }

    *out = count;
    return SL_OK;
}

/* ================= Algorithms ================= */

SL_Result sl_reverse(SinglyLinkedList* list)
{
    if (list == NULL || list->head == NULL)
    {
        return SL_OK;
    }

    Node* current = list->head;
    Node* prev = NULL;
    Node* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
    return SL_OK;
}

SL_Result sl_sort(SinglyLinkedList* list, int (*cmp)(int, int))
{
    if (list == NULL)
        return SL_ERR_NULL;

    if (cmp == NULL)
        return SL_ERR_INVALID_ARG;

    if (list->size < 2)
        return SL_OK;

    list->head = mergesort_nodes(list->head, cmp);

    return SL_OK;
}

SL_Result sl_merge(SinglyLinkedList* list, SinglyLinkedList* other,
                   int (*cmp)(int a, int b))
{
    if (list == NULL || other == NULL)
    {
        return SL_ERR_NULL;
    }

    if (cmp == NULL)
    {
        return SL_ERR_INVALID_ARG;
    }

    if (!is_sorted(list->head, cmp) || !is_sorted(other->head, cmp))
    {
        return SL_ERR_NOT_SORTED;
    }

    if (list->head == NULL)
    {
        list->head = other->head;
        list->size = other->size;
        other->head = NULL;
        other->size = 0;
        return SL_OK;
    }

    Node* dummy = (Node*)malloc(sizeof(Node));
    if (dummy == NULL)
    {
        return SL_ERR_NO_MEMORY;
    }

    Node* head1 = list->head;
    Node* head2 = other->head;
    dummy->next = NULL;
    Node* current = dummy;

    while (head1 && head2)
    {
        if (cmp(head1->value, head2->value) <= 0)
        {
            current->next = head1;
            head1 = head1->next;
        }
        else
        {
            current->next = head2;
            head2 = head2->next;
        }

        current = current->next;
    }

    current->next = (head1 != NULL) ? head1 : head2;
    list->size += other->size;
    list->head = dummy->next;

    other->head = NULL;
    other->size = 0;

    return SL_OK;
}

/* ================= Utilities ================= */

SL_Result sl_to_array(const SinglyLinkedList* list, int** out)
{
    if (list == NULL)
    {
        return SL_ERR_NULL;
    }

    if (list->size == 0)
    {
        *out = NULL;
        return SL_OK;
    }

    int* arr = (int*)malloc(list->size * sizeof(int));
    if (arr == NULL)
    {
        return SL_ERR_NO_MEMORY;
    }

    Node* current = list->head;
    int i = 0;

    while (current != NULL)
    {
        arr[i++] = current->value;
        current = current->next;
    }

    *out = arr;
    return SL_OK;
}