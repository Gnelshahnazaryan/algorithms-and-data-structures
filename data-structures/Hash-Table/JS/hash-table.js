class Node {
  constructor(key, value, next = null) {
    this.key = key;
    this.value = value;
    this.next = next;
  }
}

class HashTable {
  #table;
  #capacity;
  #size;
  #loadFactor;

  constructor(capacity = 17, loadFactor = 1.0) {
    if (typeof capacity != 'number' || capacity <= 0) {
      throw new Error('Capacity must be positive number');
    }

    this.#table = new Array(capacity).fill(null);
    this.#size = 0;
    this.#capacity = capacity;
    this.#loadFactor = loadFactor;
  }

  /* ================= Basic State ================= */

  size() {
    return this.#size;
  }

  capacity() {
    return this.#capacity;
  }

  isEmpty() {
    return this.#size === 0;
  }

  clear() {
    this.#size = 0;
    this.#table = new Array(this.#capacity).fill(null);
  }

  /* ================= Hashing ================= */

  #hash(key) {
    //Division Method
    if (typeof key === 'number') {
      return Math.floor(Math.abs(key) % this.#capacity);
    }

    // Polynomial Hash
    if (typeof key === 'string') {
      let h = 0;
      const p = 31;

      for (let i = 0; i < key.length; i++) {
        h = (h * p + key.charCodeAt(i)) | 0;
      }

      return Math.abs(h) % this.#capacity;
    }
    throw new Error('Unsupported key type');
  }

  /* ================= Core Operations ================= */

  put(key, value) {
    let index = this.#hash(key);
    let node = this.#table[index];

    while (node) {
      if (node.key === key) {
        node.value = value;
        return;
      }
      node = node.next;
    }

    const newNode = new Node(key, value);
    newNode.next = this.#table[index];
    this.#table[index] = newNode;
    ++this.#size;

    if (this.loadFactor() > this.#loadFactor) {
      this.#resize(this.#capacity * 2);
    }
    ++this.#size;
    return;
  }

  get(key) {
    let index = this.#hash(key);
    let node = this.#table[index];

    while (node) {
      if (node.key === key) {
        return node.value;
      }
    }
    return undefined;
  }

  remove(key) {
    let index = this.#hash(key);
    let node = this.#table[index];
    let prev = null;
    let removed;

    while (node) {
      if (node.key === key) {
        removed = node.value;
        if (prev) {
          prev.next = node.next;
          node.next = null;
          --this.#size;
          return removed;
        }
        this.#table[index] = node.next;
        --this.#size;
        return removed;
      }
      prev = node;
      node = node.next;
    }
  }

  containsKey(key) {
    let index = this.#hash(key);
    let node = this.#table[index];

    while (node) {
      if (node.key === key) {
        return true;
      }
      node = node.next;
    }
    return false;
  }

  containsValue(value) {
    for (let i = 0; i < this.#capacity; ++i) {
      let node = null;
      if (this.#table[i]) {
        node = this.#table[i];
      } else {
        continue;
      }

      while (node) {
        if (node.value === value) {
          return true;
        }
        node = node.next;
      }
    }
    return false;
  }
  /* ================= Resize / Rehash ================= */

  #resize(newCapacity) {
    const prime = this.#getNextPrime(newCapacity);
    const newBuckets = new Array(prime).fill(null);
    const oldTable = this.#table;

    this.#table = newBuckets;
    this.#capacity = prime;

    for (let head of oldTable) {
      let node = head;

      while (node) {
        this.put(node.key, node.value);
        node = node.next;
      }
    }
  }

  loadFactor() {
    return this.#size / this.#capacity;
  }

  /* ================= isPrime / getNextPrime ================= */

  #isPrime(num) {
    if (num <= 1) {
      return false;
    }

    if (num === 2) {
      return true;
    }

    if (num % 2 === 0) {
      return false;
    }

    const sqrtNum = Math.floor(Math.sqrt(num));
    for (let i = 3; i <= sqrtNum; i += 2) {
      if (num % i === 0) {
        return false;
      }
    }
    return true;
  }

  #getNextPrime(num) {
    let nextPrime = num + 1;
    while (!this.#isPrime(nextPrime)) {
      nextPrime++;
    }
    return nextPrime;
  }

  /* ================= Entry Views ================= */

  keys() {
    const keys = [];

    for (let i = 0; i < this.#capacity; ++i) {
      let node = null;

      if (this.#table[i]) {
        node = this.#table[i];
      } else {
        continue;
      }

      while (node) {
        keys.push(node.key);
        node = node.next;
      }
    }
    return keys;
  }

  values() {
    const values = [];

    for (let i = 0; i < this.#capacity; ++i) {
      let node = null;

      if (this.#table[i]) {
        node = this.#table[i];
      } else {
        continue;
      }

      while (node) {
        values.push(node.value);
        node = node.next;
      }
    }
    return values;
  }

  entries() {
    const entries = [];

    for (let i = 0; i < this.#capacity; ++i) {
      let node = null;

      if (this.#table[i]) {
        node = this.#table[i];
      } else {
        continue;
      }

      while (node) {
        entries.push([node.key, node.value]);
        node = node.next;
      }
    }
    return entries;
  }

  /* ================= Iteration ================= */

  [Symbol.iterator]() {
    const entries = this.entries();
    let i = 0;

    return {
      next: () => {
        if (i < entries.length) {
          return {
            value: entries[i++],
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

  /* ================= Utility Operations ================= */

  toObject() {
    const map = new Map();
    const entries = this.entries();

    for (let i = 0; i < entries.length; ++i) {
      map.set(entries[i][0], entries[i][1]);
    }
    return map;
  }

  clone() {
    const clone = new HashTable(this.#capacity, this.#loadFactor);

    for (let head of this.#table) {
      let node = head;

      while (node) {
        clone.put(node.key, node.value);
        node = node.next;
      }
    }
    return clone;
  }

  equals(otherTable) {
    if (
      otherTable.size() !== this.size() ||
      !(otherTable instanceof HashTable) ||
      otherTable.capacity() !== this.capacity()
    ) {
      return false;
    }

    const thisEntries = this.entries();
    const otherEntries = otherTable.entries();

    for (let i = 0; i < thisEntries.length; ++i) {
      if (
        thisEntries[i][0] !== otherEntries[i][0] ||
        thisEntries[i][1] !== otherEntries[i][1]
      ) {
        return false;
      }
    }
    return true;
  }

  /* ================= Debug / Visualization ================= */

  bucketSizes() {
    const sizes = [];

    for (let i = 0; i < this.#capacity; ++i) {
      let count = 0;
      let node = null;

      if (this.#table[i]) {
        node = this.#table[i];
      } else {
        sizes.push(0);
        continue;
      }

      while (node) {
        ++count;
        node = node.next;
      }
      sizes.push(count);
    }
    return sizes;
  }

  print() {
    for (let i = 0; i < this.#capacity; i++) {
      let node = this.#table[i];
      let output = `Bucket ${i}: `;

      while (node) {
        output += `(${node.key}: ${node.value}) -> `;
        node = node.next;
      }

      console.log(output + 'null');
    }
  }
}
