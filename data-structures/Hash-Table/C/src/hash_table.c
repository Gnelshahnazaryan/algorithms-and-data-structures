#include "../include/hash_table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================
   Static Helpers
   ======================= */

bool is_prime(size_t num)
{
    for (size_t i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

size_t get_next_prime(size_t num)
{
    while (!is_prime(num))
    {
        ++num;
    }

    return num;
}

/* =======================
   Core Operations
   ======================= */

/* Create & Destroy */
HashTable* ht_create(size_t capacity)
{
    if (!is_prime(capacity))
    {
        capacity = get_next_prime(capacity);
    }

    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht)
    {
        free(ht);
        return NULL;
    }

    ht->buckets = (HashNode**)malloc(sizeof(HashNode*) * capacity);
    if (!ht->buckets)
    {
        return NULL;
    }

    for (size_t i = 0; i < capacity; ++i)
    {
        ht->buckets[i] = NULL;
    }

    ht->capacity = capacity;
    ht->size = 0;
    ht->max_load_factor = 0.75;

    return ht;
}

void ht_destroy(HashTable* ht)
{
    if (!ht)
    {
        return;
    }

    for (size_t i = 0; i < ht->capacity; i++)
    {
        if (ht->buckets[i] != NULL)
        {
            HashNode* current = ht->buckets[i];

            while (current)
            {
                HashNode* tmp = current;
                current = current->next;

                free(tmp->key);
                free(tmp);
            }
        }
    }

    free(ht->buckets);
    free(ht);
}

/* Insert or Update */
HT_ErrorCode ht_put(HashTable* ht, const char* key, int value)
{
    if (!ht || !key)
    {
        return HT_ERR_NULL_POINTER;
    }

    if ((double)(ht->size + 1) / ht->capacity > ht->max_load_factor)
    {
        HT_ErrorCode err = ht_resize(ht, ht->capacity * 2);
        if (err != HT_OK)
        {
            return err;
        }
    }

    size_t index = ht_hash(key, ht->capacity);
    HashNode* current = ht->buckets[index];

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value;
            return HT_OK;
        }
        current = current->next;
    }

    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode)
    {
        return HT_ERR_OUT_OF_MEMORY;
    }
    newNode->key = strdup(key);
    if (!newNode->key)
    {
        free(newNode);
        return HT_ERR_OUT_OF_MEMORY;
    }
    newNode->value = value;

    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
    ++ht->size;

    return HT_OK;
}

/* Get value by key */
HT_ErrorCode ht_get(HashTable* ht, const char* key, int* out_value)
{
    if (!ht || !key || !out_value)
    {
        return HT_ERR_NULL_POINTER;
    }

    size_t index = ht_hash(key, ht->capacity);
    HashNode* current = ht->buckets[index];

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            *out_value = current->value;
            return HT_OK;
        }
        current = current->next;
    }
    return HT_ERR_KEY_NOT_FOUND;
}

/* Remove key */
HT_ErrorCode ht_remove(HashTable* ht, const char* key)
{
    if (!ht || !key)
    {
        return HT_ERR_NULL_POINTER;
    }

    size_t index = ht_hash(key, ht->capacity);
    HashNode* current = ht->buckets[index];
    HashNode* prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (!prev)
            {
                ht->buckets[index] = current->next;
            }
            else
            {
                prev->next = current->next;
                break;
            }
            free(current->key);
            free(current);
            --ht->size;
            return HT_OK;
        }
        prev = current;
        current = current->next;
    }

    return HT_ERR_KEY_NOT_FOUND;
}

/* Check existence */
bool ht_contains(HashTable* ht, const char* key)
{
    if (!ht || !key)
    {
        return false;
    }

    size_t index = ht_hash(key, ht->capacity);
    HashNode* current = ht->buckets[index];

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

/* Size */
size_t ht_size(HashTable* ht)
{
    if (!ht)
    {
        return 0;
    }

    return ht->size;
}

/* Hash function */
size_t ht_hash(const char* key, size_t capacity)
{
    if (!key || capacity == 0)
    {
        return 0;
    }

    unsigned long hash = 0;
    const unsigned long p = 31;

    while (*key)
    {
        hash = hash * p + (unsigned char)(*key);
        key++;
    }

    return hash % capacity;
}

/*Check Load Factor*/
double ht_load_factor(HashTable* ht)
{
    if (!ht)
    {
        return 0.0;
    }

    return (double)ht->size / ht->capacity;
}

/*Print Hash Table*/
void ht_print(HashTable* ht)
{
    if (!ht)
    {
        printf("HashTable is NULL\n");
        return;
    }

    for (size_t i = 0; i < ht->capacity; i++)
    {
        HashNode* node = ht->buckets[i];

        printf("Bucket [%zu]: ", i);

        while (node)
        {
            printf("(%s: %d) -> ", node->key, node->value);
            node = node->next;
        }

        printf("null\n");
    }
}

/* =======================
   Resize / Rehash
   ======================= */

/* Resize table to new capacity */
HT_ErrorCode ht_resize(HashTable* ht, size_t new_capacity)
{
    if (!ht)
    {
        return HT_ERR_NULL_POINTER;
    }

    new_capacity = get_next_prime(new_capacity);

    HashNode** new_buckets =
        (HashNode**)malloc(sizeof(HashNode*) * new_capacity);
    if (!new_buckets)
    {
        return HT_ERR_OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < new_capacity; ++i)
    {
        new_buckets[i] = NULL;
    }

    for (size_t i = 0; i < ht->capacity; ++i)
    {
        HashNode* current = ht->buckets[i];

        while (current)
        {
            HashNode* next = current->next;

            size_t new_index = ht_hash(current->key, new_capacity);

            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;

            current = next;
        }
    }

    free(ht->buckets);

    ht->buckets = new_buckets;
    ht->capacity = new_capacity;

    return HT_OK;
}