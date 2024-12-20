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

struct Pos {
	int x,y;
	int s = 0;
	bool cheated = false;
};

Pos start;
Pos finish;

Pos find_start() {
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (input.grid[i][j] == 'S') {
				return {j,i};
			}
		}
	}
	assert(false);
}

Pos find_finish() {
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (input.grid[i][j] == 'E') {
				return {j,i};
			}
		}
	}
	assert(false);
}

void prepare() {
	start = find_start();
	finish = find_finish();
}

vector<vector<int>> calc_distances(Pos p) {
	queue<Pos> q;
	q.push(p);

	vector<vector<int>> state(H,vector<int>(W, 999999999));

	while(!q.empty()) {
		Pos p = q.front();
		q.pop();

		if (input.grid[p.y][p.x] == '#') continue;
		if (state[p.y][p.x] <= p.s) continue;

		state[p.y][p.x] = p.s;
		q.push({p.x+1, p.y, p.s+1});
		q.push({p.x-1, p.y, p.s+1});
		q.push({p.x, p.y+1, p.s+1});
		q.push({p.x, p.y-1, p.s+1});
	}

	return state;
}

int calc_with_cheat(int max_jump, int better_path = 100) {
	auto distances = calc_distances(finish);
	int nc = distances[start.y][start.x];

	int res = 0;

	vector<vector<int>> state(H, vector<int>(W, 999999999));
	queue<Pos> q;
	q.push(start);

	while(!q.empty()) {
		Pos p = q.front();
		q.pop();

		if (input.grid[p.y][p.x] == '#') continue;
		if (state[p.y][p.x] <= p.s) continue;

		state[p.y][p.x] = p.s;

		for (int l=2;l<=max_jump;l++) {
			for (int i=0;i<l;i++) {
				int lx = l-i;
				int ly = i;

				for (int d=0;d<4;d++) {
					swap(lx,ly);
					ly = -ly;

					int x = p.x + lx;
					int y = p.y + ly;

					if (x<0 || y<0 || x>=W || y>=H) continue;
					if (input.grid[y][x] == '#') continue;

					int lres = distances[y][x] + p.s + l;
					if (lres <= nc-better_path) res++;
				}
			}
		}

		q.push({p.x+1, p.y, p.s+1});
		q.push({p.x-1, p.y, p.s+1});
		q.push({p.x, p.y+1, p.s+1});
		q.push({p.x, p.y-1, p.s+1});
	}

	return res;
}

ll first() {
	return calc_with_cheat(2,100);
}

ll second() {
	return calc_with_cheat(20,100);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
