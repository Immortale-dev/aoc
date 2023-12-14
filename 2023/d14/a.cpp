#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> grid;
int H,W;

void prepare() {
	string s;
	while(getline(cin, s)){
		grid.push_back(s);
	}
	H = grid.size();
	W = grid[0].size();
}

void tilt_north(vector<string>& res) {
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (res[i][j] == 'O') {
				int k = i;
				while(k-1 >= 0 && res[k-1][j] == '.') --k;
				if (k != i) {
					swap(res[k][j], res[i][j]);
				}
			}
		}
	}
}

void tilt_west(vector<string>& res) {
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (res[i][j] == 'O') {
				int k = j;
				while(k-1 >= 0 && res[i][k-1] == '.') --k;
				if (k != j) {
					swap(res[i][k], res[i][j]);
				}
			}
		}
	}
}

void tilt_south(vector<string>& res) {
	for(int i=H-1;i>=0;i--) {
		for(int j=0;j<W;j++) {
			if (res[i][j] == 'O') {
				int k = i;
				while(k+1 < H && res[k+1][j] == '.') ++k;
				if (k != i) {
					swap(res[k][j], res[i][j]);
				}
			}
		}
	}
}

void tilt_east(vector<string>& res) {
	for(int i=0;i<H;i++) {
		for(int j=W-1;j>=0;j--) {
			if (res[i][j] == 'O') {
				int k = j;
				while(k+1 < W && res[i][k+1] == '.') ++k;
				if (k != j) {
					swap(res[i][k], res[i][j]);
				}
			}
		}
	}
}

void print_grid(vector<string>& grid) {
	cout << endl;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
}

ll calc_score(vector<string>& new_grid) {
	ll res = 0;
	for(size_t i=0;i<new_grid.size();i++) {
		for(size_t j=0;j<new_grid[i].size();j++) {
			if (new_grid[i][j] == 'O') {
				res += new_grid.size()-i;
			}
		}
	}
	return res;
}

ll first() {
	auto new_grid = vector<string>(grid.begin(), grid.end());
	tilt_north(new_grid);
	return calc_score(new_grid);
}

ll second() {
	auto new_grid = vector<string>(grid.begin(), grid.end());

	vector<int> pattern;

	for(int i=0;i<1000;i++) {
		tilt_north(new_grid);
		tilt_west(new_grid);
		tilt_south(new_grid);
		tilt_east(new_grid);
		pattern.push_back(calc_score(new_grid));
	}
	for(int i=0;i<pattern.size()/2;i++) {
		swap(pattern[i], pattern[pattern.size()-i-1]);
	}

	int max_pattern_size = 0;
	for(int i=1;i<100;i++) {
		bool good = true;
		for(int j=0;j<i;j++) {
			if (pattern[j] != pattern[i+j]) {
				good = false;
				break;
			}
		}
		if (good) {
			max_pattern_size = i;
		}
	}

	int rest = (1000000000-1000) % max_pattern_size;
	while(rest--) {
		tilt_north(new_grid);
		tilt_west(new_grid);
		tilt_south(new_grid);
		tilt_east(new_grid);
	}

	return calc_score(new_grid);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
