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

const int H = input.grid.size();
const int W = input.grid[0].size();

int dfs(pair<int,int> p, bool dist = false) {
	set<int> done;
	queue<pair<int,int>> q;
	q.push(p);
	int res = 0;
	while (!q.empty()) {
		auto a = q.front();
		q.pop();
		if (input.grid[a.first][a.second] == '9' && (dist || !done.count(a.first * 1000 + a.second))) {
			done.insert(a.first * 1000 + a.second);
			++res;
			continue;
		}
		if (a.first < H-1 && input.grid[a.first+1][a.second] - input.grid[a.first][a.second] == 1) q.push({a.first+1,a.second});
		if (a.first > 0 && input.grid[a.first-1][a.second] - input.grid[a.first][a.second] == 1) q.push({a.first-1,a.second});
		if (a.second < W-1 && input.grid[a.first][a.second+1] - input.grid[a.first][a.second] == 1) q.push({a.first,a.second+1});
		if (a.second > 0 && input.grid[a.first][a.second-1] - input.grid[a.first][a.second] == 1) q.push({a.first,a.second-1});
	}
	return res;
}

ll first() {
	vector<pair<int,int>> heads;
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (input.grid[i][j] == '0') {
				heads.push_back({i,j});
			}
		}
	}

	int res = 0;
	for (auto &p : heads) {
		res += dfs(p);
	}
	return res;
}

ll second() {
	vector<pair<int,int>> heads;
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (input.grid[i][j] == '0') {
				heads.push_back({i,j});
			}
		}
	}

	int res = 0;
	for (auto &p : heads) {
		res += dfs(p, true);
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
