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

int findWord(Input &input, int r, int c) {
	const string word = "XMAS";
	int res = 0;
	vector<pair<int,int>> dirs{{0,1}, {1,0}, {1,1}, {1,-1}, {0,-1}, {-1,0}, {-1,-1}, {-1,1}};
	for (auto& pair : dirs) {
		bool found = true;
		for (int i=r,j=c,k=0;k<word.size();k++,i+=pair.first,j+=pair.second) {
			if (i >= input.grid.size() || j >= input.grid[0].size() || i < 0 || j < 0) {
				found = false;
				break;
			}
			if (word[k] != input.grid[i][j]) {
				found = false;
				break;
			}
		}
		if (found) ++res;
	}
	return res;
}

int findMas(Input &input, int i, int j) {
	if (i-1<0 || j-1<0 || i+1>=input.grid.size() || j+1>=input.grid[0].size()) {
		return 0;
	}
	auto& grid = input.grid;
	int res = 0;
	if (grid[i][j] != 'A') return 0;
	if (grid[i-1][j-1] == 'M' && grid[i-1][j+1] == 'M' && grid[i+1][j+1] == 'S' && grid[i+1][j-1] == 'S') ++res;
	if (grid[i+1][j+1] == 'M' && grid[i+1][j-1] == 'M' && grid[i-1][j-1] == 'S' && grid[i-1][j+1] == 'S') ++res;
	if (grid[i-1][j-1] == 'M' && grid[i+1][j-1] == 'M' && grid[i+1][j+1] == 'S' && grid[i-1][j+1] == 'S') ++res;
	if (grid[i-1][j+1] == 'M' && grid[i+1][j+1] == 'M' && grid[i-1][j-1] == 'S' && grid[i+1][j-1] == 'S') ++res;
	return res;
}

ll first() {
	int res = 0;
	for (int i=0;i<input.grid.size();i++) {
		for (int j=0;j<input.grid[0].size();j++) {
			int local = findWord(input, i, j);
			res += local;
		}
	}
	return res;
}

ll second() {
	int res = 0;
	for (int i=0;i<input.grid.size();i++) {
		for (int j=0;j<input.grid[0].size();j++) {
			int local = findMas(input, i, j);
			res += local;
		}
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
