# Assignment 1 — STL, Bellman-Ford, Floyd-Warshall

## Problem Summaries

| File | Question | Topic |
|------|----------|-------|
| `q1_stl.cpp` | Q1 | STL containers: `vector`, `deque`, `std::array` |
| `q2_bellman_ford.cpp` | Q2 | Single-source shortest paths + negative cycle detection |
| `q3_floyd_warshall.cpp` | Q3 | All-pairs shortest paths + negative cycle detection |

---

## Q1 — STL Usage

### Approach
- **Part a** — Fill a `vector<int>` and traverse with `rbegin()`/`rend()` reverse iterators.  
- **Part b** — Use a `deque<int>` to simulate push_front, push_back, pop_front operations.  
- **Part c** — Use `std::array<int, 5>` with `std::accumulate` from `<numeric>` for the sum.

### Compile & Run
```bash
g++ q1_stl.cpp -o q1_stl 
./q1_stl
```

### Example
```
[Part a] Enter N: 5
Enter 5 integers: 10 20 30 40 50
Reversed: 50 40 30 20 10

[Part b] Enter number of operations: 4
1 5
2 3
3
1 9
Deque contents: 5 9

[Part c] Enter 5 integers: 1 2 3 4 5
Sum of array elements = 15
```

---

## Q2 — Bellman-Ford Algorithm

### Approach
1. Initialise `dist[src] = 0`, all others `= INF`.  
2. Relax all edges **(V − 1)** times — guarantees correctness if no negative cycle.  
3. Perform one more relaxation pass; any improvement signals a **negative weight cycle**.

### Complexity
| | Time | Space |
|-|------|-------|
| Bellman-Ford | O(V · E) | O(V + E) |

### Compile & Run
```bash
g++ q2_bellman_ford.cpp -o q2_bellman_ford
./q2_bellman_ford
```

### Example (no negative cycle)
```
Enter V and E: 5 8
Enter each edge as: u v w
0 1 -1
0 2  4
1 2  3
1 3  2
1 4  2
3 2  5
3 1  1
4 3 -3
Enter source vertex: 0

Shortest distances from source vertex 0:
  Vertex 0 : 0
  Vertex 1 : -1
  Vertex 2 : 2
  Vertex 3 : -2
  Vertex 4 : 1
```

---

## Q3 — Floyd-Warshall Algorithm

### Approach
1. Build a `V×V` distance matrix initialised to `INF` (0 on diagonal).  
2. Run the three-nested-loop DP: `dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j])`.  
3. After the loops, check `dist[i][i] < 0` for any `i` — indicates a negative cycle.

### Why it works with negative edges
Floyd-Warshall uses dynamic programming without greedy selection, so negative weights are handled correctly. It simply picks the minimum path through every possible intermediate vertex, regardless of edge sign.

### Why it fails with negative cycles
A path through a negative cycle can be made arbitrarily short (−∞). While the algorithm detects the cycle via `dist[i][i] < 0`, it cannot return finite shortest paths for vertices reachable through that cycle.

### Complexity
| | Time | Space |
|-|------|-------|
| Floyd-Warshall | O(V³) | O(V²) |

### Compile & Run
```bash
g++ q3_floyd_warshall.cpp -o q3_floyd_warshall
./q3_floyd_warshall
```

### Example
```
Enter V and E: 4 5
0 1 3
0 3 7
1 0 8
1 2 2
3 0 2

All-pairs shortest path distance matrix:
       [0]  [1]  [2]  [3]
[0]     0    3    5    7
[1]     8    0    2   15
[2]   INF  INF    0  INF
[3]     2    5    7    0
```
