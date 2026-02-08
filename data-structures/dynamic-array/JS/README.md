# Dynamic Array (JavaScript)

**Dynamic Array** in JavaScript is a flexible array-like class, inspired by `std::vector` in C++ and native JS arrays.  
Supports dynamic resizing, safe element access, and **high-order functions** like `map`, `filter`, and `reduce`.

---

## Summary

- **Resizable:** Grows automatically when needed.  
- **Safe Access:** Methods validate indices.  
- **High-order Functions:** `map`, `filter`, `reduce` available, similar to native JS arrays.  
- **Memory Management:** Managed by JavaScript GC.  
- **Error Handling:** Throws errors or returns `null`/`undefined` for invalid operations.

---

## Table of Contents

1. [Lifecycle](#lifecycle)  
2. [Capacity](#capacity)  
3. [Modifiers](#modifiers)  
4. [Element Access](#element-access)  
5. [High-Order / Algorithms](#high-order--algorithms)  
6. [Utilities](#utilities)  
7. [Time & Space Complexity](#time--space-complexity)  
8. [Quick Start Example](#quick-start-example)

---

## Lifecycle

| Method | Returns | Notes |
|:-------|:-------|:-----|
| `constructor(capacity)` | `DynamicArray` | Initialize array with optional capacity |
| `clear()` | `void` | Reset size to 0 |

---

## Capacity

| Method | Returns | Notes |
|:-------|:-------|:-----|
| `empty()` | `boolean` | True if array is empty |
| `size()` | `number` | Number of elements |
| `capacity()` | `number` | Allocated capacity (optional) |
| `reserve(newCapacity)` | `void` | Ensure minimum capacity |
| `shrinkToFit()` | `void` | Reduce capacity to current size |

---

## Modifiers

| Method | Returns | Notes |
|:-------|:-------|:-----|
| `push(value)` | `void` | Append element |
| `pop()` | `any` | Remove last element |
| `insert(index, value, count=1)` | `void` | Insert element(s) at index |
| `erase(index)` | `void` | Remove element at index |
| `resize(newSize, fillValue=0)` | `void` | Resize array |
| `set(index, value)` | `void` | Set element at index |
| `swap(i, j)` | `void` | Swap two elements |

---

## Element Access

| Method | Returns | Notes |
|:-------|:-------|:-----|
| `at(index)` | `any` | Get element at index, `undefined` if out-of-bounds |
| `front()` | `any` | First element |
| `back()` | `any` | Last element |
| `toArray()` | `Array` | Returns a native JS array copy |

---

## High-Order / Algorithms

| Method | Returns | Notes |
|:-------|:-------|:-----|
| `includes(value)` | `boolean` | True if value exists |
| `filter(callback, ctx)` | `DynamicArray` | Returns new array with filtered elements |
| `map(callback, ctx)` | `DynamicArray` | Returns new array with mapped elements |
| `reduce(callback, initial, ctx)` | `any` | Reduce values to single result |

---

## Utilities

| Method | Returns | Notes |
|:-------|:-------|:-----|
| `reverse()` | `void` | Reverse array in place |
| `clone()` | `DynamicArray` | Returns deep copy |
| `equals(otherArray)` | `boolean` | Compare arrays for equality |
| `sort(cmp)` | `void` | Sort array in-place using compare function |

---

## Time & Space Complexity

| Operation | Time | Space | Notes |
|:----------|:---:|:-----|:-----|
| `push` | O(1) amortized | O(n) on resize | Doubles capacity when full |
| `pop` | O(1) | O(1) | |
| `insert` | O(n) | O(n) if resizing | Shifts elements right |
| `erase` | O(n) | O(1) | Shifts elements left |
| `at` / `front` / `back` | O(1) | O(1) | |
| `map` / `filter` | O(n) | O(n) | Returns new DynamicArray |
| `reduce` | O(n) | O(1) | Accumulates value |
| `sort` | O(n log n) | O(log n) | JS QuickSort / TimSort |

---

## Quick Start Example

```javascript
class DynamicArray {
  constructor(capacity = 0) {
    this.data = new Array(capacity);
    this.size = 0;
  }

  push(value) {
    this.data[this.size++] = value;
  }

  filter(callback, ctx) {
    const result = new DynamicArray();
    for (let i = 0; i < this.size; i++) {
      if (callback(this.data[i], i, this, ctx)) {
        result.push(this.data[i]);
      }
    }
    return result;
  }

  toArray() {
    return this.data.slice(0, this.size);
  }
}

// Example usage
const arr = new DynamicArray();
[1, 2, 3, 4, 5].forEach(v => arr.push(v));

const evens = arr.filter((val) => val % 2 === 0);

console.log(evens.toArray()); // [2, 4]
