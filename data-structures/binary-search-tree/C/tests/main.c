#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/BST.h"

void print_array(const int* arr, size_t size, const char* name)
{
    printf("%s: ", name);
    for (size_t i = 0; i < size; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    /* ===== CREATE ===== */
    BST* tree = bst_create();
    if (!tree)
    {
        printf("Failed to create BST\n");
        return EXIT_FAILURE;
    }

    printf("BST created successfully\n");

    /* ===== INSERT ===== */
    int values[] = {20, 10, 30, 5, 15, 25, 35};
    size_t n = sizeof(values) / sizeof(values[0]);
    for (size_t i = 0; i < n; ++i)
    {
        assert(bst_insert(tree, values[i]) == BST_OK);
    }

    printf("Inserted values into BST\n");
    assert(bst_size(tree) == n);
    printf("BST size: %zu\n", bst_size(tree));
    printf("BST height: %d\n", bst_height(tree));

    /* ===== SEARCH ===== */
    assert(bst_search(tree, 20) == true);
    assert(bst_search(tree, 99) == false);
    printf("Search tests passed\n");

    /* ===== TRAVERSALS ===== */
    size_t out_size;
    int* arr;

    arr = bst_inorder(tree, &out_size);
    print_array(arr, out_size, "Inorder");
    free(arr);

    arr = bst_preorder(tree, &out_size);
    print_array(arr, out_size, "Preorder");
    free(arr);

    arr = bst_postorder(tree, &out_size);
    print_array(arr, out_size, "Postorder");
    free(arr);

    arr = bst_level_order(tree, &out_size);
    print_array(arr, out_size, "Level-order");
    free(arr);

    /* ===== FIND MIN / MAX ===== */
    int value;
    assert(bst_find_min(tree, &value) == BST_OK && value == 5);
    assert(bst_find_max(tree, &value) == BST_OK && value == 35);
    printf("Min / Max tests passed\n");

    /* ===== FIND PREDECESSOR ===== */
    assert(bst_find_predecessor(tree, 20, &value) == BST_OK && value == 15);
    assert(bst_find_predecessor(tree, 5, &value) == BST_NOT_FOUND);
    printf("Predecessor tests passed\n");

    /* ===== FIND SUCCESSOR ===== */
    assert(bst_find_successor(tree, 20, &value) == BST_OK && value == 25);
    assert(bst_find_successor(tree, 35, &value) == BST_NOT_FOUND);
    printf("Successor tests passed\n");

    /* ===== REMOVE ===== */
    assert(bst_remove(tree, 5) == BST_OK);   // leaf
    assert(bst_remove(tree, 30) == BST_OK);  // one-child
    assert(bst_remove(tree, 20) == BST_OK);  // two-children
    assert(bst_remove(tree, 99) == BST_NOT_FOUND); // non-existing
    printf("Remove tests passed\n");
    printf("BST size after removals: %zu\n", bst_size(tree));

    /* ===== DESTROY ===== */
    bst_destroy(&tree);
    assert(tree == NULL);
    printf("BST destroyed successfully\n");

    printf("\nAll BST tests passed successfully!\n");
    return 0;
}