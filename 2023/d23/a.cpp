#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> grid;

int H,W;

struct Pt {
	int y,x;
};

void prepare() {
	string s;
	while(getline(cin, s)){
		grid.push_back(s);
	}
	H = grid.size();
	W = grid[0].size();
}

void print_visited(vector<vector<bool>>& visited) {
	cout << endl;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			cout << (visited[i][j] ? 'O' : '.');
		}
		cout << endl;
	}
}

int find_longest(Pt pos, vector<string>& grid, vector<vector<int>>& saved, vector<vector<bool>> visited, bool slippery) {
	int res = -1;
	Pt p = pos;
	while(true) {
		assert(p.y >= 0 && p.y < H && p.x >= 0 && p.x < W);
		res++;
		visited[p.y][p.x] = true;
		if (p.y == 0) {
			p.y++;
			continue;
		}
		if (p.y == H-1) {
			saved[pos.y][pos.x] = res;
			return res;
		}
		if (saved[p.y][p.x]) {
			return res + saved[p.y][p.x];
		}
		if (slippery && grid[p.y][p.x] != '.') {
			char c = grid[p.y][p.x];
			if (c == '>') {
				p.x++;
			} else if (c == '<') {
				p.x--;
			} else if (c == '^') {
				p.y--;
			} else {
				p.y++;
			}
			if (visited[p.y][p.x]) return 0;
			continue;
		}
		vector<Pt> paths;
		if (grid[p.y-1][p.x] != '#') {
			paths.push_back({p.y-1,p.x});
		}
		if (grid[p.y+1][p.x] != '#') {
			paths.push_back({p.y+1,p.x});
		}
		if (grid[p.y][p.x-1] != '#') {
			paths.push_back({p.y,p.x-1});
		}
		if (grid[p.y][p.x+1] != '#') {
			paths.push_back({p.y,p.x+1});
		}
		if (paths.size() <= 2) {
			assert(paths.size() > 1);
			if (visited[paths[0].y][paths[0].x] && visited[paths[1].y][paths[1].x]) return 0;
			if (visited[paths[0].y][paths[0].x]) {
				p = paths[1];
			} else {
				p = paths[0];
			}
			continue;
		}
		int mx = 0;
		for(auto &np : paths) {
			if (!visited[np.y][np.x]) {
				mx = max(mx, find_longest(np, grid, saved, visited, slippery) + 1);
			}
		}
		return mx + res;
	}
}

ll first() {
	vector<vector<int>> saved(H, vector<int>(W, 0));
	vector<vector<bool>> visited(H, vector<bool>(W, false));

	return find_longest({0, 1}, grid, saved, visited, true);
}

ll second() {
	vector<vector<int>> saved(H, vector<int>(W, 0));
	vector<vector<bool>> visited(H, vector<bool>(W, false));

	return find_longest({0, 1}, grid, saved, visited, false);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
