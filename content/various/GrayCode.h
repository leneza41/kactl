/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Gray code converts an integer $n$ to a binary
 * representation where adjacent numbers differ by only 1 bit.
 * Includes direct formulas, iterative and recursive generation.
 * The bit that flips between $i-1$ and $i$ is $\text{ctz}(i)$.
 * Time: O(1) for conversion, O(2^k) for sequence
 * Status: tested
 */
#pragma once

// Convierte n a su codigo Gray en O(1)
int gray(int n) { return n ^ (n >> 1); }

// Convierte codigo Gray g de regreso a entero en O(log bits)
int inv_gray(int g) {
	int n = 0;
	for (; g; g >>= 1) n ^= g;
	return n;
}

// 1. Generacion iterativa directa O(2^k):
vi gray_codes(int k) {
	vi res(1 << k);
	rep(i,0,1 << k) res[i] = gray(i);
	return res;
}

// 2. Generacion recursiva (reflejo con bit n-1 encendido):
vi gray_rec(int n) {
	if (n == 0) return {0};
	vi res = gray_rec(n - 1);
	for (int i = sz(res) - 1; i >= 0; --i)
		res.push_back((1 << (n - 1)) | res[i]);
	return res;
}
