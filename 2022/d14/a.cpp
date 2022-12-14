#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<pair<int,int>>> rocks;
int maxX = 0, maxY = 0, minX = 9999, minY = 9999;

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<pair<int,int>> lines;
		auto arr = split_line(s, " -> ");
		for(auto l : arr) {
			auto p = split_line(l, ",");
			lines.push_back({stoi(p[0]), stoi(p[1])});
		}
		rocks.push_back(lines);
	}
}

vector<vector<char>> get_grid(bool with_ground=false) {
	for(auto &line : rocks) {
		for(auto &p : line) {
			maxX = max(maxX, p.first);
			maxY = max(maxY, p.second);
			minX = min(minX, p.first);
			minY = min(minY, p.second);
		}
	}
	const int rx = maxX+500;
	const int ry = maxY+10;
	vector<vector<char>> grid(ry, vector<char>(rx, '.'));
	for(auto& lines : rocks) {
		for(int i=1;i<lines.size();i++) {
			int x = lines[i-1].first;
			int y = lines[i-1].second;
			int xto = lines[i].first;
			int yto = lines[i].second;
			int px = (xto>x)-(xto<x);
			int py = (yto>y)-(yto<y);
			while(x!=xto || y!=yto) {
				grid[y][x] = '#';
				x+=px;
				y+=py;
			}
			grid[yto][xto] = '#';
		}
	}
	grid[0][500] = '+';
	if (with_ground) {
		for(int i=0;i<rx;i++) {
			grid[maxY+2][i] = '#';
		}
	}
	return grid;
}

void print_grid(vector<vector<char>>& grid, int minX, int minY, int maxX, int maxY) {
	cout << "\n";
	for(int i=minY;i<=maxY;i++) {
		for(int j=minX;j<=maxX;j++) {
			cout << grid[i][j];
		}
		cout << "\n";
	}
}

bool sand_move(int &sx, int &sy, vector<vector<char>>& grid) {
	if (sy > maxY+5) return false;
	if (grid[sy+1][sx] == '.') {
		++sy;
		return true;
	}
	if (grid[sy+1][sx-1] == '.') {
		++sy;
		--sx;
		return true;
	}
	if (grid[sy+1][sx+1] == '.') {
		++sy;
		++sx;
		return true;
	}
	return false;
}

ll first() {
	auto grid = get_grid();
	int cnt = 0;
	
	while(true) {
		int sy = 0;
		int sx = 500;
		while(sand_move(sx, sy, grid));
		if (sy > maxY+4) break;
		grid[sy][sx] = 'o';
		cnt++;
	}
	
	#ifdef PRINT
	print_grid(grid, minX-1, 0, maxX+1, maxY);
	#endif
	
	return cnt;
}

ll second() {
	auto grid = get_grid(true);
	int cnt = 0;
	
	while(true) {
		int sy = 0;
		int sx = 500;
		while(sand_move(sx, sy, grid));
		if (sx == 500 && sy == 0) break;
		grid[sy][sx] = 'o';
		cnt++;
	}
	
	#ifdef PRINT
	print_grid(grid, minX-100, 0, maxX+100, maxY+2);
	#endif
	
	return cnt+1;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
