class Node {
  #value;
  #next = null;

  constructor(value = 0) {
    this.value = value;
    this.next = null;
  }

  get value() {
    return this.#value;
  }

  set value(val) {
    if (val === undefined) {
      throw new Error('Invalid value');
    }

    this.#value = val;
  }

  get next() {
    if (!this.#next) {
      return null;
    }

    return this.#next;
  }

  set next(new_node) {
    if (!new_node) {
      this.#next = null;
      return;
    }

    this.#next = new_node;
  }
}

class SinglyLinkedList {
  #head = null;
  #size = 0;

  constructor(iterable) {
    if (!iterable) {
      return;
    }

    if (
      typeof iterable !== 'string' &&
      typeof iterable[Symbol.iterator] == 'function'
    ) {
      for (let item of iterable) {
        this.push_back(item);
      }
    } else {
      this.push_back(iterable);
    }
  }

  /* ================= Size & State ================= */

  size() {
    return this.#size;
  }

  isEmpty() {
    return this.#size === 0;
  }

  clear() {
    this.#head = null;
    this.#size = 0;
  }

  /* ================= Front Access ================= */

  front() {
    if (this.isEmpty()) {
      throw new Error('List is empty');
    }

    return this.#head;
  }

  /* ================= Push & Pop ================= */

  push_front(val) {
    let new_node = new Node(val);
    let current = this.#head;
    new_node.next = current;
    this.#head = new_node;
    this.#size++;
  }

  push_back(val) {
    if (this.isEmpty()) {
      this.#head = new Node(val);
      this.#size++;
      return;
    }

    let current = this.#head;

    while (current.next) {
      current = current.next;
    }

    let new_node = new Node(val);
    current.next = new_node;
    new_node.next = null;
    this.#size++;
  }

  pop_front() {
    if (this.isEmpty()) {
      throw new Error('List is empty');
    }

    let removed = this.#head;
    this.#head = removed.next;
    this.#size--;

    return removed.value;
  }

  pop_back() {
    if (this.isEmpty()) {
      throw new Error('List is empty');
    }

    if (this.#size === 1) {
      this.#head = null;
    }

    let current = this.#head;
    while (current.next.next != null) {
      current = current.next;
    }

    let removed = current.next;
    current.next = null;
    this.#size--;

    return removed.value;
  }

  /* ================= Random-like Access ================= */

  at(index) {
    if (index < 0 || index >= this.#size) {
      throw new Error('Invalid index');
    }

    if (index === 0) {
      return this.front().value;
    }

    let i = 0;
    let current = this.#head;

    while (i < index) {
      current = current.next;
      ++i;
    }

    return current.value;
  }

  insert(index, val) {
    if (!index || index < 0 || index >= this.#size) {
      throw new Error('Invalid index');
    }

    if (index === 0) {
      this.push_front(val);
      return;
    }

    if (index === this.#size) {
      this.push_back(val);
      return;
    }

    let new_node = new Node(val);
    let current = this.#head;

    let i = 0;

    while (i < index) {
      current = current.next;
      ++i;
    }

    let next = current.next;
    current.next = new_node;
    new_node.next = next;
    this.#size++;
  }

  erase(index) {
    if (!index || index < 0 || index >= this.#size) {
      throw new Error('Invalid index');
    }

    if (index === 0) {
      this.pop_front();
      return;
    }

    if (index === this.#size - 1) {
      this.pop_back();
      return;
    }

    let i = 0;
    let current = this.#head;

    while (i < index - 1) {
      current = current.next;
      ++i;
    }

    let next = current.next.next;
    current.next = next;
    this.#size--;
  }

  remove(value, equals) {
    let index = 0;
    let count = 0;
    let current = this.#head;

    if (typeof equals === 'function') {
      while (current) {
        if (equals(value, current.value)) {
          this.erase(index);
          ++count;
        }
        current = current.next;
        ++index;
      }
      return count;
    }

    while (current) {
      if (current.value === value) {
        this.erase(index);
        ++count;
      }
      current = current.next;
      ++index;
    }

    return count;
  }

  /* ================= Algorithms ================= */

  reverse() {
    let current = this.#head;
    let next = null;
    let prev = null;

    while (current) {
      next = current.next;
      current.next = prev;
      prev = current;
      current = next;
    }

    this.#head = prev;
  }

  #mergeSort(head, cmp) {
    if (!head || !head.next) {
      return head;
    }

    let slow = head;
    let fast = head.next;

    while (fast && fast.next) {
      fast = fast.next.next;
      slow = slow.next;
    }

    let mid = slow.next;
    slow.next = null;

    let left = this.#mergeSort(head, cmp);
    let right = this.#mergeSort(mid, cmp);

    return this.merge(left, right, cmp);
  }

  sort(cmp) {
    if (!cmp) {
      throw new Error('Function for compareing is undefined');
    }

    if (this.size() < 2) {
      return;
    }

    this.#head = this.#mergeSort(this.#head, cmp);
  }

  merge(NodeA, NodeB, cmp) {
    let dummy = new Node();
    let tail = dummy;

    while (NodeA && NodeB) {
      if (cmp(NodeA.value, NodeB.value) <= 0) {
        tail.next = NodeA;
        NodeA = NodeA.next;
      } else {
        tail.next = NodeB;
        NodeB = NodeB.next;
      }
      tail = tail.next;
    }

    tail.next = NodeA || NodeB;

    return dummy.next;
  }

  /* ================= Utilities ================= */

  toArray() {
    let current = this.#head;
    let res = [];

    while (current) {
      res.push(current.value);
      current = current.next;
    }

    return res;
  }

  static fromArray(arr) {
    return new SinglyLinkedList(arr);
  }

  /* ================= Iteration ================= */

  [Symbol.iterator]() {
    let current = this.#head;
    return {
      next: () => {
        if (!current) {
          return {
            value: undefined,
            done: true,
          };
        }
        let value = current.value;
        current = current.next;
        return {
          value: value,
          done: false,
        };
      },
    };
  }
}
