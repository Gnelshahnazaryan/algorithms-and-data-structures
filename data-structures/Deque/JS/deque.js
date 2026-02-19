class Deque {
  #deque;
  #front;
  #size;
  #cap;

  constructor(cap = 8) {
    if (typeof cap != 'number' || cap < 2) {
      throw new Error('Capacity must be above or equal 2');
    }

    this.#deque = new Array(cap).fill(undefined);
    this.#size = 0;
    this.#front = 0;
    this.#cap = cap;
  }

  /* ================= Basic State ================= */

  size() {
    return this.#size;
  }

  capacity() {
    return this.#cap;
  }

  empty() {
    return this.#size === 0;
  }

  full() {
    return this.#cap === this.#size;
  }

  /* ================= Internal Helpers ================= */

  #mod(i) {
    if (i < 0) {
      throw new Error('Index must be positive number');
    }

    return this.#index(this.#front + i);
  }

  #index(i) {
    return i % this.#cap;
  }

  #ensureCapacityForOneMore() {
    if (this.#size < this.#cap) {
      return;
    }

    let deque = new Array(this.#cap * 2).fill(undefined);

    for (let i = 0; i < this.#size; ++i) {
      let idx = this.#mod(i);
      deque[i] = this.#deque[idx];
    }

    this.#deque = deque;
    this.#front = 0;
    this.#cap *= 2;
  }

  static #deepCopyValue(value) {
    if (value === null || typeof value !== 'object') return value;
    if (Array.isArray(value)) return value.map((v) => Deque.#deepCopyValue(v));
    if (value instanceof Deque) return value.clone();

    const copy = {};
    for (const key in value) {
      if (value.hasOwnProperty(key)) {
        copy[key] = Deque.#deepCopyValue(value[key]);
      }
    }
    return copy;
  }

  /* ================= Element Access ================= */

  front() {
    if (this.empty()) {
      throw new Error('Deque is empty');
    }
    return this.#deque[this.#front];
  }

  back() {
    if (this.empty()) {
      throw new Error('Deque is empty');
    }

    return this.#deque[this.#index(this.#front - 1)];
  }

  at(i) {
    if (this.empty()) {
      throw new Error('Deque is empty');
    }

    if (i < 0 || i >= this.#size) {
      throw new Error('Index out of bounds');
    }

    return this.#deque[this.#mod(i)];
  }

  /* ================= Modifiers ================= */

  push_back(value) {
    this.#ensureCapacityForOneMore();

    const idx = this.#mod(this.#size);
    this.#deque[idx] = value;
    ++this.#size;
  }

  push_front(value) {
    this.#ensureCapacityForOneMore();

    this.#front = (this.#front - 1 + this.#cap) % this.#cap;
    this.#deque[this.#front] = value;
    ++this.#size;
  }

  pop_front() {
    if (this.empty()) {
      throw new Error('Deque is empty');
    }

    const value = this.#deque[this.#front];
    this.#deque[this.#front] = undefined;
    this.#front = this.#front + 1 === this.#cap ? 0 : ++this.#front;
    --this.#size;
    return value;
  }

  pop_back() {
    if (this.empty()) {
      throw new Error('Deque is empty');
    }

    const idx = this.#mod(this.#size) - 1;
    const value = this.#deque[idx];

    this.#deque[idx] = undefined;
    --this.#size;

    return value;
  }

  clear() {
    this.#front = 0;
    this.#size = 0;
  }

  /* ================= Extended Professional Methods ================= */

  reserve(newCapacity) {
    if (newCapacity <= this.#cap) {
      return;
    }

    let deque = new Array(newCapacity).fill(undefined);

    for (let i = 0; i < this.#size; ++i) {
      let idx = this.#mod(i);
      deque[i] = this.#deque[idx];
    }

    this.#front = 0;
    this.#deque = deque;
    this.#cap = newCapacity;
  }

  shrinkToFit() {
    if (this.#cap === this.#size) {
      return;
    }
    let deque = new Array(this.#size).fill(undefined);

    for (let i = 0; i < this.#size; ++i) {
      let idx = this.#mod(i);
      deque[i] = this.#deque[idx];
    }

    this.#front = 0;
    this.#deque = deque;
    this.#cap = this.#size;
  }

  rotateRight(k = 1) {
    if (this.empty()) return;
    k %= this.#size;
    this.#front = (this.#front - k + this.#cap + 1) % this.#cap;
  }

  rotateLeft(k = 1) {
    k %= this.#size;
    this.#front = (this.#front + k - 1) % this.#cap;
  }

  swap(i, j) {
    if (i < 0 || i >= this.#size || j < 0 || j >= this.#size) {
      throw new Error('Indexes out of bound');
    }

    const idxI = this.at(i);
    const idxJ = this.at(j);

    [this.#deque[idxI], this.#deque[idxJ]] = [
      this.#deque[idxJ],
      this.#deque[idxI],
    ];
  }

  /* ================= Search & Utilities ================= */

  find(value) {
    let arr = this.toArray();

    for (let i = 0; i < this.#size; ++i) {
      if (arr[i] === value) {
        return i;
      }
    }
    return -1;
  }

  includes(value) {
    if (this.find(value) >= 0) {
      return true;
    }
    return false;
  }

  toArray() {
    let arr = [];

    for (let i = 0; i < this.#size; ++i) {
      let idx = this.#mod(i);
      arr[i] = this.#deque[idx];
    }
    return arr;
  }

  clone() {
    const copy = new Deque(this.#cap);
    copy.#size = this.#size;
    copy.#front = 0;

    for (let i = 0; i < this.#size; i++) {
      const val = this.#deque[this.#mod(i)];
      copy.#deque[i] = Deque.#deepCopyValue(val);
    }

    return copy;
  }

  equals(otherDeque) {
    if (this.size() !== otherDeque.size()) {
      return false;
    }

    for (let i = 0; i < this.#size; ++i) {
      if (this.at(i) !== otherDeque.at(i)) {
        return false;
      }
    }
    return true;
  }

  /* ================= Iteration ================= */

  [Symbol.iterator]() {
    let i = 0;

    return {
      next: () => {
        if (i < this.#size) {
          return {
            value: this.#deque[this.#mod(i++)],
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

  *keys() {
    for (let i = 0; i < this.#size; ++i) {
      yield i;
    }
  }

  *values() {
    for (let i = 0; i < this.#size; ++i) {
      yield [this.#deque[this.#mod(i)]];
    }
  }

  *entries() {
    for (let i = 0; i < this.#size; ++i) {
      yield [i, this.#deque[this.#mod(i)]];
    }
  }

  /* ================= Functional Style ================= */

  forEach(fn) {
    for (let i = 0; i < this.#size; ++i) {
      fn(this.#deque[this.#mod(i)], i, this);
    }
  }

  map(fn) {
    let result = new Deque(this.#cap);
    for (let i = 0; i < this.#size; ++i) {
      result.push_back(fn(this.#deque[this.#mod(i)], i, this));
    }

    return result;
  }

  filter(fn) {
    let result = new Deque();

    for (let i = 0; i < this.#size; ++i) {
      if (fn(this.#deque[this.#mod(i)], i, this)) {
        result.push_back(this.#deque[this.#mod(i)]);
      }
    }

    result.shrinkToFit();
    return result;
  }

  reduce(fn, initial) {
    if (this.empty()) {
      throw new Error('Deque must be non-empty');
    }

    if (initial !== undefined) {
      acc = initial;
      startIndex = 0;
    } else {
      acc = this.#deque[this.#mod(0)];
      startIndex = 1;
    }

    for (let i = startIndex; i < this.#size; ++i) {
      acc = fn(acc, this.#deque[this.#mod(i)], i, this);
    }

    return acc;
  }
}