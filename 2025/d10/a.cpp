#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Button) {
	PARSE_SETUP;
	PARSE(int) bit = SINGLE();
	SKIP(char) = SINGLE();
};

DEFINE_PARSE_INTERFACE(ButtonGroup) {
	PARSE_SETUP;
	SKIP(char) = SINGLE('(');
	PARSE(Button) buttons = THROUGH(' ');
};

DEFINE_PARSE_INTERFACE(Machine) {
	PARSE_SETUP;
	SKIP(char) = THROUGH('[');
	PARSE(char) bits = THROUGH(']');
	PARSE(ButtonGroup) buttons = UNTIL('{');
	SKIP(char) = SINGLE('{');
	PARSE(Button) jolts = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Machine) machines = UNTIL_END();
};

Input input(std::cin);

ll solve_machine(Machine& m) {
	int indicator = 0;
	for (int i=0;i<m.bits.size();i++) {
		if (m.bits[i] == '#') indicator |= (1 << i);
	}

	vector<int> flips;
	for (auto &g : m.buttons) {
		int bits = 0;
		for (auto &b : g.buttons) {
			bits |= (1 << b.bit());
		}
		flips.push_back(bits);
	}

	int lowest = 999999;
	for (int i=0;i<(1 << flips.size())-1;i++) {
		int n = 0;
		int j = 0;
		int cnt = 0;
		while ((1<<j) <= i) {
			if (i & (1 << j)) {
				cnt++;
				n ^= flips[j];
			}
			j++;
		}
		if (n == indicator) lowest = min(lowest, cnt);
	}

	return lowest;
}

ll first() {
	ll res = 0;
	for (auto &m : input.machines) {
		res += solve_machine(m);
	}
	return res;
}

int compute_rank(vector<vector<double>> mat) {
	int rows = mat.size();
	int cols = mat[0].size();
	int rank = 0;
	const double EPS = 1e-9;
	vector<bool> selected(rows, false);
	for (int c=0;c<cols;c++) {
		int r;
		for (r=0;r<rows;r++) {
			if (!selected[r] && abs(mat[r][c]) > EPS) break;
		}
		if (r == rows) continue;
		rank++;
		selected[r] = true;
		for (int nc=c+1;nc<cols;nc++) {
			mat[r][nc] /= mat[r][c];
		}
		for (int nr=0;nr<rows;nr++) {
			if (nr == r || abs(mat[nr][c]) <= EPS) continue;
			for (int nc=c+1;nc<cols;nc++) {
				mat[nr][nc] -= mat[r][nc] * mat[nr][c];
			}
		}
	}
	return rank;
}

bool has_solution(int button, vector<vector<int>>& buttons, vector<int>& leftovers) {
	if (button == buttons.size()) return true;
	vector<vector<double>> mat;
	for (int i=button;i<buttons.size();i++) {
		vector<double> l(leftovers.size(), 0);
		for (auto &n : buttons[i]) {
			l[n] = 1;
		}
		mat.push_back(std::move(l));
	}
	int rank = compute_rank(mat);
	mat.push_back(vector<double>(leftovers.begin(), leftovers.end()));
	return rank == compute_rank(mat);
}

void solve(vector<int>& need, vector<int>& current, vector<vector<int>>& buttons, int& mn, int button, int steps) {
	if (current == need) {
		mn = min(mn, steps);
		return;
	}
	if (steps > mn || button == buttons.size()) return;
	vector<int>& bits = buttons[button];
	int max_press = 500;
	for (int i=0;i<bits.size();i++) {
		int bit = bits[i];
		max_press = min(max_press, need[bit] - current[bit]);
	}
	for (int i=max_press;i>=0;i--) {
		for (int j=0;j<bits.size();j++) {
			int bit = bits[j];
			current[bit] += i;
		}
		vector<int> leftovers;
		for (int i=0;i<need.size();i++) {
			leftovers.push_back(need[i]-current[i]);
		}
		if (has_solution(button+1, buttons, leftovers)) {
			solve(need, current, buttons, mn, button + 1, steps + i);
		}
		for (int j=0;j<bits.size();j++) {
			int bit = bits[j];
			current[bit] -= i;
		}
	}
}

ll solve_machine_jolts(Machine& m) {
	vector<int> need;
	for (auto &b : m.jolts) {
		need.push_back(b.bit());
	}
	vector<int> current(need.size());
	vector<vector<int>> buttons;
	for (auto &g : m.buttons) {
		vector<int> bits;
		for (auto &b : g.buttons) {
			bits.push_back(b.bit());
		}
		buttons.push_back(std::move(bits));
	}
	int mn = 10000;
	solve(need, current, buttons, mn, 0, 0);
	return mn;
}

ll second() {
	ll res = 0;
	int ind = 0;
	for (auto &m : input.machines) {
		res += solve_machine_jolts(m);
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
