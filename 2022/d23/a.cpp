#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> input;

int H,W;

void prepare() {
	string s;
	while(getline(cin, s)){
		input.push_back(s);
	}
	H = input.size();
	W = input[0].size();
}

template<typename T>
void clear_field(vector<vector<T>> &field, int w, int h) {
	for(int i=0;i<h;i++) {
		for(int j=0;j<w;j++) {
			field[i][j] = 0;
		}
	}
}

pair<int,int> get_move(vector<vector<bool>> &field, int x, int y, int dir) {
	if (!field[y-1][x-1] && !field[y-1][x] && !field[y-1][x+1] &&
		!field[y][x-1]                     && !field[y][x+1] &&
		!field[y+1][x-1] && !field[y+1][x] && !field[y+1][x+1]) return {x,y};

	for(int k=0;k<4;k++) {
		int d = (k+dir)%4;
		
		if (d == 0) {
			if (!field[y-1][x-1] && !field[y-1][x] && !field[y-1][x+1]) {
				return {x,y-1};
			}
		}
		if (d == 1) {
			if (!field[y+1][x-1] && !field[y+1][x] && !field[y+1][x+1]) {
				return {x, y+1};
			}
		}
		if (d == 2) {
			if (!field[y-1][x-1] && !field[y][x-1] && !field[y+1][x-1]) {
				return {x-1, y};
			}
		}
		if (d == 3) {
			if (!field[y-1][x+1] && !field[y][x+1] && !field[y+1][x+1]) {
				return {x+1, y};
			}
		}
	}
	
	return {x,y};
}

void print_field(vector<vector<bool>> &field) {
	cout << endl;
	for(size_t i=0;i<field.size();i++) {
		for(size_t j=0;j<field[i].size();j++) {
			cout << (field[i][j] ? '#' : '.');
		}
		cout << endl;
	}
}

ll first() {
	int rw = W+25;
	int rh = H+25;
	
	vector<vector<bool>> field(rh, vector<bool>(rw, false));
	vector<vector<int>> wish(rh, vector<int>(rw, 0));
	
	int ox = 12;
	int oy = 12;
	
	for(size_t i=0;i<input.size();i++) {
		for(size_t j=0;j<input[i].size();j++) {
			field[oy+i][ox+j] = input[i][j] == '#';
		}
	}
	
	int dir = 0;
	for(int step=0;step<10;step++) {
		for(int i=0;i<rh;i++) {
			for(int j=0;j<rw;j++) {
				if (field[i][j]) {
					auto [x,y] = get_move(field, j, i, dir);
					wish[y][x]++;
				}
			}
		}
		vector<vector<bool>> temp_field(rh, vector<bool>(rw, false));
		for(int i=0;i<rh;i++) {
			for(int j=0;j<rw;j++) {
				if (field[i][j]) {
					auto [x,y] = get_move(field, j, i, dir);
					if (wish[y][x] == 1) {
						temp_field[y][x] = true;
					} else {
						temp_field[i][j] = true;
					}
				}
			}
		}
		field = temp_field;
		clear_field(wish, rw, rh);
		dir++;
	}
	
	int minX=rw, maxX=0, minY=rh, maxY=0;
	int cnt = 0;
	for(int i=0;i<rh;i++) {
		for(int j=0;j<rw;j++) {
			cnt += field[i][j];
			if (field[i][j]) {
				minX = min(minX, j);
				maxX = max(maxX, j);
				minY = min(minY, i);
				maxY = max(maxY, i);
			}
		}
	}
	
	return ((maxX-minX+1) * (maxY-minY+1)) - cnt;
}

ll second() {
	int rw = W*3+20;
	int rh = H*3+20;
	
	vector<vector<bool>> field(rh, vector<bool>(rw, false));
	vector<vector<int>> wish(rh, vector<int>(rw, 0));
	
	int ox = W+10;
	int oy = H+10;
	
	for(size_t i=0;i<input.size();i++) {
		for(size_t j=0;j<input[i].size();j++) {
			field[oy+i][ox+j] = input[i][j] == '#';
		}
	}
	
	int dir = 0;
	int step = 0;
	for(;;) {
		step++;
		for(int i=0;i<rh;i++) {
			for(int j=0;j<rw;j++) {
				if (field[i][j]) {
					auto [x,y] = get_move(field, j, i, dir);
					wish[y][x]++;
				}
			}
		}
		bool was_move = false;
		vector<vector<bool>> temp_field(rh, vector<bool>(rw, false));
		for(int i=0;i<rh;i++) {
			for(int j=0;j<rw;j++) {
				if (field[i][j]) {
					auto [x,y] = get_move(field, j, i, dir);
					if (wish[y][x] == 1) {
						temp_field[y][x] = true;
						if (y != i || x != j) was_move = true;
					} else {
						temp_field[i][j] = true;
					}
				}
			}
		}
		field = temp_field;
		clear_field(wish, rw, rh);
		dir++;
		if (!was_move) break;
	}
	
	return step;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
