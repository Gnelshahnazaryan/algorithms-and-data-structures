#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

/* =========================
 *  Result Codes
 * ========================= */
typedef enum
{
    BST_OK = 0,
    BST_ERROR,
    BST_NOT_FOUND,
    BST_EMPTY
} BST_Result;

/* =========================
 *  Node Structure
 * ========================= */
typedef struct BST_Node
{
    int data;
    struct BST_Node* left;
    struct BST_Node* right;
} BST_Node;

/* =========================
 *  Tree Structure
 * ========================= */
typedef struct
{
    BST_Node* root;
    size_t size;
} BST;

/* =========================
 *  Core Functions
 * ========================= */

/* Create an empty BST */
BST* bst_create(void);

/* Destroy the BST and free all allocated memory */
void bst_destroy(BST** tree);

/* Insert a value into the BST */
BST_Result bst_insert(BST* tree, int value);

/* Remove a value from the BST */
BST_Result bst_remove(BST* tree, int value);

/* Search for a value in the BST */
bool bst_search(const BST* tree, int value);

/* Return the number of elements in the BST */
size_t bst_size(const BST* tree);

/* Check whether the BST is empty */
bool bst_is_empty(const BST* tree);

/* Find the minimum value in the BST */
BST_Result bst_find_min(const BST* tree, int* out_value);

/* Find the maximum value in the BST */
BST_Result bst_find_max(const BST* tree, int* out_value);

/* Return the height of the BST */
int bst_height(const BST* tree);

/* =========================
 *  Traversal Functions
 * ========================= */
/*
 * Perform inorder traversal and return a dynamically allocated array.
 * The function sets out_size to the number of elements.
 * Returns NULL if tree is empty or allocation fails.
 */
int* bst_inorder(const BST* tree, size_t* out_size);

/*
 * Perform preorder traversal and return a dynamically allocated array.
 */
int* bst_preorder(const BST* tree, size_t* out_size);

/*
 * Perform postorder traversal and return a dynamically allocated array.
 */
int* bst_postorder(const BST* tree, size_t* out_size);

/*
 * Perform level-order (BFS) traversal and return a dynamically allocated array.
 */
int* bst_level_order(const BST* tree, size_t* out_size);

/* =========================
 *  Advanced Operations
 * ========================= */

/*
 * Find the inorder predecessor of a given value.
 * The predecessor is the largest value smaller than the given value.
 */
BST_Result bst_find_predecessor(const BST* tree, int value, int* out_value);

/*
 * Find the inorder successor of a given value.
 * The successor is the smallest value greater than the given value.
 */
BST_Result bst_find_successor(const BST* tree, int value, int* out_value);

#endif /* BST_H */