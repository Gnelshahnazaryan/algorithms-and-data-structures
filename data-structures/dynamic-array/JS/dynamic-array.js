class DynamicArray {
  #arr;
  #size;
  #capacity;
  #GROWTH = 2;

  constructor(cap, fill = 0) {
    if (cap < 0 || !Number.isInteger(cap)) {
      throw new Error("Capacity must be positive integer");
    }
    if (!Number.isInteger(fill)) {
      throw new Error("Array must be filled only integers");
    }

    this.#arr = new Uint32Array(cap).fill(fill);
    this.#size = cap;
    this.#capacity = cap;
  }

  /* ================= Capacity ================= */

  size() {
    return this.#size;
  }

  capacity() {
    return this.#capacity;
  }

  empty() {
    return this.#size === 0;
  }

  reserve(n) {
    if (n <= this.#capacity) {
      return;
    }

    if (!Number.isInteger(n)) {
      throw new Error("n must be integer");
    }

    this.#capacity = n;
    const arr = new Uint32Array(n);

    for (let i = 0; i < this.#size; ++i) {
      arr[i] = this.#arr[i];
    }
    this.#arr = arr;
  }

  shrinkToFit() {
    this.#capacity = this.#size;

    const arr = new Uint32Array(this.#capacity);

    for (let i = 0; i < this.#capacity; ++i) {
      arr[i] = this.#arr[i];
    }

    this.#arr = arr;
  }

  clear() {
    this.#size = 0;
  }

  /* ================= Element Access ================= */

  at(i) {
    if (i < 0 || i >= this.#size || !Number.isInteger(i)) {
      throw new Error("Index out of range");
    }
    return this.#arr[i];
  }

  set(i, value) {
    if (i < 0 || i >= this.#size || !Number.isInteger(i)) {
      throw new Error("Index out of range");
    }

    if (!Number.isInteger(value)) {
      throw new Error("Value must be integer");
    }

    this.#arr[i] = value;
  }

  front() {
    return this.at(0);
  }

  back() {
    return this.at(this.#size - 1);
  }

  toArray() {
    const arr = [];

    for (let i = 0; i < this.#size; ++i) {
      arr[i] = this.#arr[i];
    }

    return arr;
  }

  /* ================= Modifiers ================= */

  pushBack(value) {
    if (!Number.isInteger(value)) {
      throw new Error("Value must be integer");
    }

    if (this.#size === this.#capacity) {
      this.#capacity = this.#capacity === 0 ? 1 : this.#capacity * this.#GROWTH;
      const arr = new Uint32Array(this.#capacity);

      for (let i = 0; i < this.#size; ++i) {
        arr[i] = this.#arr[i];
      }

      arr[this.#size++] = value;
      this.#arr = arr;
      return;
    }

    this.#arr[this.#size++] = value;
  }

  popBack() {
    if (this.empty()) throw new Error("Array is empty");

    return this.#arr[--this.#size];
  }

  #resize(n) {
    if (n <= 0 || !Number.isInteger(n)) {
      throw new Error("n must be positive integer");
    }

    const limit = Math.min(this.#size, n);
    const arr = new Uint32Array(n);

    for (let i = 0; i < limit; ++i) {
      arr[i] = this.#arr[i];
    }

    this.#arr = arr;
    this.#size = limit;
    this.#capacity = n;
  }

  insert(pos, val, count = 1) {
    if (pos < 0 || pos > this.#size || !Number.isInteger(pos)) {
      throw new Error("Index out of range");
    }

    if (!Number.isInteger(val)) {
      throw new Error("Value must be integer");
    }

    if (!Number.isInteger(count)) {
      throw new Error("Count must be integer");
    }

    if (pos == this.#size) {
      while (count--) {
        this.pushBack(val);
      }
      return;
    }

    if (this.#size + count > this.#capacity) {
      this.#resize(this.#size + count);
      this.#size += count;
    }

    const arr = new Uint32Array(this.#capacity);
    for (let i = 0; i < this.#size; ++i) {
      if (i === pos) {
        while (count > 0) {
          arr[i++] = val;
          --count;
        }
        continue;
      }
      arr[i] = this.#arr[i];
    }
    this.#arr = arr;
  }

  erase(pos) {
    if (pos < 0 || pos >= this.#size || !Number.isInteger(pos)) {
      throw new Error("Index out of range");
    }

    if (pos === this.#size - 1) {
      this.popBack();
    }

    for (let i = pos; i < this.#size - 1; ++i) {
      this.#arr[i] = this.#arr[i + 1];
    }

    this.#size--;
  }

  swap(i, j) {
    if (
      i < 0 ||
      i >= this.#size ||
      j < 0 ||
      j >= this.#size ||
      !Number.isInteger(i) ||
      !Number.isInteger(j)
    ) {
      throw new Error("Invalid index");
    }

    [this.#arr[i], this.#arr[j]] = [this.#arr[j], this.#arr[i]];
  }

  /* ================= Iteration ================= */

  *[Symbol.iterator]() {
    let i = 0;
    while (i < this.#size) {
      yield this.#arr[i++];
    }
  }

  *values() {
    let i = 0;
    while (i < this.#size) {
      yield this.#arr[i++];
    }
  }

  *keys() {
    let i = 0;
    while (i < this.#size) {
      yield i++;
    }
  }

  *entries() {
    let i = 0;
    while (i < this.#size) {
      yield [i, this.#arr[i++]];
    }
  }

  /* ================= High Order ================= */

  forEach(fn) {
    for (let i = 0; i < this.#size; ++i) {
      fn(this.#arr[i], i, this.#arr);
    }
  }

  map(fn) {
    const arr = new DynamicArray(this.#size);

    for (let i = 0; i < this.#size; ++i) {
      arr[i] = fn(this.#arr[i], i, this.#arr);
    }

    return arr;
  }

  filter(fn) {
    const arr = new DynamicArray(this.#size);

    for (let i = 0; i < this.#size; ++i) {
      if (fn(this.#arr[i], i, this.#arr)) {
        arr[i] = this.arr[i];
      }
    }
    return arr;
  }

  reduce(fn, initial) {
    if (this.#size === 0 && initial === undefined) {
      throw new Error("Reduce of empty array with no initial value");
    }
    let acc;
    let startIndex;

    if (initial !== undefined) {
      acc = initial;
      startIndex = 0;
    } else {
      acc = this.#arr[0];
      startIndex = 1;
    }

    for (let i = startIndex; i < this.#size; ++i) {
      acc = fn(acc, this.#arr[i], i, this.#arr);
    }
    return acc;
  }

  some(fn) {
    for (let i = 0; i < this.#size; ++i) {
      if (fn(this.#arr[i], i, this.#arr)) {
        return true;
      }
    }
    return false;
  }

  every(fn) {
    for (let i = 0; i < this.#size; ++i) {
      if (!fn(this.#arr[i], i, this.#arr)) {
        return false;
      }
    }
    return true;
  }

  find(fn) {
    for (let i = 0; i < this.#size; ++i) {
      if (fn(this.#arr[i], i, this.#arr)) {
        return this.#arr[i];
      }
    }
  }

  findIndex(fn) {
    for (let i = 0; i < this.#size; ++i) {
      if (fn(this.#arr[i], i, this.#arr)) {
        return i;
      }
    }
    return -1;
  }

  includes(value) {
    for (let i = 0; i < this.#size; ++i) {
      if (this.#arr[i] === value) {
        return true;
      }
    }
    return false;
  }

  /* ================= Extensions ================= */

  reverse() {
    let i = 0;
    let j = this.#size - 1;

    while (i < j) {
      this.swap(i++, j--);
    }
  }

  sort(compareFn) {
    if (this.#size <= 32) {
      for (let i = 1; i < this.#size; ++i) {
        let j = i - 1;
        let key = this.#arr[i];

        while (j >= 0 && compareFn(key, this.#arr[j]) < 0) {
          this.#arr[j + 1] = this.#arr[j];
          --j;
        }
        this.#arr[j + 1] = key;
      }
      return;
    }

    function partition(arr, low, high) {
      let pivot = arr[low];
      let i = low;
      let j = high;

      while (i <= j) {
        while (compareFn(pivot, arr[i]) >= 0) {
          ++i;
        }
        while (compareFn(pivot, arr[j]) < 0) {
          --j;
        }

        if (i < j) {
          [arr[i], arr[j]] = [arr[j], arr[i]];
          ++i;
          --j;
        }
      }

      [arr[low], arr[j]] = [arr[j], arr[low]];
      return j;
    }

    function quickSort(arr, low, high) {
      if (low >= high) return;
      let pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
    }

    quickSort(this.#arr, 0, this.#size - 1);
  }

  clone() {
    const clone = new DynamicArray(this.#capacity);

    for (let i = 0; i < this.#size; ++i) {
      clone.popBack();
    }

    for (let i = 0; i < this.#size; ++i) {
      clone.pushBack(this.#arr[i]);
    }

    return clone;
  }

  equals(other) {
    if (!(other instanceof DynamicArray)) {
      return false;
    }

    if (this.size() !== other.size()) {
      return false;
    }

    for (let i = 0; i < this.#size; ++i) {
      if (this.at(i) !== other.at(i)) {
        return false;
      }
    }
    return true;
  }
}

const arr = new DynamicArray(4, 2);
