class Queue {
  #queue;
  #front;
  #back;
  #size;
  #cap;

  constructor(capacity) {
    if (!Number.isFinite(capacity) || capacity <= 0) {
      throw new Error('Capacity must be positive integer');
    }

    this.#queue = new Uint32Array(capacity);
    this.#cap = capacity;
    this.#size = 0;
    this.#back = -1;
    this.#front = 0;
  }

  /* ================= Basic State ================= */

  size() {
    return this.#size;
  }

  capacity() {
    return this.#cap;
  }

  isEmpty() {
    return this.#size === 0;
  }

  isFull() {
    return this.#size === this.#cap;
  }

  clear() {
    this.#size = 0;
    this.#front = 0;
    this.#back = 0;
  }

  /* ================= Core Queue Operations ================= */

  enqueue(value) {
    if (this.isFull()) {
      throw new Error('Queue Overflow');
    }

    this.#back = (this.#back + 1) % this.#cap;
    this.#queue[this.#back] = value;
    ++this.#size;
  }

  dequeue() {
    if (this.isEmpty()) {
      throw new Error('Queue is empty');
    }

    let removed = this.#queue[this.#front];
    this.#front = (this.#front + 1) % this.#cap;
    --this.#size;

    return removed;
  }

  peek() {
    if (this.isEmpty()) {
      throw new Error('Queue is empty');
    }

    return this.#queue[this.#front];
  }

  back() {
    if (this.isEmpty()) {
      throw new Error('Queue is empty');
    }

    return this.#queue[this.#back];
  }

  print() {
    for (let i = 0; i < this.#size; ++i) {
      let idx = (this.#front + i) % this.#cap;
      console.log(this.#queue[idx]);
    }
  }
}

