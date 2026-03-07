#ifndef AVL_H
#define AVL_H

#include <stdbool.h> /* bool */
#include <stddef.h>  /* size_t */

/* =========================
 *  Result Codes
 * ========================= */

typedef enum
{
    AVL_OK = 0,
    AVL_ERR,
    AVL_ERR_NULL,
    AVL_ERR_MEMORY,
    AVL_ERR_NOT_FOUND,
    AVL_ERR_DUPLICATE
} AVL_Result;

/* =========================
 *  Node Structure
 * ========================= */

typedef struct AVLNode
{
    int value;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

/* =========================
 *  Tree Structure
 * ========================= */

typedef struct
{
    AVLNode* root;
    size_t size;
} AVL;

/* =========================
 *  Creation / Destruction
 * ========================= */

AVL* avl_create(void);

void avl_destroy(AVL* tree);

/* =========================
 *  Core Operations
 * ========================= */

AVL_Result avl_insert(AVL* tree, int value);

AVL_Result avl_delete(AVL* tree, int value);

bool avl_contains(const AVL* tree, int value);

/* =========================
 *  Info Functions
 * ========================= */

size_t avl_size(const AVL* tree);

size_t avl_height(const AVL* tree);

bool avl_is_empty(const AVL* tree);

/* =========================
 *  Traversals
 * ========================= */

int* avl_preorder(const AVL* tree, size_t* out_size);

int* avl_inorder(const AVL* tree, size_t* out_size);

int* avl_postorder(const AVL* tree, size_t* out_size);

int* avl_level_order(const AVL* tree, size_t* out_size);

#endif /* AVL_H */