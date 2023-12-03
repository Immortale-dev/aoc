#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> grid;
int R,C;

bool isNumChar(char c) {
	return c >= '0' && c <= '9';
}

int get_number(int r, int c, vector<vector<bool>>& found) {
	while(c > 0 && isNumChar(grid[r][c-1])) {
		--c;
	}
	int res = 0;
	while(c < C && isNumChar(grid[r][c])) {
		found[r][c] = true;
		res *= 10;
		res += grid[r][c] - '0';
		++c;
	}
	return res;
}

vector<int> findNumbersAround(int r, int c, vector<vector<bool>>& found) {
	vector<int> res;
	if (r > 0 && c > 0 && isNumChar(grid[r-1][c-1]) && !found[r-1][c-1]) {
		res.push_back(get_number(r-1,c-1,found));
	}
	if (r > 0 && isNumChar(grid[r-1][c]) && !found[r-1][c]) {
		res.push_back(get_number(r-1,c,found));
	}
	if (r > 0 && c < C-1 && isNumChar(grid[r-1][c+1]) && !found[r-1][c+1]) {
		res.push_back(get_number(r-1,c+1,found));
	}
	if (c > 0 && isNumChar(grid[r][c-1]) && !found[r][c-1]) {
		res.push_back(get_number(r,c-1,found));
	}
	if (c < C-1 && isNumChar(grid[r][c+1]) && !found[r][c+1]) {
		res.push_back(get_number(r,c+1,found));
	}
	if (r < R-1 && C > 0 && isNumChar(grid[r+1][c-1]) && !found[r+1][c-1]) {
		res.push_back(get_number(r+1,c-1,found));
	}
	if (r < R-1 && isNumChar(grid[r+1][c]) && !found[r+1][c]) {
		res.push_back(get_number(r+1,c,found));
	}
	if (r < R-1 && c < C-1 && isNumChar(grid[r+1][c+1]) && !found[r+1][c+1]) {
		res.push_back(get_number(r+1,c+1,found));
	}
	return res;
}

void prepare() {
	string s;
	while(getline(cin, s)){
		grid.push_back(s);
	}
	R = grid.size();
	C = grid[0].size();
}

ll first() {
	ll res = 0;
	vector<vector<bool>> found(R, vector<bool>(C, false));
	for(int i=0;i<R;i++) {
		for(int j=0;j<C;j++) {
			if (grid[i][j] != '.' && !isNumChar(grid[i][j])) {
				auto nums = findNumbersAround(i,j,found);
				for(auto n : nums) {
					res += n;
				}
			}
		}
	}
	return res;
}

ll second() {
	ll res = 0;
	vector<vector<bool>> found(R, vector<bool>(C, false));
	for(int i=0;i<R;i++) {
		for(int j=0;j<C;j++) {
			if (grid[i][j] == '*') {
				auto nums = findNumbersAround(i,j,found);
				if (nums.size() == 2)
				res += nums[0] * nums[1];
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
