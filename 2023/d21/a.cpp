#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<char>> grid;

ll H,W;
int SX,SY;

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<char> line;
		for(auto c : s) {
			line.push_back(c);
		}
		grid.push_back(line);
	}
	H = grid.size();
	W = grid[0].size();
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (grid[i][j] == 'S') {
				SY = i;
				SX = j;
			}
		}
	}
}

vector<vector<pair<ll, bool>>> generate_visited(vector<vector<char>>& new_grid, int sy, int sx) {
	int h = new_grid.size();
	int w = new_grid[0].size();
	vector<vector<pair<ll, bool>>> visited(h, vector<pair<ll, bool>>(w, {99999999, false}));

	queue<pair<int,int>> q;
	visited[sy][sx] = {0, true};
	q.push({sy,sx});

	while(!q.empty()) {
		auto top = q.front();
		q.pop();

		auto& current = visited[top.first][top.second];
		if (top.first-1 >= 0 && current.first+1 < visited[top.first-1][top.second].first && new_grid[top.first-1][top.second] != '#') {
			visited[top.first-1][top.second] = {current.first+1, !current.second};
			q.push({top.first-1, top.second});
		}
		if (top.first+1 < h && current.first+1 < visited[top.first+1][top.second].first && new_grid[top.first+1][top.second] != '#') {
			visited[top.first+1][top.second] = {current.first+1, !current.second};
			q.push({top.first+1, top.second});
		}
		if (top.second-1 >= 0 && current.first+1 < visited[top.first][top.second-1].first && new_grid[top.first][top.second-1] != '#') {
			visited[top.first][top.second-1] = {current.first+1, !current.second};
			q.push({top.first, top.second-1});
		}
		if (top.second+1 < w && current.first+1 < visited[top.first][top.second+1].first && new_grid[top.first][top.second+1] != '#') {
			visited[top.first][top.second+1] = {current.first+1, !current.second};
			q.push({top.first, top.second+1});
		}
	}
	return visited;
}

ll first() {
	auto visited = generate_visited(grid, SY, SX);
	int res = 0;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (visited[i][j].first <= 64 && visited[i][j].second == true) {
				res++;
			}
		}
	}

	return res;
}

ll second() {
	vector<vector<char>> new_grid(H*5,vector<char>(W*5, '.'));
	for(int i=0;i<H*5;i++) {
		for(int j=0;j<W*5;j++) {
			new_grid[i][j] = grid[i%H][j%W];
		}
	}

	int l_sy = SY+H*2;
	int l_sx = SX+W*2;

	auto visited = generate_visited(new_grid, l_sy, l_sx);
	ll cnt = 26501365;
	bool cnt_b = !(cnt%2);

	assert(H == W);

	ll res = 0;
	for(int i=0;i<H*4-1;i++) {
		for(int j=0;j<W*4-1;j++) {
			int y = H/2+i+1;
			int x = W/2+j+1;

			if (visited[y][x].second == cnt_b && new_grid[y][x] != '#' && visited[y][x].first <= cnt) {
				ll screens = (cnt-visited[y][x].first)/(H*2) + 1;

				res += (screens * (screens+1)) / 2;
				if (y == l_sy) {
					res += (screens * (screens-1)) / 2;
				}
				if (x == l_sx) {
					res += (screens * (screens-1)) / 2;
				}
			}
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
