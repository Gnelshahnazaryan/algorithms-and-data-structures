class Node {
  constructor(value, left = null, right = null) {
    this.value = value;
    this.left = left;
    this.right = right;
  }
}

class BST {
  #root;
  #size;

  constructor() {
    this.#root = null;
    this.#size = 0;
  }

  /* ================= Basic State ================= */

  size() {
    return this.#size;
  }

  root() {
    return this.#root;
  }

  is_empty() {
    return this.#size === 0;
  }

  clear() {
    this.#root = null;
    this.#size = 0;
  }

  /* ================= Insert / Delete ================= */

  insert_itr(value) {
    const newNode = new Node(value);
    let current = this.#root;

    if (!current) {
      this.#root = newNode;
      ++this.#size;
      return;
    }

    while (true) {
      if (value < current.value) {
        if (!current.left) {
          current.left = newNode;
          break;
        }
        current = current.left;
      } else if (current.value < value) {
        if (!current.right) {
          current.right = newNode;
          break;
        }
        current = current.right;
      } else {
        return;
      }
    }
    ++this.#size;
    return;
  }

  insert_rec(value) {
    this.#root = this.#_insert(this.#root, value);
  }

  delete_itr(value) {
    if (this.is_empty()) {
      return false;
    }

    let current = this.#root;
    let parent = null;

    while (current && current.value !== value) {
      parent = current;
      current = current.value < value ? current.right : current.left;
    }

    if (!current) {
      return false;
    }

    if (!current.left || !current.right) {
      const child = current.left || current.right;

      if (!parent) {
        this.#root = child;
      } else if (parent.left === current) {
        parent.left = child;
      } else {
        parent.right = child;
      }
    } else {
      let successor = current.right;
      let successorParent = current;

      while (successor.left) {
        successorParent = successor;
        successor = successor.left;
      }

      current.value = successor.value;

      if (successorParent.left === successor) {
        successorParent.left = successor.right;
      } else {
        successorParent.right = successor.right;
      }
    }
    --this.#size;
    return true;
  }

  delete_rec(value) {
    this.#root = this.#_delete(this.#root, value);
  }

  contains_itr(value) {
    if (this.is_empty()) {
      return false;
    }

    let current = this.#root;

    while (current) {
      if (value === current.value) return true;
      if (value < current.value) current = current.left;
      else current = current.right;
    }

    return false;
  }

  contains_rec(value) {
    if (this.is_empty()) {
      return false;
    }

    return this.#_contains(this.#root, value);
  }

  search(value) {
    return this.#_search(this.#root, value);
  }

  /* ================= Height & Depth ================= */

  get_height_rec() {
    return this.#_getHeight(this.#root);
  }

  get_depth_itr(value) {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    if (!this.#_contains(this.#root, value)) {
      throw new Error("Value don't exist");
    }

    let depth = 0;
    let current = this.#root;

    while (current.value != value) {
      current = current.value < value ? current.right : current.left;
      ++depth;
    }

    return depth;
  }

  get_depth_rec(value) {
    return this.#_getDepth(this.#root, value);
  }
  /* ================= Min / Max ================= */

