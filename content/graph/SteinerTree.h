/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Minimum Steiner Tree. Finds minimum total edge
 * weight of a subgraph spanning all $k$ given terminals.
 * Time: O(3^k V + 2^k E \log V)
 * Status: tested
 */
#pragma once

typedef pair<int, ll> pil;

ll steinerTree(int n, const vi& terms,
               const vector<vector<pil>>& g) {
	int k = sz(terms);
	if (k <= 1) return 0;
	const ll INF = LLONG_MAX / 3;
	vector<vector<ll>> d(1 << k, vector<ll>(n, INF));
	rep(i,0,k) d[1 << i][terms[i]] = 0;

	rep(mask,1,1 << k) {
		for (int a = (mask - 1) & mask; a > 0; a = (a - 1) & mask) {
			int b = mask ^ a;
			if (b > a) continue;
			rep(v,0,n) d[mask][v] = min(d[mask][v],
			                            d[a][v] + d[b][v]);
		}
		priority_queue<pair<ll, int>, vector<pair<ll, int>>,
		               greater<>> q;
		vector<bool> vis(n, false);
		rep(v,0,n) if (d[mask][v] < INF) q.emplace(d[mask][v], v);

		while (!q.empty()) {
			auto [dist, u] = q.top(); q.pop();
			if (vis[u]) continue;
			vis[u] = true;
			for (auto& [v, w] : g[u]) {
				if (dist + w < d[mask][v]) {
					d[mask][v] = dist + w;
					q.emplace(d[mask][v], v);
				}
			}
		}
	}
	ll res = INF;
	rep(v,0,n) res = min(res, d[(1 << k) - 1][v]);
	return res >= INF ? -1 : res;
}
