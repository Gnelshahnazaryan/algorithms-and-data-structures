#include "../include/BST.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* =======================
 *  Static Helpers
 * ======================== */

static void bst_destroy_nodes(BST_Node* node)
{
    if (!node)
    {
        return;
    }

    bst_destroy_nodes(node->left);
    bst_destroy_nodes(node->right);
    free(node);
}

static BST_Node* bst_insert_node(BST_Node* node, int value, bool* flag)
{
    if (!node)
    {
        BST_Node* new_node = (BST_Node*)malloc(sizeof(BST_Node));
        if (!new_node)
        {
            *flag = false;
            return NULL;
        }
        new_node->data = value;
        new_node->left = NULL;
        new_node->right = NULL;

        *flag = true;
        return new_node;
    }

    if (value == node->data)
    {
        *flag = false;
        return node;
    }

    if (value < node->data)
    {
        node->left = bst_insert_node(node->left, value, flag);
    }
    else
    {
        node->right = bst_insert_node(node->right, value, flag);
    }

    return node;
}

static BST_Node* remove_node(BST_Node* node, int value, bool* flag)
{
    if (!node)
    {
        return node;
    }

    if (value < node->data)
    {
        node->left = remove_node(node->left, value, flag);
    }
    else if (value > node->data)
    {
        node->right = remove_node(node->right, value, flag);
    }
    else
    {
        *flag = true;

        if (!node->left || !node->right)
        {
            BST_Node* child = node->left ? node->left : node->right;
            free(node);
            return child;
        }

        BST_Node* successor = node->right;

        while (successor->left)
        {
            successor = successor->left;
        }

        node->data = successor->data;
        node->right = remove_node(node->right, successor->data, flag);
    }
    return node;
}

static bool bst_search_node(BST_Node* node, int value)
{
    if (!node)
        return false;

    if (node->data == value)
    {
        return true;
    }

    return bst_search_node(value < node->data ? node->left : node->right,
                           value);
}

static int find_min_node(BST_Node* node)
{
    if (!node->left)
    {
        return node->data;
    }

    return find_min_node(node->left);
}

static int find_max_node(BST_Node* node)
{
    if (!node->right)
    {
        return node->data;
    }

    return find_max_node(node->right);
}

static int _bst_height(BST_Node* node)
{
    if (!node)
    {
        return 0;
    }

    int left = _bst_height(node->left);
    int right = _bst_height(node->right);

    return left > right ? left + 1 : right + 1;
}

static void preorder_fill(BST_Node* node, int* arr, size_t* index)
{
    if (!node)
    {
        return;
    }

    arr[*index] = node->data;
    (*index)++;

    preorder_fill(node->left, arr, index);
    preorder_fill(node->right, arr, index);
}

static void inorder_fill(BST_Node* node, int* arr, size_t* index)
{
    if (!node)
    {
        return;
    }

    inorder_fill(node->left, arr, index);

    arr[*index] = node->data;
    (*index)++;

    inorder_fill(node->right, arr, index);
}

static void postorder_fill(BST_Node* node, int* arr, size_t* index)
{
    if (!node)
    {
        return;
    }

    postorder_fill(node->left, arr, index);
    postorder_fill(node->right, arr, index);
    arr[*index] = node->data;
    (*index)++;
}

/* =========================
 *  Core Functions
 * ========================= */

