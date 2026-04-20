# Assignment 2 — Bitmasking, Graphs, Strings

## Problem Summaries

| File | Question | Topic |
|------|----------|-------|
| `q1_bitmasking.cpp` | Q1 | Subset enumeration + sum divisibility using bitmasking |
| `q2_johnson.md` | Q2 | Johnson's Algorithm — theory |
| `q3_arbitrage.md` | Q3 | Arbitrage detection via log-transform + Bellman-Ford |
| `q4_edmonds.md` | Q4 | Edmonds' Algorithm — minimum spanning arborescence |
| `q5_string_matching.cpp` | Q5 | KMP (LPS array) and Rabin-Karp string matching |

---

## Q1 — Bitmasking

### Approach
Enumerate all `2^N` subsets by iterating `mask` from `0` to `2^N − 1`.  
For each mask, bit `i` set means element `a[i]` is included.  
Compute the sum per subset and check `sum % K == 0`.

### Complexity
| | Time | Space |
|-|------|-------|
| Subset enumeration | O(2ᴺ · N) | O(N) |

### Compile & Run
```bash
g++ q1_bitmasking.cpp -o q1_bitmasking
./q1_bitmasking
```

### Example
```
Enter N: 3
Enter 3 integers: 1 2 3
Enter K: 3

{ }  sum = 0  ✓
{ 1 }  sum = 1
{ 2 }  sum = 2
{ 1 2 }  sum = 3  ✓
{ 3 }  sum = 3  ✓
{ 1 3 }  sum = 4
{ 2 3 }  sum = 5
{ 1 2 3 }  sum = 6  ✓

Total subsets            : 8
Subsets with sum div by 3: 4
```

---

## Q2 — Johnson's Algorithm (Theory)

See [`q2_johnson.md`](q2_johnson.md).

**Key points:**
- Johnson's runs in **O(V · E log V)** vs Floyd-Warshall's O(V³) — much faster for sparse graphs.
- Uses Bellman-Ford once for reweighting, then Dijkstra from every vertex.
- Reweighting formula: `w'(u,v) = w(u,v) + h[u] − h[v]` ensures non-negative weights.

---

## Q3 — Arbitrage Detection (Theory)

See [`q3_arbitrage.md`](q3_arbitrage.md).

**Key points:**
- Model currencies as vertices, exchange rates as directed edge weights.
- Transform: `w'(u,v) = −log(r(u,v))` → arbitrage ↔ negative weight cycle.
- Use **Bellman-Ford** to detect the negative cycle.

---

## Q4 — Edmonds' Algorithm (Theory)

See [`q4_edmonds.md`](q4_edmonds.md).

**Problem:** Find a **Minimum Spanning Arborescence** rooted at a given vertex in a
directed weighted graph — a minimum-cost spanning tree where all edges are directed
away from the root and every vertex is reachable from it.

**Complexity:** O(V · E) naive; O(E + V log V) with Fibonacci heap.

---

## Q5 — String Matching

### Approach

**KMP:**  
1. Build the LPS (Longest Proper Prefix = Suffix) array in O(M).  
2. Search text in O(N) using LPS to avoid redundant comparisons.

**LPS for "ABABCABAB":**
```
Index :  0  1  2  3  4  5  6  7  8
Pattern: A  B  A  B  C  A  B  A  B
LPS   :  0  0  1  2  0  1  2  3  4
```

**Rabin-Karp:**  
1. Compute polynomial rolling hash for the pattern and each text window.  
2. On hash match, do a character-by-character verification (handles spurious hits / collisions).

| Algorithm | Average Time | Worst Time | Space |
|-----------|-------------|------------|-------|
| KMP | O(N + M) | O(N + M) | O(M) |
| Rabin-Karp | O(N + M) | O(N · M) | O(1) |

### Compile & Run
```bash
g++ q5_string_matching.cpp -o q5_string_matching
./q5_string_matching
```

### Example
```
=== Part a: KMP LPS Array ===
Pattern : ABABCABAB
LPS     : 0 0 1 2 0 1 2 3 4

=== KMP Search ===
Enter text   : ABABCABABABABCABAB
Enter pattern: ABABCABAB
LPS array for "ABABCABAB": 0 0 1 2 0 1 2 3 4
KMP: Pattern found at indices: 0 8

=== Rabin-Karp Search (lowercase) ===
Rabin-Karp: Pattern found at indices: 0 8
```
