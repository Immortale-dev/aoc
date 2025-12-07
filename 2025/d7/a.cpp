#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(string) lines = UNTIL_END();
};

Input input(std::cin);

void move_down(vector<vector<int>>& grid, int y, int x) {
	if (y >= grid.size() || x < 0 || x > grid[0].size()) return;
	while(y < grid.size()) {
		if (grid[y][x] == 1) break;
		grid[y][x]++;
		if (grid[y][x] == 3) {
			move_down(grid, y, x-1);
			move_down(grid, y, x+1);
			break;
		}
		y++;
	}
}

ll first() {
	int H = input.lines.size();
	int W = input.lines[0].size();
	int y,x;
	vector<vector<int>> grid(H, vector<int>(W, 0));
	for (size_t i=0;i<H;i++) {
		for (size_t j=0;j<W;j++) {
			char c = input.lines[i][j];
			if (c == 'S') {
				y = y;
				x = j;
			}
			if (c == '^') {
				grid[i][j] = 2;
			}
		}
	}
	move_down(grid, y, x);
	int res = 0;
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (grid[i][j] == 3) res++;
		}
	}
	return res;
}

ll move_down_q(vector<vector<ll>>& grid, int y, int x, ll& res) {
	if (y >= grid.size() || x < 0 || x > grid[0].size()) return 0;
	while(y < grid.size()) {
		if (grid[y][x] > 0) {
			res += grid[y][x];
			return grid[y][x];
		}
		if (grid[y][x] == -1) {
			grid[y][x] = move_down_q(grid, y, x-1, res) + move_down_q(grid, y, x+1, res);
			return grid[y][x];
		}
		y++;
	}
	res++;
	return 1;
}

ll second() {
	int H = input.lines.size();
	int W = input.lines[0].size();
	int y,x;
	vector<vector<ll>> grid(H, vector<ll>(W, 0));
	for (size_t i=0;i<H;i++) {
		for (size_t j=0;j<W;j++) {
			char c = input.lines[i][j];
			if (c == 'S') {
				y = i;
				x = j;
			}
			if (c == '^') {
				grid[i][j] = -1;
			}
		}
	}
	ll res = 0;
	move_down_q(grid, y, x, res);
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
