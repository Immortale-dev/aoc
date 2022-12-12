#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<int>> heights;
int startX, startY, endX, endY, W, H;
int maxSteps = 9999999;

struct Step {
	int x,y,v;
};

void prepare() {
	string s;
	int lind = 0;
	while(getline(cin, s)){
		vector<int> line;
		for(int i=0;i<s.size();i++) {
			if (s[i] == 'S') {
				startX = i;
				startY = lind;
				s[i] = 'a';
			}
			if (s[i] == 'E') {
				endX = i;
				endY = lind;
				s[i] = 'z';
			}
			line.push_back(s[i] - 'a');
		}
		heights.push_back(line);
		lind++;
	}
	H = heights.size();
	W = heights[0].size();
}

int steps_to_end(int sx, int sy) {
	vector<vector<int>> steps(H, vector<int>(W, maxSteps));
	queue<Step> process;
	process.push({sx, sy, 0});
	
	while(!process.empty()) {
		Step st = process.front();
		process.pop();
		
		int x = st.x;
		int y = st.y;
		int v = st.v;
		
		if (steps[y][x] <= v) continue;
		
		steps[y][x] = v;
		
		if (x-1 >= 0 && heights[y][x-1] - heights[y][x] <= 1) {
			process.push({x-1,y,v+1});
		}
		if (x+1 < W && heights[y][x+1] - heights[y][x] <= 1) {
			process.push({x+1,y,v+1});
		}
		if (y-1 >= 0 && heights[y-1][x] - heights[y][x] <= 1) {
			process.push({x,y-1,v+1});
		}
		if (y+1 < H && heights[y+1][x] - heights[y][x] <= 1) {
			process.push({x,y+1,v+1});
		}
	}
	
	return steps[endY][endX];
}

ll first() {
	return steps_to_end(startX, startY);
}

ll second() {
	int min_steps = 9999999;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (heights[i][j] == 0) {
				min_steps = min(min_steps, steps_to_end(j,i));
			}
		}
	}
	return min_steps;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