BST* bst_create(void)
{
    BST* tree = (BST*)malloc(sizeof(BST));
    if (!tree)
    {
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

void bst_destroy(BST** tree)
{
    if (!tree || !(*tree))
    {
        return;
    }

    bst_destroy_nodes((*tree)->root);
    free(*tree);
    *tree = NULL;
}

size_t bst_size(const BST* tree)
{
    if (!tree)
    {
        return 0;
    }

    return tree->size;
}

BST_Result bst_insert(BST* tree, int value)
{
    if (!tree)
    {
        return BST_ERROR;
    }

    bool flag = false;
    tree->root = bst_insert_node(tree->root, value, &flag);

    if (flag)
    {
        ++tree->size;
        return BST_OK;
    }

    return BST_ERROR;
}

BST_Result bst_remove(BST* tree, int value)
{
    if (!tree)
    {
        return BST_ERROR;
    }

    if (bst_is_empty(tree))
    {
        return BST_EMPTY;
    }

    if (!bst_search(tree, value))
    {
        return BST_NOT_FOUND;
    }

    bool flag = false;
    tree->root = remove_node(tree->root, value, &flag);

    if (flag)
    {
        --tree->size;
        return BST_OK;
    }

    return BST_ERROR;
}

bool bst_search(const BST* tree, int value)
{
    if (!tree || !tree->root)
    {
        return false;
    }

    if (bst_is_empty(tree))
    {
        return false;
    }

    return bst_search_node(tree->root, value);
}

bool bst_is_empty(const BST* tree)
{
    if (!tree)
    {
        return true;
    }

    return tree->size == 0;
}

BST_Result bst_find_min(const BST* tree, int* out_value)
{
    if (bst_is_empty(tree))
    {
        return BST_EMPTY;
    }

    *out_value = find_min_node(tree->root);
    return BST_OK;
}

BST_Result bst_find_max(const BST* tree, int* out_value)
{
    if (bst_is_empty(tree))
    {
        return BST_EMPTY;
    }

    *out_value = find_max_node(tree->root);
    return BST_OK;
}

int bst_height(const BST* tree)
{
    if (!tree || bst_is_empty(tree))
    {
        return 0;
    }

    return _bst_height(tree->root);
}

/* =========================
 *  Traversal Functions
 * ========================= */

int* bst_inorder(const BST* tree, size_t* out_size)
{
    if (!tree || !tree->root)
    {
        *out_size = 0;
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

    *out_size = tree->size;
    return arr;
}

int* bst_preorder(const BST* tree, size_t* out_size)
{
    if (!tree || !tree->root)
    {
        *out_size = 0;
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
    return arr;
}

int* bst_postorder(const BST* tree, size_t* out_size)
{
    if (!tree || !tree->root)
    {
        *out_size = 0;
        return NULL;
    }

    int* arr = (int*)malloc(tree->size * sizeof(int));
    if (!arr)
    {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    postorder_fill(tree->root, arr, &index);
    return arr;
}

int* bst_level_order(const BST* tree, size_t* out_size)
{
    if (!tree || tree->size == 0)
    {
        if (out_size)
            *out_size = 0;
        return NULL;
    }

    int* arr = (int*)malloc(sizeof(int) * tree->size);
    if (!arr)
        return NULL;

    BST_Node** queue = (BST_Node**)malloc(sizeof(BST_Node*) * tree->size);
    if (!queue)
    {
        free(arr);
        return NULL;
    }

    size_t front = 0;
    size_t rear = 0;
    size_t index = 0;

    queue[rear++] = tree->root;

    while (front < rear)
    {
        BST_Node* current = queue[front++];

        arr[index++] = current->data;

        if (current->left)
            queue[rear++] = current->left;

        if (current->right)
            queue[rear++] = current->right;
    }

    free(queue);

    if (out_size)
    {
        *out_size = index;
    }

    return arr;
}

BST_Result bst_find_predecessor(const BST* tree, int value, int* out_value)
{
    if (!tree || !tree->root)
    {
        return BST_ERROR;
    }

    BST_Node* current = tree->root;

    while (current && current->data != value)
    {
        current = current->data > value ? current->left : current->right;
    }

    if (!current)
    {
        return BST_NOT_FOUND;
    }

    if (current->left)
    {
        current = current->left;
        while (current->right)
        {
            current = current->right;
        }
        *out_value = current->data;
        return BST_OK;
    }

    BST_Node* ancestor = NULL;
    current = tree->root;
    while (current->data != value)
    {
        if (value > current->data)
        {
            ancestor = current;
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }

    if (!ancestor)
    {
        return BST_NOT_FOUND;
    }
    *out_value = ancestor->data;
    return BST_OK;
}

BST_Result bst_find_successor(const BST* tree, int value, int* out_value)
{

    if (!tree || !tree->root)
    {
        return BST_ERROR;
    }

    BST_Node* current = tree->root;

    while (current && current->data != value)
    {
        current = current->data > value ? current->left : current->right;
    }

    if (!current)
    {
        return BST_NOT_FOUND;
    }

    if (current->right)
    {
        current = current->right;
        while (current->left)
        {
            current = current->left;
        }
        *out_value = current->data;
        return BST_OK;
    }

    current = tree->root;
    BST_Node* ancestor = NULL;
    while (current->data != value)
    {
        if (value < current->data)
        {
            ancestor = current;
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (!ancestor)
    {
        return BST_NOT_FOUND;
    }
    *out_value = ancestor->data;
    return BST_OK;
}