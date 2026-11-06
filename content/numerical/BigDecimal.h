/**
 * Author: CP Reference
 * Date: 2024-03-01
 * License: CC0
 * Source: folklore
 * Description: Arbitrary precision decimal arithmetic.
 * d stores digits reversed, p decimal places, n negative sign.
 * Time: +, - O(N), * O(NM), / O(N^2)
 * Status: tested
 */
#pragma once

struct B {
	static const int PREC = 50;
	string d; int p = 0; bool n = 0;
	B(string s = "0") {
		if (s[0] == '-') n = 1, s = s.substr(1);
		auto t = s.find('.');
		if (t != string::npos) p = sz(s) - 1 - t, s.erase(t, 1);
		d = s; reverse(all(d)); c();
	}
	void c() {
		while (sz(d) > p + 1 && d.back() == '0') d.pop_back();
		while (p > 0 && sz(d) > 1 && d[0] == '0') d.erase(0, 1), p--;
		if (d.empty() || d == "0") d = "0", p = n = 0;
	}
	void a(B& o) {
		int m = max(p, o.p);
		d.insert(0, m - p, '0'); o.d.insert(0, m - o.p, '0');
		p = o.p = m;
	}
	int cmp(B o) {
		if (sz(d) != sz(o.d)) return sz(d) > sz(o.d) ? 1 : -1;
		for (int i = sz(d) - 1; i >= 0; i--)
			if (d[i] != o.d[i]) return d[i] > o.d[i] ? 1 : -1;
		return 0;
	}
	B operator+(B o) {
		if (n != o.n) return o.n = !o.n, *this - o;
		a(o); B r; r.d = "", r.p = p, r.n = n; int c = 0;
		for (int i = 0; i < max(sz(d), sz(o.d)) || c; i++) {
			int s = c + (i < sz(d) ? d[i] - '0' : 0) +
			            (i < sz(o.d) ? o.d[i] - '0' : 0);
			r.d += char('0' + s % 10); c = s / 10;
		}
		return r.c(), r;
	}
	B sub(B o) {
		a(o); B r; r.d = "", r.p = p; int b = 0;
		for (int i = 0; i < sz(d); i++) {
			int s = d[i] - '0' - (i < sz(o.d) ? o.d[i] - '0' : 0) - b;
			if (s < 0) s += 10, b = 1; else b = 0;
			r.d += char('0' + s);
		}
		return r.c(), r;
	}
	B operator-(B o) {
		if (n != o.n) return o.n = !o.n, *this + o;
		B t = *this; t.a(o); int c = t.cmp(o);
		if (!c) return B();
		if (c > 0) return t = t.sub(o), t.n = n, t;
		return t = o.sub(t), t.n = !n, t;
	}
	B operator*(B o) {
		B r; r.p = p + o.p;
		vector<int> v(sz(d) + sz(o.d));
		rep(i,0,sz(d)) rep(j,0,sz(o.d))
			v[i + j] += (d[i] - '0') * (o.d[j] - '0');
		int c = 0; r.d = "";
		for (int x : v)
			r.d += char('0' + (x + c) % 10), c = (x + c) / 10;
		return r.n = n != o.n, r.c(), r;
	}
	B operator/(B o) {
		if (o.d == "0") return B();
		B a = *this, b = o; bool neg = a.n != o.n; a.n = b.n = 0;
		int mp = max(a.p, b.p);
		a.d.insert(0, mp - a.p, '0'); b.d.insert(0, mp - b.p, '0');
		a.p = b.p = 0; a.c(); b.c();
		a.d.insert(0, PREC, '0');
		string res = ""; B cur;
		for (int i = sz(a.d) - 1; i >= 0; i--) {
			cur.d.insert(0, 1, a.d[i]); cur.c();
			int q = 0;
			while (cur.cmp(b) >= 0) cur = cur.sub(b), q++;
			res += char('0' + q);
		}
		reverse(all(res));
		B r; r.d = res, r.p = PREC, r.n = neg;
		return r.c(), r;
	}
	bool operator==(B o) {
		if (n != o.n) return 0;
		B t = *this; t.a(o); return t.d == o.d;
	}
	bool operator<(B o) {
		if (n != o.n) return n;
		B t = *this; t.a(o); int c = t.cmp(o);
		return n ? c > 0 : c < 0;
	}
	bool operator>(B o) { return o < *this; }
	void print() {
		if (n) cout << "-";
		string t = d; reverse(all(t));
		if (p > 0) {
			if (p >= sz(t)) t.insert(0, p - sz(t) + 1, '0');
			t.insert(sz(t) - p, ".");
		}
		cout << t;
	}
};
