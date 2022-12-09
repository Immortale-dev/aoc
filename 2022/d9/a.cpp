#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "../helpers/terminal.cpp"

typedef long long int ll;

//=======================================//

struct Move {
	char dir;
	int cnt;
};

int minx = 0, maxx = 0, miny = 0, maxy = 0;
vector<Move> moves;
int w, h;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto movearr = split_line(s, " ");
		moves.push_back({movearr[0][0], stoi(movearr[1])});
	}
	int posx, posy;
	for(auto &move : moves) {
		if (move.dir == 'U') posy -= move.cnt;
		if (move.dir == 'D') posy += move.cnt;
		if (move.dir == 'L') posx -= move.cnt;
		if (move.dir == 'R') posx += move.cnt;
		minx = min(minx, posx);
		maxx = max(maxx, posx);
		miny = min(miny, posy);
		maxy = max(maxy, posy);
	}
	w = maxx-minx+1;
	h = maxy-miny+1;
}

void moveHead(int& x, int& y, char move) {
	if (move == 'U') y--;
	if (move == 'D') y++;
	if (move == 'L') x--;
	if (move == 'R') x++;
}

void moveTail(int Hx, int Hy, int& Tx, int& Ty) {
	if (abs(Hx-Tx) > 1 || abs(Hy-Ty) > 1) {
		Tx += (0<Hx-Tx)-(Hx-Tx<0);
		Ty += (0<Hy-Ty)-(Hy-Ty<0);
	}
}

void printPos(vector<pair<int,int>> rope, vector<vector<bool>>& visited) {
	for(int i=0;i<h;i++) {
		cout << "\n";
		for(int j=0;j<w;j++) {
			bool found = false;
			for(int r=0;r<rope.size();r++) {
				auto part = rope[r];
				if (part.first == j && part.second == i) {
					char pc = r+'0';
					if (r == 0) pc = 'H';
					cout << pc;
					found = true;
					break;
				}
			}
			if (found) {
				continue;
			}
			if (visited[i][j]) {
				cout << "#";
				continue;
			}
			cout << ".";
		}
	}
	cout << "\n";
}

ll first() {
	vector<vector<bool>> visited(h, vector<bool>(w, false));
	int Hx = -minx;
	int Hy = -miny;
	int Tx = Hx;
	int Ty = Hy;
	
	for(auto &move : moves) {
		for(int m=0;m<move.cnt;m++) {
			moveHead(Hx, Hy, move.dir);
			moveTail(Hx, Hy, Tx, Ty);
			visited[Ty][Tx] = true;
		}
	}
	
	#ifdef PRINT
	printPos({{Hx, Hy}, {Tx, Ty}}, visited);
	#endif
	
	int res = 0;
	for(int i=0;i<h;i++) {
		for(int j=0;j<w;j++) {
			res += visited[i][j];
		}
	}
	
	return res;
}

ll second() {
	vector<vector<bool>> visited(h, vector<bool>(w, false));
	vector<pair<int,int>> rope(10, {-minx, -miny});
	
	for(auto &move : moves) {
		for(int m=0;m<move.cnt;m++) {
			moveHead(rope[0].first, rope[0].second, move.dir);
			
			for(int r=1;r<rope.size();r++) {
				moveTail(rope[r-1].first, rope[r-1].second, rope[r].first, rope[r].second);
			}
			visited[rope[rope.size()-1].second][rope[rope.size()-1].first] = true;
		}
	}
	
	#ifdef PRINT
	printPos(rope, visited);
	#endif
	
	int res = 0;
	for(int i=0;i<h;i++) {
		for(int j=0;j<w;j++) {
			res += visited[i][j];
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
