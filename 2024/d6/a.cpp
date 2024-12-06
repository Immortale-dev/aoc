#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(string) grid = UNTIL_END();
};

Input input(std::cin);

struct GuardPos {
	int row, col, pos;
};

GuardPos getPos() {
	unordered_map<int,int> m{{'^', 0}, {'>', 1}, {'v', 2}, {'<', 3}};
	for (int i=0;i<input.grid.size();++i) {
		for (int j=0;j<input.grid[i].size();++j) {
			char ch = input.grid[i][j];
			if (m.count(ch)) {
				return {i,j,m[ch]};
			}
		}
	}
	assert(false);
	return {};
}

bool nextPos(GuardPos &pos) {
	int row = pos.row;
	int col = pos.col;
	if (pos.pos == 0) --row;
	if (pos.pos == 1) ++col;
	if (pos.pos == 2) ++row;
	if (pos.pos == 3) --col;
	if (row < 0 || col < 0 || row >= input.grid.size() || col >= input.grid[0].size()) return false;
	if (input.grid[row][col] == '#') {
		pos.pos = (pos.pos + 1)%4;
		return true;
	}
	pos.row = row;
	pos.col = col;
	return true;
}

ll first() {
	vector<vector<int>> visited(input.grid.size(), vector<int>(input.grid[0].size(), 0));
	GuardPos pos = getPos();
	do {
		visited[pos.row][pos.col] = 1;
	} while(nextPos(pos));
	int res = 0;
	for (int i=0;i<visited.size();++i) {
		for (int j=0;j<visited[i].size();++j) {
			res += visited[i][j];
		}
	}
	return res;
}

ll second() {
	GuardPos initial_pos = getPos();
	int res = 0;
	for (int i=0;i<input.grid.size();++i) {
		for (int j=0;j<input.grid[i].size();++j) {
			if (input.grid[i][j] != '.') continue;
			input.grid[i][j] = '#';
			vector<vector<char>> visited(input.grid.size(), vector<char>(input.grid[0].size(), 0));
			auto pos = initial_pos;
			do {
				int index = 1 << pos.pos;
				if (visited[pos.row][pos.col] & index) {
					++res;
					break;
				}
				visited[pos.row][pos.col] |= index;
			} while(nextPos(pos));
			input.grid[i][j] = '.';
		}
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
