## Description
**Insertion Sort** is a simple and efficient comparison-based sorting algorithm.
It builds the sorted array one element at a time by inserting each new element into its correct position among the previously sorted elements.

It is similar to how people sort playing cards in their hands.

---

## How It Works
1. Start with the second element (index 1) as the key.
2. Compare the key with elements before it in the sorted part.
3. Shift all elements larger than the key one position to the right.
4. Insert the key into its correct position.
5. Repeat until the entire array is sorted.

---
## Time & Space Complexity

| Case        | Time Complexity | Space Complexity | Stable? |
|------------|----------------|----------------|---------|
| Best Case  | O(n)           | O(1)           | Yes   |
| Average    | O(n²)          | O(1)           | Yes   |
| Worst Case | O(n²)          | O(1)           | Yes   |

**Explanation:**
- **Best Case (O(n))**: Array is already sorted. Only comparisons occur, no shifting needed.
- **Average Case (O(n²))**: Elements need shifting to insert into the correct position.
- **Worst Case (O(n²))**: Array is reverse-sorted, maximum shifting required.
- **Space Complexity (O(1))**: Sorting is done **in-place**, no extra array is needed.
- **Stable**: Equal elements maintain their relative order.
- **Adaptive**: Performs faster on nearly sorted arrays.