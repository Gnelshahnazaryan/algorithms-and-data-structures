#include "../include/avl.h"
#include <stdio.h>
#include <stdlib.h>

void print_array(const char* name, int* arr, size_t size)
{
    printf("%s: ", name);

    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
    free(arr);
}

int main(void)
{
    AVL* tree = avl_create();

    if (!tree)
    {
        printf("Failed to create AVL tree\n");
        return 1;
    }

    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25};
    size_t n = sizeof(values) / sizeof(values[0]);

    printf("=== INSERT TEST ===\n");

    for (size_t i = 0; i < n; i++)
    {
        AVL_Result r = avl_insert(tree, values[i]);

        if (r == AVL_OK)
            printf("Inserted %d\n", values[i]);
        else
            printf("Insert failed: %d\n", values[i]);
    }

    printf("\nTree size: %zu\n", avl_size(tree));
    printf("Tree height: %zu\n", avl_height(tree));

    printf("\n=== DUPLICATE TEST ===\n");

    AVL_Result dup = avl_insert(tree, 50);
    if (dup == AVL_ERR_DUPLICATE)
        printf("Duplicate correctly rejected\n");

    printf("\n=== CONTAINS TEST ===\n");

    printf("Contains 40: %s\n", avl_contains(tree, 40) ? "YES" : "NO");
    printf("Contains 99: %s\n", avl_contains(tree, 99) ? "YES" : "NO");

    printf("\n=== TRAVERSALS ===\n");

    size_t size;

    int* inorder = avl_inorder(tree, &size);
    print_array("Inorder", inorder, size);

    int* preorder = avl_preorder(tree, &size);
    print_array("Preorder", preorder, size);

    int* postorder = avl_postorder(tree, &size);
    print_array("Postorder", postorder, size);

    int* level = avl_level_order(tree, &size);
    print_array("Level Order", level, size);

    printf("\n=== DELETE TEST ===\n");

    avl_delete(tree, 70);
    avl_delete(tree, 30);

    int* after = avl_inorder(tree, &size);
    print_array("Inorder after delete", after, size);

    printf("\nTree size: %zu\n", avl_size(tree));
    printf("Tree height: %zu\n", avl_height(tree));

    avl_destroy(tree);

    return 0;
}