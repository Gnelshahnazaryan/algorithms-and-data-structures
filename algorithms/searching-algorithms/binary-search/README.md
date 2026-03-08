# Binary Search 

## Overview

Binary Search is an efficient searching algorithm used to find the position of a target value in a **sorted array**.
It works by repeatedly dividing the search interval in half.

Instead of checking every element like **Linear Search**, Binary Search compares the target value with the **middle element** of the array and eliminates half of the remaining elements.

Binary Search only works on **sorted arrays**.

---

## Algorithm Idea

1. Find the **middle index** of the array.
2. Compare the middle element with the target value.
3. If the target equals the middle element → return the index.
4. If the target is smaller → search in the **left half**.
5. If the target is greater → search in the **right half**.
6. Repeat until the element is found or the search space becomes empty.

---