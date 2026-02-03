## Description
**Bubble Sort** is a simple and classic sorting algorithm.
It works by repeatedly comparing adjacent elements and swapping them if they are in the wrong order.

With each pass, the largest element “bubbles up” to the end of the array.

---

## How It Works
1. Traverse the array
2. Compare `arr[j]` and `arr[j + 1]`
3. Swap them if they are in the wrong order
4. Repeat until the array is fully sorted

---
## Time and Space Complexity

### Time Complexity
| Case        | Complexity |
|------------|------------|
| Best Case  | O(n)       |
| Average    | O(n²)      |
| Worst Case | O(n²)      |

**Explanation:**
- **Best Case (O(n))**: When the array is already sorted.
  With the early-exit optimization, the algorithm finishes after one pass.
- **Average Case (O(n²))**: When the elements are in random order.
- **Worst Case (O(n²))**: When the array is sorted in reverse order.

---

### Space Complexity
- **O(1)** — Bubble Sort is an in-place algorithm and does not use extra memory.

---

### Stability
- **Stable**
  Equal elements maintain their relative order.

---

### Adaptiveness
- **Adaptive**
  Bubble Sort can stop early if no swaps occur during a pass.