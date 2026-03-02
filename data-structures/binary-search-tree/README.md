# Binary Search Tree (BST) – (JS/C) Implementation

## Overview

This project implements a **Binary Search Tree (BST)** with JS and C.

A Binary Search Tree is a binary tree data structure where:

- All values in the left subtree are **less than** the node value.
- All values in the right subtree are **greater than** the node value.
- Duplicate values are not allowed (depending on implementation).

The BST supports insertion, deletion, search, traversal, predecessor, and successor operations.

---

## Features

- Insert
- Delete (leaf, one child, two children)
- Search
- Find Minimum
- Find Maximum
- Find Predecessor
- Find Successor
- Inorder Traversal
- Preorder Traversal
- Postorder Traversal
- Level-order Traversal
- Full test coverage (main.c)

---

| Operation               | Average Case | Worst Case |
| ----------------------- | ------------ | ---------- |
| Insert                  | O(log n)     | O(n)       |
| Search                  | O(log n)     | O(n)       |
| Delete                  | O(log n)     | O(n)       |
| Find Min / Max          | O(log n)     | O(n)       |
| Predecessor / Successor | O(log n)     | O(n)       |
| Traversals              | O(n)         | O(n)       |

---

## Traversals

| Traversal   | Order               | Usage         |
| ----------- | ------------------- | ------------- |
| Inorder     | Left → Root → Right | Sorted output |
| Preorder    | Root → Left → Right | Tree copy     |
| Postorder   | Left → Right → Root | Safe delete   |
| Level-order | Level by level      | BFS traversal |
