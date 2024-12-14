#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Robot) {
	PARSE_SETUP;
	SKIP(char) = THROUGH('=');
	PARSE(int) x = SINGLE();
	SKIP(char) = SINGLE(',');
	PARSE(int) y = SINGLE();
	SKIP(char) = THROUGH('=');
	PARSE(int) vx = SINGLE();
	SKIP(char) = SINGLE(',');
	PARSE(int) vy = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Robot) robots = UNTIL_END();
};

Input input(std::cin);

const int W = 101; //11; // 101
const int H = 103; //7; // 103

pair<int,int> calc_pos(int x, int y, int vx, int vy) {
	x += vx;
	y += vy;
	if (x >= W) x = x%W;
	if (x < 0) x = W + x;
	if (y >= H) y = y%H;
	if (y < 0) y = H + y;
	return {x,y};
}

int quadrant(int x, int y) {
	if (x == W/2 || y == H/2) return -1;
	int ret = 0;
	if (x > W/2) ret++;
	if (y > H/2) ret+=2;
	return ret;
}

ll first() {
	vector<ll> q(4, 0);
	for (auto &r : input.robots) {
		int x = r.x();
		int y = r.y();
		for (int i=0;i<100;i++) {
			auto [nx,ny] = calc_pos(x,y,r.vx(),r.vy());
			x = nx;
			y = ny;
		}
		int qua = quadrant(x,y);
		if (qua >= 0) q[qua]++;
	}
	return q[0] * q[1] * q[2] * q[3];
}

void print(vector<pair<int,int>> &pos) {
	cout << endl;
	vector<vector<bool>> grid(H,vector<bool>(W,0));
	for (auto &p : pos) {
		grid[p.second][p.first] = true;
	}
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			cout << (grid[i][j] ? '#' : ' ');
		}
		cout << endl;
	}
	cout << endl;
}

int calc_hash(int x, int y) {
	return x*1000 + y;
}

int cget(int what, vector<int> &cluster) {
	if (what == cluster[what]) return what;
	return cluster[what] = cget(cluster[what], cluster);
}

int cadd(int what, int where, vector<int>& cluster) {
	if (what == where) return what;
	return cluster[what] = cget(where, cluster);
}

int check_tree(vector<pair<int,int>> &pos) {
	vector<int> clusters(pos.size());
	unordered_map<int,int> hpos;
	const vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
	for (int i=0;i<pos.size();i++) {
		clusters[i] = i;
		auto [x,y] = pos[i];
		hpos.insert({calc_hash(x,y), i});
	}
	for (int i=0;i<pos.size();i++) {
		auto [x,y] = pos[i];
		int into = -1;
		for (auto d : dirs) {
			if (hpos.count(calc_hash(x+d.first,y+d.second))) {
				into = hpos[calc_hash(x+d.first,y+d.second)];
				cadd(i, into, clusters);
			}
		}
	}
	int max_cluster = 0;
	unordered_map<int,int> sizes;
	for (int i=0;i<pos.size();i++) {
		sizes[cget(i, clusters)]++;
	}
	for (auto &p : sizes) {
		max_cluster = max(max_cluster, p.second);
	}
	return max_cluster;
}

ll second() {
	vector<ll> q(4, 0);
	vector<pair<int,int>> pos;
	for (auto &r : input.robots) {
		pos.push_back({r.x(), r.y()});
	}
	for (int i=0;i<1000000;i++) {
		vector<pair<int,int>> new_pos(pos.size());
		for (int j=0;j<pos.size();j++) {
			auto [x,y] = pos[j];
			auto new_p = calc_pos(x,y,input.robots[j].vx(), input.robots[j].vy());
			new_pos[j] = new_p;
		}
		swap(pos,new_pos);
		int check = check_tree(pos);
		if (check_tree(pos) > 30) {
			#ifdef PRINT
			print(pos);
			#endif
			return i+1;
		}
	}
	return -1;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
