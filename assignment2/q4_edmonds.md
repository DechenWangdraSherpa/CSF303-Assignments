# Question 4: Edmonds' Algorithm

## Problem Solved 
Edmonds’ Algorithm (also called Chu-Liu/Edmonds’ algorithm) solves the Minimum Spanning Arborescence problem: given a weighted directed graph and a designated root vertex r, find a minimum-weight set of directed edges such that there is exactly one directed path from r to every other vertex.

This is the directed graph analogue of the Minimum Spanning Tree problem. Unlike MST algorithms (Kruskal/Prim) which work on undirected graphs, Edmonds’ handles the asymmetry of directed edges.

### Key steps:
1. For each non-root vertex, select the minimum incoming edge.
2. If no cycle forms, these edges form the optimal arborescence.
3. If a cycle forms, contract the cycle into a single supernode, adjust edge weights, and recurse.
4. Expand contracted cycles to recover the final arborescence.

Time complexity: O(EV) naive, O(E + V log V) with Fibonacci heaps.
