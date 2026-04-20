# Question 3: Arbitrage Detection in Currency Exchange

## a) Model the currency exchange problem as a weighted directed graph

Each currency is a vertex. Each exchange rate r(u,v) from currency u to v is a directed edge with weight r(u,v). Starting with 1 unit of currency A, after a sequence of exchanges A → B → C → A, the final amount is r(A,B) × r(B,C) × r(C,A). Arbitrage exists if this product > 1.

---

## b) Explain how logarithmic transformation of exchange rates converts the problem into a shortest path or cycle detection problem.

Shortest path algorithms work with addition, but exchange rates multiply. Taking the negative log of each rate bridges this gap — multiplying rates becomes adding weights. A profitable cycle (product > 1) becomes a negative-weight cycle (sum < 0). So by setting each edge weight to the negative log of its exchange rate, arbitrage detection turns into finding a negative-weight cycle, which Bellman-Ford handles directly.

---

## c) Identify the algorithm used to detect arbitrage opportunities and justify its use.

Bellman-Ford is used because it directly detects negative weight cycles. Run Bellman-Ford from any source vertex. After V-1 relaxation iterations, perform one more iteration. If any distance can still be reduced, a negative cycle (arbitrage opportunity) exists. Time complexity: O(V × E) where V = number of currencies, E = number of exchange pairs.
