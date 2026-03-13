class PriorityQueue {
  #heap;
  #cmp;
  #size;

  constructor(cmp = (a, b) => a - b) {
    if (typeof cmp !== 'function') {
      throw new Error('Invalid comparator');
    }

    this.#size = 0;
    this.#cmp = cmp;
    this.#heap = [];
  }

  /* ================= Basic State ================= */

  size() {
    return this.#size;
  }

  is_empty() {
    return this.#size === 0;
  }

  clear() {
    this.#heap = [];
    this.#size = 0;
  }

  comparator() {
    return this.#cmp;
  }

  /* ================= Access Operations ================= */

  peek() {
    if (this.is_empty()) {
      return undefined;
    }

    return this.#heap[0];
  }

  /* ================= Modification Operations ================= */

  add(value) {
    this.#heap[this.#size] = value;
    this.#shiftUp(this.#size);
    ++this.#size;
  }

  pop() {
    if (this.is_empty()) return undefined;
    this.#swap(0, this.#size - 1);
    let removed = this.#heap[this.#size - 1];
    --this.#size;
    this.#shiftDown(0);
    return removed;
  }

  remove(value) {
    if (this.is_empty()) return undefined;

    for (let i = 0; i < this.#size; ++i) {
      if (value === this.#heap[i]) {
        this.#swap(i, this.#size - 1);
        --this.#size;
        this.#shiftDown(i);
        this.#shiftUp(i);
        return;
      }
    }
  }

  /* ================= Index Helpers ================= */

  #get_parent(index) {
    return Math.floor((index - 1) / 2);
  }

  #get_left_child(index) {
    return 2 * index + 1;
  }

  #get_right_child(index) {
    return 2 * index + 2;
  }

  #swap(i, j) {
    [this.#heap[i], this.#heap[j]] = [this.#heap[j], this.#heap[i]];
  }

  /* ================= Heap Utilities ================= */

  toArray() {
    let arr = [];
    for (let i = 0; i < this.#size; ++i) {
      arr[i] = this.#heap[i];
    }
    return arr;
  }

  /* ================= Heap Maintenance ================= */

  #shiftUp(index) {
    if (index === 0) {
      return;
    }

    let parent = this.#get_parent(index);
    if (this.#cmp(this.#heap[index], this.#heap[parent]) >= 0) {
      return;
    }

    this.#swap(index, parent);
    this.#shiftUp(parent);
  }

  #shiftDown(index) {
    let leftChild = this.#get_left_child(index);
    let rightChild = this.#get_right_child(index);
    let targetIndex = index;

    if (
      leftChild < this.#size &&
      this.#cmp(this.#heap[leftChild], this.#heap[targetIndex]) < 0
    ) {
      targetIndex = leftChild;
    }

    if (
      rightChild < this.#size &&
      this.#cmp(this.#heap[rightChild], this.#heap[targetIndex]) < 0
    ) {
      targetIndex = rightChild;
    }

    if (targetIndex === index) {
      return;
    }
    this.#swap(index, targetIndex);
    this.#shiftDown(targetIndex);
  }

  /* ================= Search Utility ================= */

  #indexOf(value) {
    for (let i = 0; i < this.#size; ++i) {
      if (this.#heap[i] == value) {
        return i;
      }
    }
    return -1;
  }

  /* ================= Advanced Heap Operations ================= */

  heapify(array) {
    for (let i = 0; i < Math.floor(array.length / 2); ++i) {
      this.#shiftDown(i);
    }
  }

  replace(value) {
    let removed = this.#heap[0];
    this.#heap[0] = value;
    this.#shiftDown(0);
    return removed;
  }

  contains(value) {
    return this.#indexOf(value) !== -1;
  }

  /* ================= Iteration ================= */

  [Symbol.iterator]() {
    let i = 0;
    return {
      next: () => {
        if (i < this.#size) {
          return {
            value: this.#heap[i++],
            done: false,
          };
        }
        return {
          value: undefined,
          done: true,
        };
      },
    };
  }

  *values() {
    for (let i = 0; i < this.#size; ++i) {
      yield this.#heap[i];
    }
  }

  *entries() {
    for (let i = 0; i < this.#size; ++i) {
      yield [i, this.#heap[i]];
    }
  }
}