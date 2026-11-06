/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Min-heap Cartesian Tree in linear time. In-order
 * traversal gives indices 0..n-1. LCA(u, v) is range min in [u, v].
 * Time: O(N)
 * Status: tested
 */
#pragma once

template<class T>
struct CartesianTree {
	vi l, r, p;
	int root = -1;
	CartesianTree(const vector<T>& a) {
		int n = sz(a);
		l.assign(n, -1); r.assign(n, -1); p.assign(n, -1);
		vi st;
		rep(i,0,n) {
			int last = -1;
			while (!st.empty() && a[st.back()] > a[i]) {
				last = st.back();
				st.pop_back();
			}
			if (last != -1) l[i] = last, p[last] = i;
			if (!st.empty()) r[st.back()] = i, p[i] = st.back();
			st.push_back(i);
		}
		if (!st.empty()) root = st[0];
	}
};
