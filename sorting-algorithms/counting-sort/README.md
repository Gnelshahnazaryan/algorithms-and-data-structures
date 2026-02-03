## Description
**Counting Sort** is a non-comparison-based sorting algorithm.
It works by counting the number of occurrences of each element in the input array, and then using this information to place each element in the correct position in the sorted array.

**Cumulative Counting Sort** is an extension of Counting Sort where we compute the cumulative count to determine the final positions of elements. This helps make the sort **stable**.

---

## How It Works (Cumulative Counting Sort)
1. Find the maximum value in the array (`max`).
2. Create a `count` array of size `max + 1` and initialize all elements to 0.
3. Count the occurrences of each element in the input array and store in `count`.
4. Transform `count` into a **cumulative count** array.
5. Iterate the input array **in reverse** to place each element at its correct position in the output array.
6. Copy the sorted array back to the original array (if needed).

---
## Time & Space Complexity

| Algorithm                  | Time Complexity     | Space Complexity | Stable? |
|----------------------------|------------------|----------------|---------|
| Counting Sort (basic)      | O(n + k)         | O(n + k)       | No      |
| Cumulative Counting Sort   | O(n + k)         | O(n + k)       | Yes   |

**Legend:**
- `n` = number of elements in the array
- `k` = maximum value in the array

**Explanation:**
- **Time Complexity:** Counting occurs once for each element, and placement into the output array takes O(n). Cumulative counting also takes O(k) to build positions.
- **Space Complexity:** Both algorithms use a **count array of size k+1** and an **output array of size n**.
- **Stability:** Basic Counting Sort is not stable, but using cumulative counting makes it stable.
- **Notes:** If `k` is very large relative to `n`, space and time can be significant, so it may be less efficient than comparison-based sorts.