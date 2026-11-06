/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Centroid Decomposition of a tree. Recursively finds
 * centroid and solves path queries passing through it in $O(N \log N)$.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

struct CentroidDecomp {
	vector<vi>& adj;
	vector<bool> rem;
	vi sub;
	int tree_sz;

	CentroidDecomp(vector<vi>& g) : adj(g), rem(sz(g)), sub(sz(g)) {}

	int get_sz(int u, int p = -1) {
		sub[u] = 1;
		for (int v : adj[u]) if (v != p && !rem[v])
			sub[u] += get_sz(v, u);
		return sub[u];
	}

	int get_centroid(int u, int p = -1) {
		for (int v : adj[u]) if (v != p && !rem[v])
			if (sub[v] * 2 > tree_sz) return get_centroid(v, u);
		return u;
	}

	void solve_paths(int c) {
		// DFS de solucion: procesar caminos que pasan por c
		for (int v : adj[c]) if (!rem[v]) {
			// dfs_query(v, c, ...);
			// dfs_add(v, c, ...);
		}
	}

	void build(int u = 0, int p_centroid = -1) {
		tree_sz = get_sz(u);
		int c = get_centroid(u);
		solve_paths(c);
		rem[c] = true;
		for (int v : adj[c]) if (!rem[v])
			build(v, c);
	}
};
