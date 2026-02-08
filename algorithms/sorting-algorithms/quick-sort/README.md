## Description
**Quick Sort** is a classic **divide and conquer** sorting algorithm.
It selects a pivot element, partitions the array into elements less than the pivot and elements greater than the pivot, recursively sorts the partitions, and then combines them into a single sorted array.
Quick Sort is **not stable** but works efficiently on large datasets and is widely used due to its in-place sorting capability.

---

## How It Works
1. Choose a pivot element from the array (commonly first, last, middle, or random element).
2. Partition the array such that elements less than the pivot go to the left and elements greater go to the right.
3. Recursively apply Quick Sort to the left and right partitions.
4. Combine the partitions and pivot to form a sorted array.

---

## Time & Space Complexity

| Case       | Time Complexity | Space Complexity | Stable? |
| ---------- | --------------- | ---------------- | ------- |
| Best Case  | O(n log n)      | O(log n)         | No      |
| Average    | O(n log n)      | O(log n)         | No      |
| Worst Case | O(n²)           | O(n)             | No      |



**Explanation:**
- **Time Complexity:**
  - Quick Sort uses a divide-and-conquer approach:
    - Partitioning → O(n) work per recursion
    - Recursion depth → log n on average
  - Total average: O(n log n), worst case O(n²) when pivot selection is poor
- **Space Complexity:**
  - O(log n) extra space for recursion stack (in-place partitioning)
  - Quick Sort is **in-place**, no extra arrays required
- **Stable:** No, equal elements may change their relative order
- **Adaptive:** No, performance does not improve for nearly sorted arrays
