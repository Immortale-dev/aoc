#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Item) {
	PARSE_SETUP;
	PARSE(int) val = SINGLE();
	SKIP(char) = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	SKIP(char) = THROUGH(':');
	PARSE(int) a = SINGLE();
	SKIP(char) = THROUGH(':');
	PARSE(int) b = SINGLE();
	SKIP(char) = THROUGH(':');
	PARSE(int) c = SINGLE();
	SKIP(char) = THROUGH(':');
	PARSE(Item) prog = UNTIL_END();
};

Input input(std::cin);

struct Inter {
	Inter(ll a, ll b, ll c, vector<int> prog): a(a), b(b), c(c), prog(prog) {}

	vector<int> run() {
		vector<int> ret;
		while(true) {
			int r = step();
			if (r == -2) return ret;
			if (r >= 0) ret.push_back(r);
		}
		throw logic_error("unreachable");
	}

	int step() {
		if (state >= prog.size()) return -2;
		ll i = prog[state];
		ll lit = prog[state+1];
		state += 2;
		return call(i,lit);
	}

	int call(int i, int lit) {
		switch(i) {
			case 0: adv(get_comb(lit)); return -1;
			case 1: bxl(lit); return -1;
			case 2: bst(get_comb(lit)); return -1;
			case 3: jnz(lit); return -1;
			case 4: bxc(); return -1;
			case 5: return out(get_comb(lit));
			case 6: bdv(get_comb(lit)); return -1;
			case 7: cdv(get_comb(lit)); return -1;
			default: throw logic_error("unreachable");
		}
	}

	void reset() {
		state = a = b = c = 0;
	}

	void adv(ll comb) { a = sdv(a, comb); }
	void bxl(ll lit) { b = b^lit; }
	void bst(ll comb) { b = comb % 8LL; }
	void jnz(ll lit) { if (a != 0) state=lit; }
	void bxc() { b = b^c; }
	int out(ll comb) { return comb % 8LL; }
	void bdv(ll comb) { b = sdv(a, comb); }
	void cdv(ll comb) { c = sdv(a, comb); }

	ll sdv(ll a, ll i) {
		return a / (1 << i);
	}

	ll get_comb(int lit) {
		if (lit == 4) return a;
		if (lit == 5) return b;
		if (lit == 6) return c;
		if (lit >= 7) throw logic_error("unreachable");
		if (lit < 0) throw logic_error("unreachable");
		return lit;
	}

	ll a,b,c;
	vector<int> prog;
	int state = 0;
};

ll first() {
	vector<int> prog;
	for (auto &item : input.prog) {
		prog.push_back(item.val());
	}

	Inter p(input.a(), input.b(), input.c(), prog);

	vector<int> res = p.run();
	for (int i=0;i<res.size();i++) {
		if (i) cout << ",";
		cout << res[i];
	}
	cout << endl;
	return 0;
}

bool veq(vector<int> &a, vector<int> &b) {
	for (int i=0;i<a.size();i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

ll second() {
	vector<int> prog;
	for (auto &item : input.prog) {
		prog.push_back(item.val());
	}

	ll s = pow(8,3);
	ll e = pow(8,4);

	Inter p(input.a(), input.b(), input.c(), prog);
	vector<ll> found = {0};

	for (int step=0;step<=3;step++) {
		vector<ll> new_found;
		for (auto f : found) {
			for (ll i=step ? 0 : s;i<e;i++) {
				ll val = (f << (3*4)) + i;
				p.reset();
				p.a = val;
				vector<int> res = p.run();
				vector<int> prog_res(prog.begin() + (prog.size()-res.size()), prog.end());
				if (veq(prog_res, res)) {
					new_found.push_back(val);
				}
			}
		}
		found = new_found;
	}

	return found[0];
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
