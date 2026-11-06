/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Game Theory cheat sheet and algorithms for impartial
 * games (normal play: last to move wins).
 * Any game is a directed graph where nodes = states, edges = moves.
 * In practice, transitions can be evaluated on the fly.
 * Nim sum: $X = \bigoplus a_i$. Win $\iff X \ne 0$. Move: choose $a_i$
 * with $a_i \oplus X < a_i$, change to $a_i \oplus X$.
 * Misere Nim: if all $a_i \le 1$, win $\iff$ count of 1s is even
 * ($X = 0$). Otherwise play like normal Nim.
 * Sprague-Grundy theorem: $g(G) = \bigoplus g(G_i)$. Win $\iff g(G) \ne 0$.
 * $g(u) = \text{mex}(\{g(v) \mid u \to v\})$. Terminal has $g = 0$.
 * Time: mex: O(|v|), solve_game: O(V + E)
 * Status: tested
 */
#pragma once

// 1. MEX (Minimum Excluded Value) en O(|v|)
int mex(const vi& v) {
	vector<bool> seen(sz(v) + 1);
	for (int x : v) if (x <= sz(v)) seen[x] = 1;
	int m = 0; while (seen[m]) m++;
	return m;
}

// 2. Grundy sobre la marcha (sin construir grafo explicito):
// Genera los estados alcanzables con las reglas del juego.
// vi memo(N, -1);
int grundy(int n, vi& memo) {
	if (n == 0) return 0; // terminal
	if (memo[n] != -1) return memo[n];
	vi trans;
	// Ejemplo: restar 1, 2 o 5 fichas (adaptar segun el juego):
	for (int take : {1, 2, 5}) {
		if (n >= take) trans.push_back(grundy(n - take, memo));
	}
	return memo[n] = mex(trans);
}

// 3. Retrograde Analysis (Juegos en grafos con ciclos/empate)
// Retorna: 1 = Win (jugador actual gana), -1 = Loss, 0 = Draw
vi solve_game(int n, const vector<vi>& adj) {
	vector<vi> radj(n);
	vi deg(n), state(n, 0);
	queue<int> q;
	rep(u,0,n) {
		deg[u] = sz(adj[u]);
		for (int v : adj[u]) radj[v].push_back(u);
		if (deg[u] == 0) state[u] = -1, q.push(u); // terminal
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int p : radj[u]) {
			if (state[p]) continue;
			if (state[u] == -1) {
				state[p] = 1; q.push(p); // va a Loss -> Win
			} else if (--deg[p] == 0) {
				state[p] = -1; q.push(p); // todos van a Win -> Loss
			}
		}
	}
	return state;
}
