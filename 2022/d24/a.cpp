#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

using field_type = vector<vector<queue<char>>>;

field_type input;

int W,H;

vector<vector<vector<bool>>> lab;

void step(field_type &field, bool back=false) {
	queue<int> cnts;
	for(int i=1;i<H-1;i++) {
		for(int j=1;j<W-1;j++) {
			//cout << field[i][j].size();
			cnts.push(field[i][j].size());
		}
		//cout << endl;
	}
	for(int i=1;i<H-1;i++) {
		for(int j=1;j<W-1;j++) {
			int sz = cnts.front();
			//cout << "SZ: " << sz << endl;
			cnts.pop();
			while(sz--) {
				//cout << j << "x" << i << " " << field[i][j].size() << " --- " << sz << endl;
				if (field[i][j].empty()) {
					throw logic_error("Empty queue");
				}
				char c = field[i][j].front();
				field[i][j].pop();
				int y = i;
				int x = j;
				if (!back && c == '>' || back && c == '<') {
					x++;
				} else if (!back && c == '<' || back && c == '>') {
					x--;
				} else if (!back && c == 'v' || back && c == '^') {
					y++;
				} else if (!back && c == '^' || back && c == 'v') {
					y--;
				} else {
					//cout << "WTF??" << c << endl;
					throw logic_error("Something went wrong ");
				}
				if (x == 0) {
					x = W-2;
				} else if (x == W-1) {
					x = 1;
				}
				if (y == 0) {
					y = H-2;
				} else if (y == H-1) {
					y = 1;
				}
				field[y][x].push(c);
			}
		}
	}
}

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<queue<char>> line;
		for(auto c : s) {
			queue<char> q;
			if (c != '.') q.push(c);
			line.push_back(q);
		}
		input.push_back(line);
	}
	H = input.size();
	W = input[0].size();
	
	lab = vector<vector<vector<bool>>>(H-2, vector<vector<bool>>(W-2, vector<bool>((W-2)*(H-2), false)));
	
	for(int k=0;k<(W-2)*(H-2);k++) {
		for(int i=1;i<H-1;i++) {
			for(int j=1;j<W-1;j++) {
				lab[i-1][j-1][k] = input[i][j].empty();
			}
		}
		step(input);
	}
}

void print_field(field_type& field) {
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (i == 0 && j == 1 || i == H-1 && j == W-2) {
				cout << '.';
				continue;
			}
			if (i == 0 || i == H-1 || j == 0 || j == W-1) {
				cout << '#';
				continue;
			}
			if (field[i][j].empty()) {
				cout << '.';
				continue;
			}
			if (field[i][j].size() > 1) {
				cout << field[i][j].size();
				continue;
			}
			cout << field[i][j].front();
		}
		cout << endl;
	}
}

struct P3 {
	int x,y,z;
	int step;
};


int find_steps_to(int sx, int sy, int ex, int ey, int time) {
	int w = W-2;
	int h = H-2;
	int d = w*h;
	vector<vector<vector<int>>> min_steps(h, vector<vector<int>>(w, vector<int>(d, 1000000)));
	
	queue<P3> q;
	for(int i=0;i<d;i++) {
		if (lab[sy][sx][(i+time)%d]) {
			q.push({sx,sy,(i+time+1)%d,i+1});
		}
	}
	
	while(!q.empty()) {
		P3 p = q.front();
		q.pop();
		
		if (p.x < 0 || p.x >= w || p.y < 0 || p.y >= h || !lab[p.y][p.x][p.z] || min_steps[p.y][p.x][p.z] <= p.step) {
			continue;
		}
		min_steps[p.y][p.x][p.z] = p.step;
		q.push({p.x+1, p.y, (p.z+1)%d, p.step+1});
		q.push({p.x-1, p.y, (p.z+1)%d, p.step+1});
		q.push({p.x, p.y+1, (p.z+1)%d, p.step+1});
		q.push({p.x, p.y-1, (p.z+1)%d, p.step+1});
		q.push({p.x, p.y, (p.z+1)%d, p.step+1});
	}
	
	int mn = 1000000;
	for(int i=0;i<d;i++) {
		mn = min(min_steps[ey][ex][i], mn);
	}
	return mn;
}

ll first() {
	int w = W-2;
	int h = H-2;
	int d = w*h;
	
	return find_steps_to(0,0,w-1,h-1,0)+1;
}

ll second() {
	int w = W-2;
	int h = H-2;
	int d = w*h;
	
	int steps_to = find_steps_to(0,0,w-1,h-1,0)+1;
	int steps_back = find_steps_to(w-1,h-1,0,0,steps_to)+1;
	return steps_to + steps_back + find_steps_to(0,0,w-1,h-1,steps_to+steps_back)+1;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
