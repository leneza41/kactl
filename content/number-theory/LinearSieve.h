/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Linear sieve (Euler's sieve) computing primes and least
 * prime factor (lp) for each number up to N in linear time.
 * Time: O(N)
 * Status: tested
 */
#pragma once

const int N = 10'000'000;
vector<int> lp(N + 1), pr;

void linearSieve() {
	for (int i = 2; i <= N; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; i * pr[j] <= N; ++j) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i]) break;
		}
	}
}
