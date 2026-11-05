/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once

typedef uint64_t ull;
static const ull MOD = (1ULL << 61) - 1, C = 1e11 + 3;
struct H {
	ull x;
	H(ull x=0) : x((x >> 61) + (x & MOD)) {
		if (this->x >= MOD) this->x -= MOD; }
	H operator+(H o) const {
		ull v = x + o.x; return {v >= MOD ? v - MOD : v}; }
	H operator-(H o) const {
		return {x >= o.x ? x - o.x : x + MOD - o.x}; }
	H operator*(H o) const {
		__uint128_t m = (__uint128_t)x * o.x;
		ull v = (ull)(m >> 61) + (ull)(m & MOD);
		return {v >= MOD ? v - MOD : v};
	}
	ull get() const { return x; }
	bool operator==(H o) const { return x == o.x; }
	bool operator<(H o) const { return x < o.x; }
};

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}
