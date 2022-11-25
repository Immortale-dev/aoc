#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<vector<int> > input;

const int Y = 10;
const int X = 10;
const int MS = 50;

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<int> line;
		for(int i=0;i<s.size();i++) {
			line.push_back(s[i] - '0');
		}
		input.emplace_back(line);
	}
}


void flash(vector<vector<int>>& inp, int y, int x, vector<vector<bool>>& flashed) {
	if(flashed[y][x]) return;
	flashed[y][x] = true;
	for(int i=y-1;i<=y+1;i++) {
		for(int j=x-1;j<=x+1;j++) {
			if(i < 0 || j < 0 || i >= Y || j >= X || i == y && j == x) continue;
			if(++inp[i][j] >= 10)
				flash(inp, i, j, flashed);
		}
	}
}

void step(vector<vector<int>>& inp) {
	vector<vector<bool>> flashed(10, vector<bool>(10, false));
	for(int i=0;i<Y;i++) {
		for(int j=0;j<X;j++) {
			++inp[i][j];
		}
	}
	for(int i=0;i<Y;i++) {
		for(int j=0;j<X;j++) {
			if(inp[i][j] >= 10) {
				flash(inp, i, j, flashed);
			}
		}
	}
	for(int i=0;i<Y;i++) {
		for(int j=0;j<X;j++) {
			if(inp[i][j] >= 10) {
				inp[i][j] = 0;
			}
		}
	}
}

void print_flashes(vector<vector<int>>& inp, bool clr) {
	if(!clr) {
		cout << '\n';
	} else {
		cout << "\033[s"; // save_pos
		cout << "\033[10A";
	}
	for(int i=0;i<Y;i++){
		for(int j=0;j<X;j++){
			if(inp[i][j]) {
				cout << '.';
			} else {
				cout << 'x';
			}
		}
		cout << '\n';
	}
	if(clr) {
		cout << "\033[u"; //restore_pos
	}
}

ll first() {
	ll res = 0;
	vector<vector<int>> inp = input;
	for(int i=0;i<100;i++){
		step(inp);
		
		// Visualize
		//print_flashes(inp, i);
		//this_thread::sleep_for(chrono::milliseconds(MS));
		
		for(int y=0;y<Y;y++) {
			for(int x=0;x<X;x++) {
				if(!inp[y][x]) ++res;
			}
		}
	}
	return res;
}

ll second() {
	vector<vector<int>> inp = input;
	for(ll i=0;;i++){
		int flashes = 0;
		step(inp);
		
		// Visualize
		//print_flashes(inp, i);
		//this_thread::sleep_for(chrono::milliseconds(MS));
		
		for(int y=0;y<Y;y++) {
			for(int x=0;x<X;x++) {
				if(!inp[y][x]) ++flashes;
			}
		}
		if(flashes == Y*X) return i+1;
	}
	return -1;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
