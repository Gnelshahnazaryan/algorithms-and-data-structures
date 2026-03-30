# Hash Table (Separate Chaining)

Implementation of a **Hash Table** using **Separate Chaining** with linked lists for collision handling.

---

## Overview

A **Hash Table** is a data structure that stores **key–value pairs** and provides **fast insertion, lookup, and deletion** operations.

It works by using a **hash function** to convert a key into an **index** in an underlying array called a **bucket array**. Each bucket stores one or more entries.

- **Collision handling**: When multiple keys map to the same bucket, this implementation uses **Separate Chaining** with **linked lists**. All entries that hash to the same index are stored in a linked list within that bucket.
- **Dynamic resizing**: The table can grow to maintain efficient operations when the **load factor** exceeds a certain threshold.

**Key Advantages:**

1. Average **O(1)** time complexity for insert, search, and delete operations.
2. Handles collisions efficiently using linked lists.

---

## Data Structure

The hash table contains:

- An array of buckets
- Each bucket stores a **linked list** of nodes:

---

## Features

- Key–value storage
- Collision handling using linked lists
- Automatic resizing
- `print()` function for debugging

---

| Operation | Average | Worst |
| --------- | ------- | ----- |
| Insert    | O(1)    | O(n)  |
| --------- | ------- | ----- |
| Search    | O(1)    | O(n)  |
| --------- | ------- | ----- |
| Delete    | O(1)    | O(n)  |