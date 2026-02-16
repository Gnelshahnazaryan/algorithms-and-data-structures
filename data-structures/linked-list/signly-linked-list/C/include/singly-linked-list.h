#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

/* ================= Error codes ================= */

typedef enum
{
    SL_OK = 0, // operation successful

    SL_ERR_NULL,          // passed NULL pointer
    SL_ERR_EMPTY,         // list is empty
    SL_ERR_NO_MEMORY,     // malloc / allocation failed
    SL_ERR_OUT_OF_BOUNDS, // invalid index
    SL_ERR_NOT_SORTED,    // list is not sorted (for merge)
    SL_ERR_INVALID_ARG    // invalid argument (e.g. cmp == NULL)

} SL_Result;

/* ================= Node Struct ================= */
typedef struct Node
{
    int value;         // value of node
    struct Node* next; // pointer to next node
} Node;

/* ================= Singly Linked List Struct ================= */
typedef struct
{
    Node* head;  // pointer to first node
    size_t size; // number of nodes
} SinglyLinkedList;

/* ================= Lifecycle ================= */
SL_Result sl_init(SinglyLinkedList* list);    // initialize empty list
SL_Result sl_destroy(SinglyLinkedList* list); // free all nodes

/* ================= Size ================= */
int sl_size(const SinglyLinkedList* list);   // return number of nodes
bool sl_is_empty(const SinglyLinkedList* list); // check if list is empty
SL_Result sl_clear(SinglyLinkedList* list);     // remove all nodes

/* ================= Front Access ================= */
SL_Result sl_front(const SinglyLinkedList* list,
                   int* out); // get first node value

/* ================= Push & Pop ================= */
SL_Result sl_push_front(SinglyLinkedList* list, int value); // insert at head
SL_Result sl_push_back(SinglyLinkedList* list, int value);  // insert at tail
SL_Result sl_pop_front(SinglyLinkedList* list, int* out);   // remove head
SL_Result sl_pop_back(SinglyLinkedList* list, int* out);    // remove tail

/* ================= Random-like Access ================= */
SL_Result sl_at(const SinglyLinkedList* list, size_t index,
                int* out); // get value at index
SL_Result sl_insert(SinglyLinkedList* list, size_t index,
                    size_t count, int value); // insert at index
SL_Result sl_erase(SinglyLinkedList* list, size_t index,
                   int* out); // remove node at index
size_t sl_remove(SinglyLinkedList* list,
                 int value, int (*cmp)(int a, int b), int* out); // remove all nodes with value

/* ================= Algorithms ================= */
SL_Result sl_reverse(SinglyLinkedList* list); // reverse nodes in place
SL_Result sl_sort(SinglyLinkedList* list,
                  int (*cmp)(int a, int b)); // sort nodes
SL_Result sl_merge(SinglyLinkedList* list, SinglyLinkedList* other,
                   int (*cmp)(int a, int b)); // merge two sorted lists

/* ================= Utilities ================= */
SL_Result sl_to_array(
    const SinglyLinkedList* list, int** out); // return array copy of node values

#endif /* SINGLY_LINKED_LIST_H */