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

const vector<pair<int,int>> dirs = {{1,0}, {0,1}, {-1,0}, {0,-1}};

struct Pos {
	int x, y, dir, score;
};

int sx=-1,sy=-1,ex=-1,ey=-1;
int dir = 0;

void prepare() {
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (input.grid[i][j] == 'S') {
				sx = j;
				sy = i;
			}
			if (input.grid[i][j] == 'E') {
				ex = j;
				ey = i;
			}
		}
	}
}

vector<vector<vector<int>>> calc_scores() {
	queue<Pos> q;
	q.push({sx, sy, dir, 0});
	vector<vector<vector<int>>> scores(H, vector<vector<int>>(W, vector<int>(4, 999999999)));
	scores[sy][sx][dir] = 0;

	while(!q.empty()) {
		auto pos = q.front();
		q.pop();

		int x = pos.x;
		int y = pos.y;
		int dir = pos.dir;
		for (int d=0;d<4;d++) {
			int nd = (dir + d) % 4;
			auto [px, py] = dirs[nd];
			int nx = x + px;
			int ny = y + py;
			int ps = d > 0 ? (2-(d%2)) * 1000 : 0;
			int nscore = pos.score + 1 + ps;
			if (input.grid[ny][nx] == '#') continue;
			if (scores[ny][nx][nd] < nscore) continue;

			scores[ny][nx][nd] = nscore;
			q.push({nx,ny,nd,nscore});
		}
	}
	return scores;
}

ll first() {
	auto scores = calc_scores();
	int mn = 999999999;
	for (int i=0;i<4;i++) {
		mn = min(mn, scores[ey][ex][i]);
	}
	return mn;
}

ll second() {
	auto scores = calc_scores();
	vector<vector<bool>> best_places(H, vector<bool>(W, false));
	int mn = 999999999;
	for (int i=0;i<4;i++) {
		mn = min(mn, scores[ey][ex][i]);
	}

	queue<Pos> q;
	for (int i=0;i<4;i++) {
		if (scores[ey][ex][i] == mn) {
			q.push({ex, ey, i, mn});
		}
	}

	while(!q.empty()) {
		auto pos = q.front();
		q.pop();

		int x = pos.x;
		int y = pos.y;
		int dir = pos.dir;

		auto [mx,my] = dirs[dir];
		int nx = x-mx;
		int ny = y-my;

		best_places[y][x] = true;

		if (scores[ny][nx][dir] == pos.score - 1) {
			q.push({nx, ny, dir, pos.score-1});
		}
		for (int i=1;i<=3;i++) {
			int nd = (dir+i)%4;
			if (scores[ny][nx][nd] == pos.score - 1001) {
				q.push({nx, ny, nd, pos.score-1001});
			}
		}
	}

	int res = 0;
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			res += best_places[i][j];
		}
	}

	#ifdef PRINT
	cout << endl;
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (best_places[i][j]) cout << 'O';
			else cout << input.grid[i][j];
		}
		cout << endl;
	}
	#endif

	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
