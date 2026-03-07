#include "../include/avl.h"
#include <stdbool.h>
#include <stdlib.h>

/* ================================
 *  PRIVATE HELPER DECLARATIONS
   ================================ */

static int height(AVLNode* node) { return node ? node->height : 0; }

static int balance_factor(AVLNode* node)
{
    if (!node)
    {
        return 0;
    }

    return height(node->left) - height(node->right);
}

static void updateHeight(AVLNode* node)
{
    if (!node)
    {
        return;
    }

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    node->height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

static AVLNode* rotate_left(AVLNode* node)
{
    AVLNode* y = node->right;
    node->right = y->left;
    y->left = node;

    updateHeight(node);
    updateHeight(y);
    return y;
}

static AVLNode* rotate_right(AVLNode* node)
{
    AVLNode* y = node->left;
    node->left = y->right;
    y->right = node;

    updateHeight(node);
    updateHeight(y);
    return y;
}

static void destroy_nodes(AVLNode* node)
{
    if (!node)
    {
        return;
    }

    destroy_nodes(node->left);
    destroy_nodes(node->right);
    free(node);
}

static AVLNode* avl_insert_node(AVLNode* node, int value, bool* flag)
{
    if (!node)
    {
        *flag = true;
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        if (!newNode)
        {
            *flag = false;
            return NULL;
        }

        newNode->left = NULL;
        newNode->right = NULL;
        newNode->value = value;
        newNode->height = 1;
        return newNode;
    }

    if (node->value == value)
    {
        *flag = false;
        return node;
    }
    else if (value < node->value)
    {
        node->left = avl_insert_node(node->left, value, flag);
    }
    else
    {
        node->right = avl_insert_node(node->right, value, flag);
    }

    updateHeight(node);
    int bf = balance_factor(node);

    if (bf > 1 && value < node->left->value)
    {
        return rotate_right(node); // LL Case;
    }

    if (bf > 1 && value > node->left->value)
    {
        node->left = rotate_left(node->left); // LR Case;
        return rotate_right(node);
    }

    if (bf < -1 && value > node->right->value)
    {
        return rotate_left(node);
    }

    if (bf < -1 && value < node->right->value)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

static AVLNode* avl_delete_node(AVLNode* node, int value, bool* flag)
{
    if (!node)
        return node;

    if (value < node->value)
    {
        node->left = avl_delete_node(node->left, value, flag);
    }
    else if (value > node->value)
    {
        node->right = avl_delete_node(node->right, value, flag);
    }
    else
    {
        *flag = true;

        if (!node->left || !node->right)
        {
            AVLNode* child = node->left ? node->left : node->right;
            return child;
        }

        AVLNode* successor = node->right;

        while (successor->left)
        {
            successor = successor->left;
        }

        node->value = successor->value;
        node->right = avl_delete_node(node->right, successor->value, flag);
    }

    updateHeight(node);
    int bf = balance_factor(node);

    if (bf > 1 && balance_factor(node->left) >= 0)
    {
        return rotate_right(node); // LL Case;
    }

    if (bf > 1 && balance_factor(node->left) < 0)
    {
        node->left = rotate_left(node->left); // LR Case;
        return rotate_right(node->right);
    }

    if (bf < -1 && balance_factor(node->right) <= 0)
    {
        return rotate_left(node->left);
    }

    if (bf < -1 && balance_factor(node->right) > 0)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

static bool avl_contains_node(AVLNode* node, int value)
{
    if (!node)
    {
        return false;
    }
    if (node->value == value)
    {
        return true;
    }

    return avl_contains_node(node->value > value ? node->left : node->right,
                             value);
}

static void preorder_fill(AVLNode* node, int* arr, size_t* index)
{
    if (!node)
    {
        return;
    }

    arr[(*index)++] = node->value;
    preorder_fill(node->left, arr, index);
    preorder_fill(node->right, arr, index);
}

static void inorder_fill(AVLNode* node, int* arr, size_t* index)
{
    if (!node)
    {
        return;
    }

    inorder_fill(node->left, arr, index);
    arr[(*index)++] = node->value;
    inorder_fill(node->right, arr, index);
}

static void postorder_fill(AVLNode* node, int* arr, size_t* index)
{
    if (!node)
    {
        return;
    }

    postorder_fill(node->left, arr, index);
    postorder_fill(node->right, arr, index);
    arr[(*index)++] = node->value;
}

/* =========================
 *  Creation / Destruction
 * ========================= */

AVL* avl_create(void)
{
    AVL* avl = (AVL*)malloc(sizeof(AVL));
    if (!avl)
    {
        return NULL;
    }

    avl->root = NULL;
    avl->size = 0;
    return avl;
}

void avl_destroy(AVL* tree)
{
    if (!tree)
    {
        return;
    }

    destroy_nodes(tree->root);
}

AVL_Result avl_insert(AVL* tree, int value)
{
    if (!tree)
    {
        return AVL_ERR_NULL;
    }

    bool flag = false;
    tree->root = avl_insert_node(tree->root, value, &flag);

    if (flag)
    {
        ++tree->size;
        return AVL_OK;
    }

    return AVL_ERR_DUPLICATE;
}

AVL_Result avl_delete(AVL* tree, int value)
{
    if (!tree)
    {
        return AVL_ERR_NULL;
    }

    if (avl_is_empty(tree))
    {
        return AVL_ERR_NOT_FOUND;
    }

    bool flag = false;
    tree->root = avl_delete_node(tree->root, value, &flag);

    if (flag)
    {
        --tree->size;
        return AVL_OK;
    }

    return AVL_ERR;
}

bool avl_contains(const AVL* tree, int value)
{
    if (!tree || !tree->root)
    {
        return false;
    }

    if (avl_is_empty(tree))
    {
        return false;
    }
    return avl_contains_node(tree->root, value);
}

/* =========================
 *  Info Functions
 * ========================= */

size_t avl_size(const AVL* tree)
{
    if (!tree)
    {
        return 0;
    }

    return tree->size;
}

size_t avl_height(const AVL* tree)
{
    if (!tree)
    {
        return 0;
    }

    return height(tree->root);
}

bool avl_is_empty(const AVL* tree)
{
    if (!tree)
    {
        return true;
    }

    return tree->size == 0;
}

/* =========================
 *  Traversals
 * ========================= */

int* avl_preorder(const AVL* tree, size_t* out_size)
{
    if (!tree)
    {
        if (out_size)
        {
            *out_size = 0;
        }
        return NULL;
    }

    int* arr = (int*)malloc(tree->size * sizeof(int));
    if (!arr)
    {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    preorder_fill(tree->root, arr, &index);
    if (out_size)
    {
        *out_size = index;
    }
    return arr;
}

int* avl_inorder(const AVL* tree, size_t* out_size)
{
    if (!tree)
    {
        if (out_size)
        {
            *out_size = 0;
        }
        return NULL;
    }

    int* arr = (int*)malloc(tree->size * sizeof(int));
    if (!arr)
    {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    inorder_fill(tree->root, arr, &index);
    if (out_size)
    {
        *out_size = index;
    }
    return arr;
}

int* avl_postorder(const AVL* tree, size_t* out_size)
{
    if (!tree)
    {
        if (out_size)
        {
            *out_size = 0;
        }
        return NULL;
    }

    int* arr = (int*)malloc(tree->size * sizeof(int));
    if (!arr)
    {
        if (out_size)
        {
            *out_size = 0;
        }
        return NULL;
    }

    size_t index = 0;
    postorder_fill(tree->root, arr, &index);

    if (out_size)
    {
        *out_size = index;
    }
    return arr;
}

int* avl_level_order(const AVL* tree, size_t* out_size)
{
    if (!tree)
    {
        if (out_size)
        {
            *out_size = 0;
        }
        return NULL;
    }

    int* arr = (int*)malloc(tree->size * sizeof(int));
    if (!arr)
    {
        if (out_size)
        {
            *out_size = 0;
        }
        return NULL;
    }

    AVLNode** queue = (AVLNode**)malloc(tree->size * sizeof(AVLNode*));
    if (!queue)
    {
        free(arr);
        if (out_size)
        {
            *out_size = 0;
        }
        return NULL;
    }

    size_t front = 0;
    size_t rear = 0;
    size_t index = 0;

    queue[rear++] = tree->root;

    while (front < rear)
    {
        AVLNode* node = queue[front++];
        arr[index++] = node->value;

        if (node->left)
        {
            queue[rear++] = node->left;
        }

        if (node->right)
        {
            queue[rear++] = node->right;
        }
    }

    free(queue);

    if (out_size)
    {
        *out_size = index;
    }

    return arr;
}