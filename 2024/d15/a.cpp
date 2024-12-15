#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

const int H = 50;

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(string) grid = COUNT(H);
	PARSE(string) moves = UNTIL_END();
};

Input input(std::cin);

const vector<pair<int,int>> dirs = {{0,-1}, {1,0}, {0,1}, {-1,0}};

bool move(int x, int y, vector<string> &grid, int dir) {
	auto [mx,my] = dirs[dir];
	char c = grid[y+my][x+mx];
	if (c == '#') return false;
	if (c == 'O') move(x+mx, y+my, grid, dir);
	if (grid[y+my][x+mx] == '.') {
		swap(grid[y][x], grid[y+my][x+mx]);
		return true;
	}
	return false;
}

ll first() {
	vector<string> grid(input.grid.begin(), input.grid.end());
	vector<int> moves;
	for (auto &s : input.moves) {
		for (auto c : s) {
			if (c == '^') moves.push_back(0);
			else if (c == '>') moves.push_back(1);
			else if (c == 'v') moves.push_back(2);
			else if (c == '<') moves.push_back(3);
			else assert(false);
		}
	}
	int px=-1,py=-1;
	for (int i=0;i<input.grid.size();i++) {
		for (int j=0;j<input.grid[0].size();j++) {
			if (input.grid[i][j] == '@') {
				px = j;
				py = i;
			}
		}
	}
	assert(px >= 0 && py >= 0);
	for (int m : moves) {
		if (move(px, py, grid, m)) {
			auto [mx, my] = dirs[m];
			px += mx;
			py += my;
		}
	}
	ll res = 0;
	for (int i=0;i<input.grid.size();i++) {
		for (int j=0;j<input.grid[0].size();j++) {
			if (input.grid[i][j] == 'O') {
				res += i*100 + j;
			}
		}
	}
	return res;
}

bool can_move_v(int x, int y, vector<string> &grid, int dir) {
	auto [mx,my] = dirs[dir];
	char tc = grid[y][x];
	if (tc == '.') return true;
	if (tc == '#') return false;
	if (tc == '@') {
		return can_move_v(x+mx,y+my,grid,dir);
	}
	if (tc == '[') {
		return can_move_v(x+mx, y+my, grid, dir) && can_move_v(x+mx+1, y+my, grid, dir);
	}
	if (tc == ']') {
		return can_move_v(x+mx, y+my, grid, dir) && can_move_v(x+mx-1, y+my, grid, dir);
	}
	assert(false);
}

bool move2(int x, int y, vector<string> &grid, int dir, bool check=true) {
	auto [mx,my] = dirs[dir];
	char c = grid[y+my][x+mx];
	if (c == '#') return false;
	if (dir == 1 || dir == 3) {
		if (c == '[' || c == ']') {
			move2(x+mx, y+my, grid, dir);
		}
		if (grid[y+my][x+mx] == '.') {
			swap(grid[y][x], grid[y+my][x+mx]);
			return true;
		}
		return false;
	}
	bool robot = grid[y][x] == '@';
	char tc = grid[y][x];
	if (!check || can_move_v(x,y,grid,dir)) {
		if (c == '[') {
			move2(x+mx, y+my, grid, dir, false);
			move2(x+mx+1, y+my, grid, dir, false);
		} else if(c == ']') {
			move2(x+mx, y+my, grid, dir, false);
			move2(x+mx-1, y+my, grid, dir, false);
		}
		swap(grid[y][x], grid[y+my][x+mx]);
		return true;
	}
	return false;
}

void print_grid(vector<string>& grid) {
	cout << endl;
	for (auto s : grid) {
		cout << s << endl;
	}
}

ll second() {
	vector<string> new_grid;
	for (auto &s : input.grid) {
		string ns;
		for (auto c : s) {
			if (c == '#') {
				ns += "##";
			} else if (c == '.') {
				ns += "..";
			} else if (c == '@') {
				ns += "@.";
			} else if (c == 'O') {
				ns += "[]";
			}
		}
		new_grid.push_back(ns);
	}
	vector<int> moves;
	for (auto &s : input.moves) {
		for (auto c : s) {
			if (c == '^') moves.push_back(0);
			else if (c == '>') moves.push_back(1);
			else if (c == 'v') moves.push_back(2);
			else if (c == '<') moves.push_back(3);
			else assert(false);
		}
	}
	int px=-1,py=-1;
	for (int i=0;i<new_grid.size();i++) {
		for (int j=0;j<new_grid[0].size();j++) {
			if (new_grid[i][j] == '@') {
				px = j;
				py = i;
			}
		}
	}
	assert(px >= 0 && py >= 0);

	int ind=0;
	for (int m : moves) {
		if (move2(px, py, new_grid, m)) {
			#ifdef ANIMATE
			#define PRINT
			print_grid(new_grid);
			cout << (++ind) << " / " << moves.size() << endl;
			this_thread::sleep_for(chrono::milliseconds(30));
			cout << "\033["<<(H+2)<<"A";
			#endif
			auto [mx, my] = dirs[m];
			px += mx;
			py += my;
		}
	}

	#ifdef PRINT
	print_grid(new_grid);
	#endif

	ll res = 0;
	for (int i=0;i<new_grid.size();i++) {
		for (int j=0;j<new_grid[0].size();j++) {
			if (new_grid[i][j] == '[') {
				res += i*100 + j;
			}
		}
	}

	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
