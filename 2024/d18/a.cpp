#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Mem) {
	PARSE_SETUP;
	PARSE(int) x = SINGLE();
	SKIP(char) = SINGLE(',');
	PARSE(int) y = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Mem) arr = UNTIL_END();
};

Input input(std::cin);

const int W=71;
const int H=71;

struct Pos {
	int x,y,s;
};

vector<vector<int>> calc_grid(vector<vector<bool>>& bytes) {
	vector<vector<int>> grid(H, vector<int>(W, 999999999));

	queue<Pos> q;
	q.push({0,0,0});

	while(!q.empty()) {
		auto p = q.front();
		q.pop();

		if (p.x < 0 || p.y < 0 || p.x >= W || p.y >= H) continue;
		if (bytes[p.y][p.x] || grid[p.y][p.x] <= p.s) continue;

		grid[p.y][p.x] = p.s;
		q.push({p.x+1, p.y, p.s+1});
		q.push({p.x-1, p.y, p.s+1});
		q.push({p.x, p.y+1, p.s+1});
		q.push({p.x, p.y-1, p.s+1});
	}

	return grid;
}

void print_grid(vector<vector<int>> &grid) {
	for (int i=0;i<grid.size();i++) {
		for (int j=0;j<grid[i].size();j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

ll first() {
	vector<vector<bool>> bytes(H, vector<bool>(W, false));

	for (int i=0;i<1024;i++) {
		int x = input.arr[i].x();
		int y = input.arr[i].y();
		bytes[y][x] = true;
	}

	auto grid = calc_grid(bytes);

	return grid[H-1][W-1];
}

ll second() {
	int mn = 0;
	int mx = input.arr.size();
	int md;
	int last = 0;

	while(mn<mx) {
		md = (mx+mn)/2;

		vector<vector<bool>> bytes(H, vector<bool>(W, false));
		for (int i=0;i<=md;i++) {
			int x = input.arr[i].x();
			int y = input.arr[i].y();
			bytes[y][x] = true;
		}
		auto grid = calc_grid(bytes);

		if (grid[H-1][W-1] < 999999) {
			mn = md+1;
		} else {
			last = md;
			mx = md;
		}
	}

	cout << input.arr[last].x() << "," << input.arr[last].y() << endl;
	return 0;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
