# Question 2: Johnson's Algorithm

## a) Why Johnson's Algorithm is More Efficient Than Floyd-Warshall for Sparse Graphs

Floyd-Warshall runs in O(V³) regardless of edge count. Johnson’s runs in O(V² log V + VE) using Dijkstra with a Fibonacci heap for each vertex. For sparse graphs where E ≈ O(V), this becomes O(V² log V), which is significantly faster than O(V³). For dense graphs (E ≈ V²), both are comparable, so Floyd-Warshall is preferred due to simpler implementation.

---

## b) Describe the purpose of edge reweighting and how Bellman-Ford is used in this context.

Johnson’s uses Dijkstra for each source, but Dijkstra cannot handle negative edges. The solution is edge reweighting:

1. Add a new vertex s connected to all vertices with weight 0.
2. Run Bellman-Ford from s to get h(v) = shortest distance from s to v.
3. Reweight each edge: w’(u,v) = w(u,v) + h(u) - h(v).
4. All reweighted edges become non-negative (proven by triangle inequality).
5. Run Dijkstra from each vertex on the reweighted graph.
6. Recover original distances: d(u,v) = d’(u,v) - h(u) + h(v).

Bellman-Ford also detects negative cycles in this step. If one exists, the algorithm reports it and terminates.
