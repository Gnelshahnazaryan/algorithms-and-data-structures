# Graph Data Structure (Adjacency List)

A graph is a data structure that is composed of **vertices (nodes)** and **edges (connections between nodes)**.  
It is used to model **relationships** between pairs of objects.

---

## Features

- Supports **Directed** and **Undirected** graphs
- Efficient **Adjacency List representation**
- Graph traversals (**DFS**, **BFS**)
- Path-related algorithms
- Cycle detection
- Topological Sort (for DAGs)
- Works with **disconnected graphs**

---

# Data Structure Overview

A graph consists of:

- **Vertices (V)** → nodes of the graph
- **Edges (E)** → connections between vertices

---

## Adjacency List Representation

Each vertex stores a list of its neighbors.

```
0 → [1, 2]
1 → [0, 3]
2 → [0]
3 → [1]
```

This can be implemented using:

- Linked List
- Dynamic Array / Vector
- Set / Map (optional)

---

## Core Operations

### Add Edge

Adds a connection between two vertices.

- Directed Graph → `u → v`
- Undirected Graph → `u ↔ v`

---

### Remove Edge

Removes the connection:

- Directed → remove `u → v`
- Undirected → remove both `u → v` and `v → u`

---

## Traversal Algorithms

### DFS (Depth-First Search)

- Explores as far as possible along each branch
- Implemented using recursion or stack

---

### BFS (Breadth-First Search)

- Explores level by level
- Implemented using a queue

---

## Neighbor Access

### Get Neighbors

Returns all adjacent vertices of a given node.

---

## Level-Based Traversal

Find all nodes at a given distance from a starting node.

- Uses **BFS**
- Level = number of edges from the start node

---

## Path Algorithms

### Has Path

Determines if a path exists between two vertices.

---

### Shortest Path (Unweighted Graph)

- Uses **BFS**
- Returns minimum number of edges

---

### All Paths Count

Counts the number of possible paths between two vertices.

- Uses **DFS + Backtracking**

---

## Cycle Detection

### Undirected Graph

- DFS with **parent tracking**

---

### Directed Graph

- Using:
  - DFS + recursion stack
  - or **Kahn’s Algorithm (Topological Sort)**

---

## Topological Sort

Applies only to **Directed Acyclic Graphs (DAGs)**

### Kahn’s Algorithm

- Based on **in-degree**
- Uses a queue
- If not all vertices are processed → cycle exists

---

## Complexity

| Operation        | Time Complexity |
| ---------------- | --------------- |
| Add Edge         | O(1)            |
| Remove Edge      | O(V)            |
| DFS / BFS        | O(V + E)        |
| Topological Sort | O(V + E)        |

---

## Sparse vs Dense Graphs

- **Sparse Graph** → few edges (E << V²) → Adjacency List preferred
- **Dense Graph** → many edges (E ≈ V²) → Adjacency Matrix may be better

---

## Key Concepts

- Graph Representation
- Traversal Techniques
- Backtracking
- Cycle Detection
- Connectivity
- Topological Ordering

---

## Use Cases

- Social Networks
- Maps & Navigation Systems
- Dependency Resolution (build systems)
- Network Routing
- Scheduling problems

---

## Notes

- Vertices are represented as integers starting from 0
- Linked List is used for memory efficiency
- Directed vs Undirected behavior is controlled via isDirected flag

---
