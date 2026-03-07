class Node {
  value;
  left;
  right;

  constructor(value = null) {
    value = value;
    this.left = null;
    this.right = null;
    this.height = 1;
  }
}

class AVL {
  #root = null;
  #size = 0;

  /* ================= Basic State ================= */

  size() {
    return this.#size;
  }

  is_empty() {
    return this.#size === 0;
  }

  clear() {
    this.#root = null;
    this.#size = 0;
  }

  /* ================= Core AVL Operations ================= */

  insert(value) {
    this.#root = this.#insert(this.#root, value);
  }

  delete(value) {
    this.#root = this.#delete(this.#root, value);
  }

  search(value) {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    return this.#search(this.#root, value);
  }
  /* ================= Height / Min / Max ================= */

  getHeight() {
    return this.#getHeight(this.#root);
  }

  getMin() {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    return this.#getMin(this.#root);
  }

  getMax() {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    return this.#getMax(this.#root);
  }

  /* ================= Traversals ================= */

  levelOrder() {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    const result = [];
    const queue = [this.#root];

    while (queue.length) {
      const node = queue.shift();
      result.push(node.value);

      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    return result;
  }

  preorder_rec() {
    const result = [];
    this.#preorder_rec(this.#root, result);
    return result;
  }

  preorder_itr() {
    if (this.is_empty()) return [];

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

  inorder_rec() {
    const result = [];
    this.#inorder_rec(this.#root, result);
    return result;
  }

  inorder_itr() {
    if (this.is_empty()) return [];

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

  postorder_rec() {
    const result = [];
    this.#postorder_rec(this.#root, result);
    return result;
  }

  postorder_itr() {
    if (this.is_empty()) return [];

    const stack1 = [this.#root];
    const stack2 = [];

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
  /* ================= AVL Balancing ================= */

  #insert(node, value) {
    if (!node) {
      ++this.size;
      return new Node(value);
    }

    if (value === node.value) {
      return node;
    } else if (node.value > value) {
      node.left = this.#insert(node.left, value);
    } else {
      node.right = this.#insert(node.right, value);
    }

    node.height = this.#updateHeight(node);
    let bf = this.#balanceFactor(node);

    if (bf > 1 && node.left.value > value) {
      return this.#rotateRight(node); // LL Case;
    }

    if (bf > 1 && node.left.value < value) {
      node.left = this.#rotateLeft(node.left); // LR Case;
      return this.#rotateRight(node);
    }

    if (bf < -1 && node.right.value < value) {
      return this.#rotateLeft(node); // RR Case;
    }

    if (bf < -1 && node.right.value > value) {
      node.right = this.#rotateRight(node.right); // RL Case;
      return this.#rotateLeft(node);
    }

    return node;
  }

  #delete(node, value) {
    if (!node) return node;

    if (value < node.value) {
      node.left = this.#delete(node.left, value);
    } else if (value > node.value) {
      node.right = this.#delete(node.right, value);
    } else {
      --this.#size;
      if (!node.left || !node.right) {
        return node.left || node.right;
      }

      let successor = this.#getMin(node.right);
      node.value = successor.value;
      node.right = this.#delete(node.right, successor.value);
    }

    this.#updateHeight(node);
    let bf = this.#balanceFactor(node);

    if (bf > 1 && this.#balanceFactor(node.left) >= 0) {
      return this.#rotateRight(node); // LL Case;
    }

    if (bf > 1 && this.#balanceFactor(node.left) < 0) {
      node.left = this.#rotateLeft(node.left); // LR Case;
      return this.#rotateRight(node);
    }

    if (bf < -1 && this.#balanceFactor(node.right) <= 0) {
      return this.#rotateLeft(node); // RR Case;
    }

    if (bf < -1 && this.#balanceFactor(node.right) > 0) {
      node.right = this.#rotateRight(node.right); // RL Case;
      return this.#rotateLeft(node);
    }

    return node;
  }

  #balanceFactor(node) {
    if (!node) return 0;
    return this.#getHeight(node.left) - this.#getHeight(node.right);
  }

  #getHeight(node) {
    return node ? node.height : 0;
  }

  #updateHeight(node) {
    if (!node) return;
    node.height =
      1 + Math.max(this.#getHeight(node.left), this.#getHeight(node.right));
  }

  #isBalanced(node) {
    if (!node) return true;

    const bf = this.#balanceFactor(node);

    if (bf > 1 || bf < -1) return false;

    return this.#isBalanced(node.left) && this.#isBalanced(node.right);
  }

  #rotateRight(node) {
    let y = node.left;
    node.left = y.right;
    y.right = node;
    this.#updateHeight(node);
    this.#updateHeight(y);
    return y;
  }

  #rotateLeft(node) {
    let y = node.right;
    node.right = y.left;
    y.left = node;
    this.#updateHeight(node);
    this.#updateHeight(y);
    return y;
  }

  /* ================= BST Helpers ================= */

  #getMin(node) {
    if (!node.left) return node;
    return this.#getMin(node.left);
  }

  #getMax(node) {
    if (!node.right) return node;
    return this.#getMax(node.right);
  }

  #search(node, value) {
    if (!node) return false;

    if (node.value === value) {
      return true;
    }

    return this.#search(node.value < value ? node.right : node.left, value);
  }

  /* ================= DFS Helpers ================= */

  #preorder_rec(node, res) {
    if (!node) return;
    res.push(node.value);
    this.#preorder_rec(node.left, res);
    this.#preorder_rec(node.right, res);
  }

  #inorder_rec(node, res) {
    if (!node) return;
    this.#inorder_rec(node.left, res);
    res.push(node.value);
    this.#inorder_rec(node.right, res);
  }

  #postorder_rec(node, res) {
    if (!node) return;
    this.#inorder_rec(node.left, res);
    this.#inorder_rec(node.right, res);
    res.push(node.value);
  }

  /* ================= Advanced AVL Utilities ================= */

  isBalanced() {
    return this.#isBalanced(this.#root);
  }

  findSuccessor(value) {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    let current = this.#root;
    while (current && current.value !== value) {
      current = current.value < value ? current.right : current.left;
    }

    if (!current) {
      throw new Error("Value dont't exist");
    }

    if (current.right) {
      return this.#getMin(current.right);
    }

    let ancestor = null;
    current = this.#root;

    while (current.value !== value) {
      if (current.value > value) {
        ancestor = current;
        current = current.left;
      } else {
        current = current.right;
      }
    }
    return ancestor.value;
  }

  findPredecessor(value) {
    if (this.is_empty()) {
      throw new Error('Tree is empty');
    }

    let current = this.#root;
    while (current && current.value !== value) {
      current = current.value < value ? current.right : current.left;
    }

    if (!current) {
      throw new Error("Value dont't exist");
    }

    if (current.left) {
      return this.#getMax(current.left);
    }

    let ancestor = null;
    current = this.#root;

    while (current.value !== value) {
      if (value > current.value) {
        ancestor = current;
        current = current.right;
      } else {
        current = current.left;
      }
    }
    return ancestor.value;
  }

  toArray() {
    return this.inorder_rec();
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
        }
        return {
          value: undefined,
          done: true,
        };
      },
    };
  }

  *entries() {
    const inorder = this.inorder_rec();
    for (let i = 0; i < inorder.length; ++i) {
      yield [i, inorder[i]];
    }
  }
}