  find_min() {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }
    return this.#_find_min(this.#root);
  }

  find_max() {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    return this.#find_max(this.#root);
  }

  /* ================= Traversals ================= */

  preorder_itr() {
    if (!this.#root) {
      return [];
    }

    const stack = [this.#root];
    const result = [];

    while (stack.length) {
      const node = stack.pop();
      result.push(node.value);

      if (node.right) stack.push(node.right);
      if (node.left) stack.push(node.left);
    }
    return result;
  }

  preorder_rec() {
    const res = [];
    this.#_preorder(this.#root, res);
    return res;
  }

  inorder_itr() {
    if (!this.#root) {
      return [];
    }

    const stack = [];
    const result = [];
    let current = this.#root;

    while (current || stack.length) {
      while (current) {
        stack.push(current);
        current = current.left;
      }
      current = stack.pop();
      result.push(current.value);
      current = current.right;
    }
    return result;
  }

  inorder_rec() {
    const result = [];
    this.#_inorder(this.#root, result);
    return result;
  }

  postorder_itr() {
    if (!this.#root) return [];

    const stack1 = [this.#root];
    const stack2 = [];
    const result = [];

    while (stack1.length) {
      const node = stack1.pop();
      stack2.push(node);

      if (node.left) stack1.push(node.left);
      if (node.right) stack1.push(node.right);
    }

    while (stack2.length) {
      result.push(stack2.pop().value);
    }
    return result;
  }

  postorder_rec() {
    const result = [];
    this.#_postorder(this.#root, result);
    return result;
  }

  level_order_itr() {
    if (!this.#root) return [];

    const queue = [this.#root];
    const result = [];

    while (queue.length) {
      const node = queue.shift();
      result.push(node.value);

      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    return result;
  }

  level_order_rec() {
    const result = [];
    this.#_level_order(this.#root, 0, result);
    return result;
  }

  /* ================= Advanced Operations ================= */

  find_successor(node) {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    if (!this.#_contains(this.#root, node.value)) {
      throw new Error("Node don't exist");
    }

    if (node.right) {
      return this.#_find_min(node.right);
    }

    let current = this.#root;
    let ancestor = null;

    while (current.value !== node.value) {
      if (current.value > node.value) {
        ancestor = current;
        current = current.left;
      } else {
        current = current.right;
      }
    }
    return ancestor.value;
  }

  find_predecessor(node) {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    if (!this.#_contains(this.#root, node.value)) {
      throw new Error("Node don't exist");
    }

    if (node.left) {
      return this.#find_max(node.left);
    }

    let current = this.#root;
    let ancestor = null;

    while (node.value !== current.value) {
      if (current.value < node.value) {
        ancestor = current;
        current = current.right;
      } else {
        current = current.left;
      }
    }
    return ancestor.value;
  }

  isBalanced() {
    if (!this.#root) {
      return true;
    }

    const left = this.#_getHeight(this.#root.left);
    const right = this.#_getHeight(this.#root.right);

    return Math.abs(left - right) <= 1;
  }

  /* ================= Utilities ================= */

  toArray() {
    return this.inorder_rec();
  }

  clone() {
    const clone = new BST();
    const nodes = this.preorder_rec();

    for (let i = 0; i < nodes.length; ++i) {
      clone.insert_rec(nodes[i]);
    }

    return clone;
  }

  equals(otherTree) {
    if (otherTree.size() !== this.size() || !(otherTree instanceof BST)) {
      return false;
    }

    return this.#_equals(this.root(), otherTree.root());
  }

  /* ================= Iteration ================= */

  [Symbol.iterator]() {
    const inorder = this.inorder_rec();
    let i = 0;

    return {
      next: () => {
        if (i < inorder.length) {
          return {
            value: inorder[i++],
            done: false,
          };
        } else {
          return {
            value: undefined,
            done: true,
          };
        }
      },
    };
  }

  *values() {
    const inorder = this.inorder_rec();

    for (let i = 0; i < inorder.length; ++i) {
      yield inorder[i];
    }
  }

  *entries() {
    const inorder = this.inorder_rec();

    for (let i = 0; i < inorder.length; ++i) {
      yield [i, inorder[i]];
    }
  }

  /* ================= Private Helpers ================= */

  #_insert(node, value) {
    if (!node) {
      ++this.#size;
      return new Node(value);
    }

    if (value < node.value) {
      node.left = this.#_insert(node.left, value);
    } else {
      node.right = this.#_insert(node.right, value);
    }

    return node;
  }

  #_delete(node, value) {
    if (!node) return node;

    if (value < node.value) {
      node.left = this.#_delete(node.left, value);
    } else if (node.value < value) {
      node.right = this.#_delete(node.right, value);
    } else {
      --this.#size;

      if (!node.left) return node.right;
      if (!node.right) return node.left;

      let successor = node.right;
      while (successor.left) {
        successor = successor.left;
      }

      node.value = successor.value;
      node.right = this.#_delete(node.right, successor.value);
    }
    return node;
  }

  #_contains(node, value) {
    if (!node) {
      return false;
    }

    if (node.value === value) {
      return true;
    }

    if (value < node.value) {
      return this.#_contains(node.left, value);
    } else {
      return this.#_contains(node.right, value);
    }
  }

  #_getHeight(node) {
    if (!node) {
      return 0;
    }

    return (
      Math.max(this.#_getHeight(node.left), this.#_getHeight(node.right)) + 1
    );
  }

  #_getDepth(node, value) {
    if (!node) return -1;

    return (
      1 + this.#_getDepth(node.value < value ? node.right : node.left, value)
    );
  }

  #_preorder(node, result) {
    if (!node) return;
    result.push(node.value);
    this.#_preorder(node.left, result);
    this.#_preorder(node.right, result);
  }

  #_inorder(node, result) {
    if (!node) return;

    this.#_inorder(node.left, result);
    result.push(node.value);
    this.#_inorder(node.right, result);
  }

  #_postorder(node, result) {
    if (!node) return;

    this.#_postorder(node.left, result);
    this.#_postorder(node.right, result);
    result.push(node.value);
  }

  #_level_order(node, level, result) {
    if (!node) return;

    if (!result[level]) result[level] = [];
    result[level].push(node.value);

    this.#_level_order(node.left, level + 1, result);
    this.#_level_order(node.right, level + 1, result);
  }

  #_find_min(node) {
    if (!node.left) return node.value;
    return this.#_find_min(node.left);
  }

  #find_max(node) {
    if (!node.right) return node.value;
    return this.#find_max(node.right);
  }

  #_search(node, value) {
    if (!node) return null;

    if (node.value == value) {
      return node;
    }

    return this.#_search(node.value < value ? node.right : node.left, value);
  }

  #_equals(node1, node2) {
    if (!node1 && !node2) {
      return true;
    }

    if (!node1 || !node2) {
      return false;
    }

    if (node1.value !== node2.value) {
      return false;
    }

    return (
      this.#_equals(node1.left, node2.left) &&
      this.#_equals(node1.right, node2.right)
    );
  }
}