#include "../include/hash_table.h"
#include <assert.h>
#include <stdio.h>

void test_create_and_destroy()
{
    HashTable* ht = ht_create(10);
    assert(ht != NULL);
    assert(ht_size(ht) == 0);

    ht_destroy(ht);
    printf("test_create_and_destroy passed\n");
}

void test_put_and_get()
{
    HashTable* ht = ht_create(10);

    assert(ht_put(ht, "apple", 1) == HT_OK);
    assert(ht_put(ht, "banana", 2) == HT_OK);

    int value;

    assert(ht_get(ht, "apple", &value) == HT_OK);
    assert(value == 1);

    assert(ht_get(ht, "banana", &value) == HT_OK);
    assert(value == 2);

    printf("test_put_and_get passed\n");
    ht_destroy(ht);
}

void test_update_value()
{
    HashTable* ht = ht_create(10);

    ht_put(ht, "key", 10);
    ht_put(ht, "key", 20);

    int value;
    assert(ht_get(ht, "key", &value) == HT_OK);
    assert(value == 20);

    printf("test_update_value passed\n");
    ht_destroy(ht);
}

void test_contains()
{
    HashTable* ht = ht_create(10);

    ht_put(ht, "test", 100);

    assert(ht_contains(ht, "test") == true);
    assert(ht_contains(ht, "not_exist") == false);

    printf("test_contains passed\n");
    ht_destroy(ht);
}

void test_remove()
{
    HashTable* ht = ht_create(10);

    ht_put(ht, "remove_me", 123);

    assert(ht_contains(ht, "remove_me") == true);

    assert(ht_remove(ht, "remove_me") == HT_OK);
    assert(ht_contains(ht, "remove_me") == false);

    printf("test_remove passed\n");
    ht_destroy(ht);
}

void test_collision()
{
    HashTable* ht = ht_create(2);

    ht_put(ht, "a", 1);
    ht_put(ht, "b", 2);
    ht_put(ht, "c", 3);

    int value;

    assert(ht_get(ht, "a", &value) == HT_OK);
    assert(ht_get(ht, "b", &value) == HT_OK);
    assert(ht_get(ht, "c", &value) == HT_OK);

    printf("test_collision passed\n");
    ht_destroy(ht);
}

void test_resize()
{
    HashTable* ht = ht_create(2);

    ht_put(ht, "a", 1);
    ht_put(ht, "b", 2);
    ht_put(ht, "c", 3);

    int value;

    assert(ht_get(ht, "a", &value) == HT_OK);
    assert(ht_get(ht, "b", &value) == HT_OK);
    assert(ht_get(ht, "c", &value) == HT_OK);

    printf("test_resize passed\n");
    ht_destroy(ht);
}

void test_error_cases()
{
    HashTable* ht = ht_create(5);

    int value;

    assert(ht_get(ht, "missing", &value) == HT_ERR_KEY_NOT_FOUND);

    assert(ht_put(NULL, "key", 1) == HT_ERR_NULL_POINTER);

    printf("test_error_cases passed\n");
    ht_destroy(ht);
}

int main()
{
    test_create_and_destroy();
    test_put_and_get();
    test_update_value();
    test_contains();
    test_remove();
    test_collision();
    test_resize();
    test_error_cases();

    printf("All tests passed \n");
    return 0;
}