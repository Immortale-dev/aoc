#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<int>> grid;
int H,W;

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<int> v;
		for(auto c : s) {
			v.push_back(c-'0');
		}
		grid.push_back(v);
	}
	H = grid.size();
	W = grid[0].size();
}

struct Case {
	int y;
	int x;
	int dir;
	int moves;
	int score;
};

pair<int,int> give_pluses(int dir) {
	if (dir == 0) {
		return {0,1};
	}
	if (dir == 1) {
		return {1,0};
	}
	if (dir == 2) {
		return {0,-1};
	}
	if (dir == 3) {
		return {-1,0};
	}
	throw logic_error("wrong direction");
}

ll first() {
	vector<vector<vector<vector<int>>>> dp(H+1, vector<vector<vector<int>>>(W+1, vector<vector<int>>(4, vector<int>(4, 9999999))));
	queue<Case> q;
	q.push({0,0,0,0,0});
	while(!q.empty()) {
		Case c = q.front();
		q.pop();
		if (c.y < 0 || c.y >= H || c.x < 0 || c.x >= W || c.moves > 3) {
			continue;
		}
		if (c.score + grid[c.y][c.x] >= dp[c.y][c.x][c.dir][c.moves]) {
			continue;
		}
		int new_score = c.score + grid[c.y][c.x];
		dp[c.y][c.x][c.dir][c.moves] = new_score;
		auto curDir = give_pluses(c.dir);
		auto leftDir = give_pluses((c.dir+1)%4);
		auto rightDir = give_pluses((c.dir-1+4)%4);
		q.push({c.y + curDir.first, c.x + curDir.second, c.dir, c.moves+1, new_score });
		q.push({c.y + leftDir.first, c.x + leftDir.second, (c.dir+1)%4, 1, new_score});
		q.push({c.y + rightDir.first, c.x + rightDir.second, (c.dir-1+4)%4, 1, new_score});
	}
	int res = 9999999;
	for(int i=0;i<4;i++) {
		for(int j=0;j<=3;j++) {
			res = min(res, dp[H-1][W-1][i][j]);
		}
	}
	return res - grid[0][0];
}

ll second() {
	vector<vector<vector<vector<int>>>> dp(H+1, vector<vector<vector<int>>>(W+1, vector<vector<int>>(4, vector<int>(11, 9999999))));
	queue<Case> q;
	q.push({0,0,0,0,0});
	while(!q.empty()) {
		Case c = q.front();
		q.pop();
		if (c.y < 0 || c.y >= H || c.x < 0 || c.x >= W || c.moves > 10) {
			continue;
		}
		if (c.score + grid[c.y][c.x] >= dp[c.y][c.x][c.dir][c.moves]) {
			continue;
		}
		int new_score = c.score + grid[c.y][c.x];
		dp[c.y][c.x][c.dir][c.moves] = new_score;
		auto curDir = give_pluses(c.dir);
		auto leftDir = give_pluses((c.dir+1)%4);
		auto rightDir = give_pluses((c.dir-1+4)%4);
		q.push({c.y + curDir.first, c.x + curDir.second, c.dir, c.moves+1, new_score});
		if (c.moves < 4) continue;
		q.push({c.y + leftDir.first, c.x + leftDir.second, (c.dir+1)%4, 1, new_score});
		q.push({c.y + rightDir.first, c.x + rightDir.second, (c.dir-1+4)%4, 1, new_score});
	}
	int res = 9999999;
	for(int i=0;i<4;i++) {
		for(int j=4;j<=10;j++) {
			res = min(res, dp[H-1][W-1][i][j]);
		}
	}
	return res - grid[0][0];
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
