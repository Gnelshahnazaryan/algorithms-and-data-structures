class Node {
  constructor(value, next = null) {
    this.value = value;
    this.next = next;
  }
}

class GraphAdjList {
  #list;

  constructor(numVertices, isDirected = false) {
    this.numVertices = numVertices;
    this.isDirected = isDirected;
    this.#list = new Array(numVertices).fill(null);
  }

  /* ================= Add / Remove ================= */

  addEdge(u, v) {
    let vNode = new Node(v);
    vNode.next = this.#list[u];
    this.#list[u] = vNode;

    if (!this.isDirected) {
      let uNode = new Node(u);
      uNode.next = this.#list[v];
      this.#list[v] = uNode;
    }
  }

  removeEdge(u, v) {
    let prev = null;
    let current = this.#list[u];

    while (current) {
      if (current.value === v) {
        if (!prev) {
          this.#list[u] = current.next;
          current.next = null;
          break;
        }

        prev.next = current.next;
        current.next = null;
        break;
      }
      prev = current;
      current = current.next;
    }

    if (!this.isDirected) {
      prev = null;
      current = this.#list[v];

      while (current) {
        if (current.value === u) {
          if (!prev) {
            this.#list[v] = current.next;
            current.next = null;
            break;
          }

          prev.next = current.next;
          current.next = null;
          break;
        }
        prev = current;
        current = current.next;
      }
    }
  }

  /* ================= Traversals ================= */

  dfs() {
    const visited = new Array(this.numVertices).fill(false);
    const res = [];

    for (let v = 0; v < this.numVertices; ++v) {
      if (!visited[v]) {
        this.#dfs(v, visited, res);
      }
    }

    return res;
  }

  bfs() {
    const visited = new Array(this.numVertices).fill(false);
    const res = [];

    for (let v = 0; v < this.numVertices; ++v) {
      if (!visited[v]) {
        this.#bfs(v, visited, res);
      }
    }
    return res;
  }

  getNeighbors(u) {
    let current = this.#list[u];
    let res = [];

    while (current) {
      res.push(current.value);
      current = current.next;
    }

    return res;
  }

  getNodesInLevel(start, level) {
    let visited = new Array(this.numVertices).fill(false);
    let queue = [start];
    visited[start] = true;

    let currentLevel = 0;

    while (queue.length) {
      let size = queue.length;

      if (currentLevel === level) {
        return [...queue];
      }

      let nextQueue = [];

      for (let i = 0; i < size; i++) {
        let node = queue[i];

        let current = this.#list[node];
        while (current) {
          let neighbor = current.value;

          if (!visited[neighbor]) {
            visited[neighbor] = true;
            nextQueue.push(neighbor);
          }

          current = current.next;
        }
      }

      queue = nextQueue;
      currentLevel++;
    }

    return [];
  }

  /* ================= Path Algorithms / Shortest Path ================= */

  hasPath(src, dst) {
    let visited = new Array(this.numVertices).fill(false);
    return this.#hasPath(src, dst, visited);
  }

  shortestPath(src, dst) {
    let visited = new Array(this.numVertices).fill(false);

    const queue = [src];

    visited[src] = true;
    let lvl = 1;
    while (queue.length) {
      let size = queue.length;
      while (size--) {
        src = queue.shift();

        let current = this.#list[src];
        while (current) {
          if (!visited[current.value]) {
            if (current.value === dst) return lvl + 1;
            queue.push(current.value);
            visited[current.value] = true;
          }
          current = current.next;
        }
      }
      ++lvl;
    }
    return lvl;
  }

  getAllPathsCount(src, dest) {
    let visited = new Array(this.numVertices).fill(false);
    let count = 0;

    const dfs = (u) => {
      if (u === dest) {
        count++;
        return;
      }

      visited[u] = true;

      let current = this.#list[u];
      while (current) {
        let v = current.value;

        if (!visited[v]) {
          dfs(v);
        }

        current = current.next;
      }

      visited[u] = false;
    };

    dfs(src);
    return count;
  }

  /* ================= Cycle Detection ================= */

  hasCycle() {
    if (!this.isDirected) {
      let visited = new Array(this.numVertices).fill(false);

      for (let u = 0; u < this.numVertices; ++u) {
        if (!visited[u]) {
          if (this.#hasCycleUndirected(u, -1, visited)) {
            return true;
          }
        }
      }
      return false;
    }

    try {
      this.topologicalSortKahn();
    } catch (e) {
      return true;
    }
    return false;
  }

  /* ================= Topological Sort ================= */

  topologicalSortKahn() {
    let inDegree = new Array(this.numVertices).fill(0);
    let topSort = [];
    let queue = [];

    for (let u = 0; u < this.numVertices; ++u) {
      let current = this.#list[u];
      while (current) {
        ++inDegree[current.value];
        current = current.next;
      }
    }

    let tmp = null;

    for (let u = 0; u < inDegree.length; ++u) {
      if (inDegree[u] === 0) queue.push(u);
    }

    while (queue.length) {
      tmp = queue.shift();
      topSort.push(tmp);

      let current = this.#list[tmp];
      while (current) {
        --inDegree[current.value];
        if (inDegree[current.value] === 0) {
          queue.push(current.value);
        }
        current = current.next;
      }
    }

    if (topSort.length !== this.numVertices) {
      throw new Error('Graph has cycle');
    }

    return topSort;
  }

  /* ================= Debug / Vizualization ================= */

  print() {
    for (let i = 0; i < this.numVertices; i++) {
      let current = this.#list[i];
      let output = `${i} -> `;

      while (current) {
        output += `${current.value} -> `;
        current = current.next;
      }

      output += 'null';
      console.log(output);
    }
  }

  /* ================= Helpers / Private Methods ================= */

  #dfs(u, visited, res) {
    visited[u] = true;
    res.push(u);

    let current = this.#list[u];
    while (current) {
      if (!visited[current.value]) {
        this.#dfs(current.value, visited, res);
      }
      current = current.next;
    }
  }

  #bfs(u, visited, res) {
    const queue = [u];
    visited[u] = true;

    while (queue.length) {
      u = queue.shift();
      res.push(u);

      let current = this.#list[u];
      while (current) {
        if (!visited[current.value]) {
          queue.push(current.value);
          visited[current.value] = true;
        }
        current = current.next;
      }
    }
  }

  #hasPath(src, dst, visited) {
    if (src === dst) return true;
    visited[src] = true;

    let current = this.#list[src];
    while (current) {
      if (!visited[current.value]) {
        if (this.#hasPath(current.value, dst, visited)) {
          return true;
        }
      }
      current = current.next;
    }

    return false;
  }

  #hasCycleUndirected(u, prev, visited) {
    visited[u] = true;

    let current = this.#list[u];
    while (current) {
      if (current.value !== prev) {
        if (visited[current.value]) return true;
        if (this.#hasCycleUndirected(current.value, u, visited)) {
          return true;
        }
      }
      current = current.next;
    }
    return false;
  }
}
