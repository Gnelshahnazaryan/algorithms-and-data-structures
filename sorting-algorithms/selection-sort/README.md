## Description
**Selection Sort** is a simple comparison-based sorting algorithm.
It works by repeatedly selecting the smallest element from the unsorted portion of the array and placing it at the beginning.

The algorithm divides the array into two parts:
- a **sorted** part on the left
- an **unsorted** part on the right

On each iteration, Selection Sort finds the minimum element in the unsorted part and swaps it with the first element of that part.
This process continues until the entire array is sorted.


## Time and Space Complexity

### Time Complexity
| Case        | Complexity |
|------------|------------|
| Best Case  | O(n²)      |
| Average    | O(n²)      |
| Worst Case | O(n²)      |

**Explanation:**
- **Best Case (O(n²))**: Even if the array is already sorted, Selection Sort still scans the remaining unsorted part to find the minimum element.
- **Average Case (O(n²))**: The algorithm always performs the same number of comparisons regardless of the input order.
- **Worst Case (O(n²))**: When the array is in reverse order, the number of comparisons remains the same.

---

### Space Complexity
- **O(1)** — Selection Sort is an in-place algorithm and does not require additional memory.

---

### Stability
- **Not Stable**
  Swapping elements can change the relative order of equal values.

---

### Adaptiveness
- **Not Adaptive**
  Selection Sort does not take advantage of an already sorted array.