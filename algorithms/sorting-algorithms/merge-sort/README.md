## Description
**Merge Sort** is a classic **divide and conquer** sorting algorithm.
It divides the array into two halves, recursively sorts each half, and then merges the sorted halves into a single sorted array.

Merge Sort is **stable** and works efficiently on large datasets.

---

## How It Works
1. Divide the array into two halves.
2. Recursively sort each half.
3. Merge the two sorted halves into a single sorted array.
4. Repeat until the entire array is sorted.

---

## Time & Space Complexity

| Case        | Time Complexity | Space Complexity | Stable? |
|------------|----------------|----------------|---------|
| Best Case  | O(n log n)     | O(n)           | Yes   |
| Average    | O(n log n)     | O(n)           | Yes   |
| Worst Case | O(n log n)     | O(n)           | Yes   |

**Explanation:**
- **Time Complexity:**
  - Merge Sort uses a divide-and-conquer approach:
    - Divides the array in half → log n levels
    - Merges each level → O(n) work per level
  - Total: O(n log n)
- **Space Complexity:**
  - O(n) extra space is used for temporary arrays during merging
  - Merge Sort is **not in-place** (unless using advanced techniques)
- **Stable:** Yes, equal elements retain their relative order
- **Adaptive:** No, performance does not improve for nearly sorted arrays