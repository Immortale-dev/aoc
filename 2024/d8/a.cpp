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

const int ROWS = input.grid.size();
const int COLS = input.grid[0].size();

vector<vector<bool>> occurs(ROWS, vector(COLS, false));
unordered_map<char, vector<pair<int,int>>> pos;

void prepare() {
	for (int i=0;i<ROWS;++i) {
		for (int j=0;j<COLS;++j) {
			char c = input.grid[i][j];
			if (c != '.') {
				pos[c].push_back({i,j});
			}
		}
	}
}

ll first() {
	for (auto &tt : pos) {
		vector<pair<int,int>> &t = tt.second;
		for (int i=0;i<t.size();i++) {
			for (int j=0;j<t.size();j++) {
				if (i == j) continue;
				pair<int,int> a = t[i];
				pair<int,int> b = t[j];
				int dr = a.first - b.first;
				int dc = a.second - b.second;
				int r = a.first + dr;
				int c = a.second + dc;
				if (r < 0 || c < 0 || r >= ROWS || c >= COLS) continue;
				occurs[r][c] = true;
			}
		}
	}
	int res = 0;
	for (int i=0;i<ROWS;++i) {
		for (int j=0;j<COLS;++j) {
			res += occurs[i][j];
		}
	}
	return res;
}

ll second() {
	for (auto &tt : pos) {
		vector<pair<int,int>> &t = tt.second;
		for (int i=0;i<t.size();i++) {
			for (int j=0;j<t.size();j++) {
				if (i == j) continue;
				pair<int,int> a = t[i];
				pair<int,int> b = t[j];
				int dr = a.first - b.first;
				int dc = a.second - b.second;
				while(a.first >= 0 && a.second >=0 && a.first < ROWS && a.second < COLS) {
					occurs[a.first][a.second] = true;
					a = {a.first + dr, a.second + dc};
				}
			}
		}
	}
	int res = 0;
	for (int i=0;i<ROWS;++i) {
		for (int j=0;j<COLS;++j) {
			res += occurs[i][j];
		}
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
