#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

/* =======================
   Error Codes
   ======================= */
typedef enum
{
    HT_OK = 0,
    HT_ERR_NULL_POINTER,
    HT_ERR_OUT_OF_MEMORY,
    HT_ERR_KEY_NOT_FOUND,
    HT_ERR_INVALID_ARGUMENT
} HT_ErrorCode;

/* =======================
   Node for separate chaining
   ======================= */
typedef struct HashNode
{
    char* key;
    int value;
    struct HashNode* next;
} HashNode;

/* =======================
   Hash Table structure
   ======================= */
typedef struct HashTable
{
    HashNode** buckets;
    double max_load_factor;
    size_t capacity;
    size_t size;
} HashTable;

/* =======================
   Core Operations
   ======================= */

/* Create & Destroy */
HashTable* ht_create(size_t capacity);
void ht_destroy(HashTable* ht);

/* Insert or Update */
HT_ErrorCode ht_put(HashTable* ht, const char* key, int value);

/* Get value by key */
HT_ErrorCode ht_get(HashTable* ht, const char* key, int* out_value);

/* Remove key */
HT_ErrorCode ht_remove(HashTable* ht, const char* key);

/* Check existence */
bool ht_contains(HashTable* ht, const char* key);

/* Size */
size_t ht_size(HashTable* ht);

/* Hash function */
size_t ht_hash(const char* key, size_t capacity);

/*Check Load Factor*/
double ht_load_factor(HashTable* ht);

/*Print Hash Table*/
void ht_print(HashTable* ht);

/* =======================
   Resize / Rehash
   ======================= */

/* Resize table to new capacity */
HT_ErrorCode ht_resize(HashTable* ht, size_t new_capacity);

#endif /* HASH_TABLE_H */