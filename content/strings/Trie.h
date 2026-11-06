/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Prefix tree for lowercase alphabet strings.
 * Returns word count or prefix count.
 * Time: O(|S|) for insert and count.
 * Status: tested
 */
#pragma once

struct Trie {
	enum { alpha = 26, first = 'a' };
	struct Node {
		int next[alpha];
		int pass = 0, end = 0;
		Node() { memset(next, -1, sizeof(next)); }
	};
	vector<Node> t;
	Trie() : t(1) {}

	void insert(const string& s) {
		int u = 0;
		for (char c : s) {
			int k = c - first;
			if (t[u].next[k] == -1) {
				t[u].next[k] = sz(t);
				t.emplace_back();
			}
			u = t[u].next[k];
			t[u].pass++;
		}
		t[u].end++;
	}

	int count(const string& s, bool prefix = false) {
		int u = 0;
		for (char c : s) {
			int k = c - first;
			if (t[u].next[k] == -1) return 0;
			u = t[u].next[k];
		}
		return prefix ? t[u].pass : t[u].end;
	}
};
