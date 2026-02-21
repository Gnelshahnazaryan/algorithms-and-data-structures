const Deque = require('../../Deque/JS/deque.js');

class Stack {
    constructor(capacity = 8) {
        this.deque = new Deque(capacity);
    }

    push(value) {
        this.deque.push_back(value);
    }

    pop() {
        return this.deque.pop_back();
    }

    peek() {
        return this.deque.back();
    }

    isEmpty() {
        return this.deque.empty();
    }

    size() {
        return this.deque.size();
    }
}