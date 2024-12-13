#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Case) {
	PARSE_SETUP;
	SKIP(char) = THROUGH('+');
	PARSE(ll) ax = SINGLE();
	SKIP(char) = THROUGH('+');
	PARSE(ll) ay = SINGLE();
	SKIP(char) = THROUGH('+');
	PARSE(ll) bx = SINGLE();
	SKIP(char) = THROUGH('+');
	PARSE(ll) by = SINGLE();
	SKIP(char) = THROUGH('=');
	PARSE(ll) x = SINGLE();
	SKIP(char) = THROUGH('=');
	PARSE(ll) y = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Case) cases = UNTIL_END();
};

Input input(std::cin);

ll C = 10000000000000LL;

ll solve_case2(Case &c, ll add = 0) {
	// c.axX + c.bxY = c.x } | * c.by
	// c.ayX + c.byY = c.y } | * -c.bx

	// c.axX*c.by + c.bx*c.by*Y = c.x*c.by    } | +
	// -c.ayX*c.bx - c.by*c.bx*Y = -c.y*c.bx  } | +

	// c.ax*c.by*X - c.ay*c.bx*X = c.x*c.by - c.y*c.bx

	// X = (c.x*c.by - c.y*c.bx) / (c.ax*c.by - c.ay*c.bx);
	// Y = (c.x - c.ax*X) / c.bx;

	ll cx = c.x() + add;
	ll cy = c.y() + add;
	ll a = (cx * c.by() - cy * c.bx());
	ll b = (c.ax() * c.by() - c.ay() * c.bx());
	if (a % b) return 0;
	ll X = a / b;

	a = (cx - c.ax() * X);
	b = c.bx();
	if (a % b) return 0;
	ll Y = a / b;

	return X * 3LL + Y;
}

ll first() {
	ll res = 0;
	for (auto &c : input.cases) {
		res += solve_case2(c);
	}
	return res;
}

ll second() {
	ll res = 0;
	for (auto &c : input.cases) {
		res += solve_case2(c, C);
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
