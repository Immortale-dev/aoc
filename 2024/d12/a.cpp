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

void bfs(pair<int,int> pt, Input &input, vector<vector<int>> &regions, vector<int> &areas, vector<int> &perimeters) {
	int ch = input.grid[pt.first][pt.second];
	int id = areas.size();
	areas.push_back(0);
	perimeters.push_back(0);
	queue<pair<int,int>> q;
	q.push(pt);

	while(!q.empty()) {
		auto a = q.front();
		q.pop();
		if (a.first < 0 || a.second < 0 || a.first >= H || a.second >= W || regions[a.first][a.second] >= 0) continue;
		if (input.grid[a.first][a.second] != ch) continue;
		regions[a.first][a.second] = id;
		areas[id]++;
		if (a.first-1 < 0 || input.grid[a.first-1][a.second] != ch) perimeters[id]++;
		if (a.second-1 < 0 || input.grid[a.first][a.second-1] != ch) perimeters[id]++;
		if (a.first+1 >= H || input.grid[a.first+1][a.second] != ch) perimeters[id]++;
		if (a.second+1 >= W || input.grid[a.first][a.second+1] != ch) perimeters[id]++;
		q.push({a.first-1, a.second});
		q.push({a.first+1, a.second});
		q.push({a.first, a.second-1});
		q.push({a.first, a.second+1});
	}
}

void bfs2(pair<int,int> pt, Input &input, vector<vector<int>> &regions, vector<int> &areas, vector<int> &perimeters) {
	int ch = input.grid[pt.first][pt.second];
	int id = areas.size();
	areas.push_back(0);
	perimeters.push_back(0);
	queue<pair<int,int>> q;
	q.push(pt);

	while(!q.empty()) {
		auto a = q.front();
		q.pop();
		if (a.first < 0 || a.second < 0 || a.first >= H || a.second >= W || regions[a.first][a.second] >= 0) continue;
		if (input.grid[a.first][a.second] != ch) continue;
		regions[a.first][a.second] = id;
		areas[id]++;

		auto& grid = input.grid;

		if ((a.first-1 < 0 || grid[a.first-1][a.second] != ch) && (a.second-1 < 0 || grid[a.first][a.second-1] != ch)) perimeters[id]++;
		if ((a.first+1 >= H || grid[a.first+1][a.second] != ch) && (a.second-1 < 0 || grid[a.first][a.second-1] != ch)) perimeters[id]++;
		if ((a.first-1 < 0 || grid[a.first-1][a.second] != ch) && (a.second+1 >= W || grid[a.first][a.second+1] != ch)) perimeters[id]++;
		if ((a.first+1 >= H || grid[a.first+1][a.second] != ch) && (a.second+1 >= W || grid[a.first][a.second+1] != ch)) perimeters[id]++;

		if (a.first-1 >= 0 && a.second-1 >= 0 && grid[a.first-1][a.second] == ch && grid[a.first][a.second-1] == ch && grid[a.first-1][a.second-1] != ch) perimeters[id]++;
		if (a.first+1 < H && a.second-1 >= 0 && grid[a.first+1][a.second] == ch && grid[a.first][a.second-1] == ch && grid[a.first+1][a.second-1] != ch) perimeters[id]++;
		if (a.first-1 >= 0 && a.second+1 < W && grid[a.first-1][a.second] == ch && grid[a.first][a.second+1] == ch && grid[a.first-1][a.second+1] != ch) perimeters[id]++;
		if (a.first+1 < H && a.second+1 < W && grid[a.first+1][a.second] == ch && grid[a.first][a.second+1] == ch && grid[a.first+1][a.second+1] != ch) perimeters[id]++;

		q.push({a.first-1, a.second});
		q.push({a.first+1, a.second});
		q.push({a.first, a.second-1});
		q.push({a.first, a.second+1});
	}
}

ll first() {
	vector<vector<int>> regions(H, vector<int>(W, -1));
	vector<int> areas;
	vector<int> perimeters;
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (regions[i][j] < 0) {
				bfs({i,j}, input, regions, areas, perimeters);
			}
		}
	}

	ll res = 0;
	for (int i=0;i<areas.size();i++) {
		res += (ll)areas[i] * perimeters[i];
	}
	return res;
}

ll second() {
	vector<vector<int>> regions(H, vector<int>(W, -1));
	vector<int> areas;
	vector<int> perimeters;
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (regions[i][j] < 0) {
				bfs2({i,j}, input, regions, areas, perimeters);
			}
		}
	}

	ll res = 0;
	for (int i=0;i<areas.size();i++) {
		res += (ll)areas[i] * perimeters[i];
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
