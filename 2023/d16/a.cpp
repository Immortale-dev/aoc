#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> grid;

int H,W;

void prepare() {
	string s;
	while(getline(cin, s)){
		grid.push_back(s);
	}
	H = grid.size();
	W = grid[0].size();
}

int LASER_UP = 1;
int LASER_RIGHT = 2;
int LASER_DOWN = 4;
int LASER_LEFT = 8;

vector<int> get_dir(pair<int, int> pos, int dir) {
	int y = pos.first;
	int x = pos.second;
	char c = grid[y][x];
	if (c == '.') return {dir};
	if (c == '/') {
		if (dir == LASER_UP) return {LASER_RIGHT};
		if (dir == LASER_RIGHT) return {LASER_UP};
		if (dir == LASER_DOWN) return {LASER_LEFT};
		if (dir == LASER_LEFT) return {LASER_DOWN};
		throw logic_error("wrong direction");
	}
	if (c == '\\') {
		if (dir == LASER_UP) return {LASER_LEFT};
		if (dir == LASER_RIGHT) return {LASER_DOWN};
		if (dir == LASER_DOWN) return {LASER_RIGHT};
		if (dir == LASER_LEFT) return {LASER_UP};
		throw logic_error("wrong direction");
	}
	if (c == '-') {
		if (dir == LASER_LEFT || dir == LASER_RIGHT) return {dir};
		return {LASER_LEFT, LASER_RIGHT};
	}
	if (c == '|') {
		if (dir == LASER_UP || dir == LASER_DOWN) return {dir};
		return {LASER_UP, LASER_DOWN};
	}
	throw logic_error("wrong grid char");
}

pair<int,int> get_new_pos(pair<int,int> pos, int dir) {
	if (dir == LASER_UP) return {pos.first-1, pos.second};
	if (dir == LASER_DOWN) return {pos.first+1, pos.second};
	if (dir == LASER_LEFT) return {pos.first, pos.second-1};
	if (dir == LASER_RIGHT) return {pos.first, pos.second+1};
	throw logic_error("wrong direction");
}

vector<vector<int>> process_laser(pair<int,int> pos, int dir) {
	vector<vector<int>> dirs(H, vector<int>(W, 0));

	queue<pair<pair<int,int>, int>> q;
	q.push({pos, dir});

	while(!q.empty()) {
		auto a = q.front();
		auto pos = a.first;
		auto dir = a.second;
		q.pop();
		if (pos.first < 0 || pos.first >= H || pos.second < 0 || pos.second >= W) continue;
		if ((dirs[pos.first][pos.second] | dir) == dirs[pos.first][pos.second]) continue;
		dirs[pos.first][pos.second] |= dir;
		for(int d : get_dir(pos, dir)) {
			q.push({get_new_pos(pos, d), d});
		}
	}

	return dirs;
}

int calc_energy(vector<vector<int>>& dirs) {
	int res = 0;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (dirs[i][j] > 0) {
				res++;
			}
		}
	}
	return res;
}

ll first() {
	vector<vector<int>> dirs = process_laser({0,0}, LASER_RIGHT);
	return calc_energy(dirs);
}

ll second() {
	int max_res = 0;
	for(int i=0;i<H;i++) {
		auto dirs = process_laser({i,0}, LASER_RIGHT);
		max_res = max(max_res, calc_energy(dirs));
		dirs = process_laser({i,W-1}, LASER_LEFT);
		max_res = max(max_res, calc_energy(dirs));
	}
	for(int i=0;i<W;i++) {
		auto dirs = process_laser({0, i}, LASER_DOWN);
		max_res = max(max_res, calc_energy(dirs));
		dirs = process_laser({H-1, i}, LASER_UP);
		max_res = max(max_res, calc_energy(dirs));
	}
	return max_res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
