# Algorithms and Data Structures

This repository contains implementations of fundamental **algorithms** and **data structures**.

## Project Structure

Algorithms-and-Data-Structures/
├── Algorithms
│   ├── Sorting
│   ├── Searching
└── Data Structures
    ├── Array
    ├── Linked List
    ├── Deque
    ├── Stacks & Queues
    ├── Binary Search Tree
    ├── AVL
    ├── Hash Table
    └── Graph

## Topics Covered

| Structure     | Description                     |
| ------------- | ------------------------------- |
| Dynamic Array | index-based structure           |
| Linked List   | Nodes connected via pointers    |
| Stack         | LIFO (Last In First Out)        |
| Queue         | FIFO (First In First Out)       |
| Deque         | Double Ended Queue              |
| Hash Table    | Key-value storage with hashing  |
| BST           | Ordered binary tree             |
| AVL Tree      | Self-balancing BST              |
| Heap          | Complete binary tree            |
| Graph         | Vertices + edges representation |

---

### Algorithms

#### Sorting

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort

#### Searching

- Linear Search
- Binary Search

## Languages Used

- JavaScript
- C

---

## Complexity Overview

### Data Strucures

| Data Structure | Access     | Search     | Insert     | Delete     |
| -------------- | ---------- | ---------- | ---------- | ---------- |
| Array          | O(1)       | O(n)       | O(n)       | O(n)       |
| Linked List    | O(n)       | O(n)       | O(1)       | O(1)       |
| Stack          | N/A        | O(n)       | O(1)       | O(1)       |
| Queue          | N/A        | O(n)       | O(1)       | O(1)       |
| Deque          | N/A        | O(n)       | O(1)       | O(1)       |
| Hash Table     | N/A        | O(1)\*     | O(1)\*     | O(1)\*     |
| BST            | O(log n)\* | O(log n)\* | O(log n)\* | O(log n)\* |
| AVL Tree       | O(log n)   | O(log n)   | O(log n)   | O(log n)   |
| Heap           | N/A        | O(n)       | O(log n)   | O(log n)   |

- O(1) for Hash Table is average case, worst case is O(n)
- BST complexities are average case; worst case becomes O(n)
- Heap does not support efficient search (O(n))
- Stack/Queue/Deque do not support direct access

### Sorting Algorithms

| Algorithm      | Best Time  | Average Time | Worst Time | Space    | Stable | In-Place |
| -------------- | ---------- | ------------ | ---------- | -------- | ------ | -------- |
| Bubble Sort    | O(n)       | O(n²)        | O(n²)      | O(1)     | Yes    | Yes      |
| Selection Sort | O(n²)      | O(n²)        | O(n²)      | O(1)     | No     | Yes      |
| Insertion Sort | O(n)       | O(n²)        | O(n²)      | O(1)     | Yes    | Yes      |
| Merge Sort     | O(n log n) | O(n log n)   | O(n log n) | O(n)     | Yes    | No       |
| Quick Sort     | O(n log n) | O(n log n)   | O(n²)      | O(log n) | No     | Yes      |

### Searching Algorithms

| Algorithm     | Time Complexity | Notes                 |
| ------------- | --------------- | --------------------- |
| Linear Search | O(n)            | Works on unsorted     |
| Binary Search | O(log n)        | Requires sorted array |

## Purpose

- Improve problem-solving skills
- Understand time and space complexity
- Prepare for coding interviews (e.g. LeetCode)
- Build strong fundamentals in DSA
- Build strong low-level and high-level understanding

---

## Notes

- Each folder includes:
  - Implementation (JS/C)
  - Comments explaining logic
  - Example usage (if needed)

- Focus is on **understanding concepts**, not just solutions.

---

## Usage

### Clone the repository

git clone https://github.com/Gnelshahnazaryan/algorithms-and-data-structures.git

### Navigate to a folder

cd algorithms-and-data-structures/

### Run JavaScript file

node filename.js

### Run C file

gcc ./tests/_.c ./src/_.c -o output
./output
