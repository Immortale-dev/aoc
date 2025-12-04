#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(string) lines = UNTIL_END();
};

Input input(std::cin);

ll first() {
	ll res = 0;
	int H = input.lines.size();
	int W = input.lines[0].size();
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (input.lines[i][j] != '@') continue;
			int cnt = 0;
			if (i > 0 && j > 0 && input.lines[i-1][j-1] == '@') cnt++;
			if (i > 0 && input.lines[i-1][j] == '@') cnt++;
			if (i > 0 && j < W-1 && input.lines[i-1][j+1] == '@') cnt++;
			if (j > 0 && input.lines[i][j-1] == '@') cnt++;
			if (j < W-1 && input.lines[i][j+1] == '@') cnt++;
			if (i < H-1 && j > 0 && input.lines[i+1][j-1] == '@') cnt++;
			if (i < H-1 && input.lines[i+1][j] == '@') cnt++;
			if (i < H-1 && j < W-1 && input.lines[i+1][j+1] == '@') cnt++;

			if (cnt < 4) res++;
		}
	}
	return res;
}

ll second() {
	int total = 0;
	int H = input.lines.size();
	int W = input.lines[0].size();
	vector<vector<int>> vals(H+5, vector<int>(W+5, 0));
	for (int i=0;i<H;i++) {
		for (int j=0;j<W;j++) {
			if (input.lines[i][j] == '@') total++;
			if (input.lines[i][j] != '@') continue;
			int cnt = 0;
			if (i > 0 && j > 0 && input.lines[i-1][j-1] == '@') cnt++;
			if (i > 0 && input.lines[i-1][j] == '@') cnt++;
			if (i > 0 && j < W-1 && input.lines[i-1][j+1] == '@') cnt++;
			if (j > 0 && input.lines[i][j-1] == '@') cnt++;
			if (j < W-1 && input.lines[i][j+1] == '@') cnt++;
			if (i < H-1 && j > 0 && input.lines[i+1][j-1] == '@') cnt++;
			if (i < H-1 && input.lines[i+1][j] == '@') cnt++;
			if (i < H-1 && j < W-1 && input.lines[i+1][j+1] == '@') cnt++;
			vals[i+1][j+1] = cnt;
		}
	}

	queue<pair<int,int>> q;
	for (int i=1;i<=H;i++) {
		for (int j=1;j<=W;j++) {
			if (vals[i][j] > 0 && vals[i][j] < 4) {
				q.push({i,j});
				vals[i][j] = 0;
			}
		}
	}
	while(!q.empty()) {
		auto [h,w] = q.front();
		q.pop();
		for (int r=-1;r<=1;r++) {
			for (int c=-1;c<=1;c++) {
				if (r == 0 && c == 0) continue;
				int rr = h+r;
				int cc = w+c;
				if (vals[rr][cc] && --vals[rr][cc] < 4) {
					vals[rr][cc] = 0;
					q.push({rr,cc});
				}
			}
		}
	}

	int res = 0;
	for (int i=1;i<=H;i++) {
		for (int j=1;j<=W;j++) {
			if (vals[i][j]) res++;
		}
	}
	return total-res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
