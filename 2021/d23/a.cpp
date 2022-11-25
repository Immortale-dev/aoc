#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<vector<char>> rooms(4, {'.', '.', '.', '.'});
vector<char> hall(11, '.');
vector<ll> scores = {1,10,100,1000};

void prepare() {
	string s;
	getline(cin, s); 
	getline(cin, s);
	
	getline(cin, s);
	rooms[0][0] = s[3];
	rooms[1][0] = s[5];
	rooms[2][0] = s[7];
	rooms[3][0] = s[9];
	
	getline(cin,s);
	rooms[0][1] = s[3];
	rooms[1][1] = s[5];
	rooms[2][1] = s[7];
	rooms[3][1] = s[9];
	
	while(getline(cin,s));
}

void print_rh(vector<vector<char>> r, vector<char> h, int RH){
	cout << endl;
	for(int i=0;i<13;i++) cout << '#'; cout << endl;
	cout << '#'; for(int i=0;i<h.size();i++){ cout << h[i]; } cout << '#'; cout << endl;
	cout << "##"; for(int i=0;i<4;i++){ cout << '#' << r[i][0]; } cout << "###"; cout << endl;
	for(int j=1;j<RH;j++){
		cout << "  "; for(int i=0;i<4;i++){ cout << '#' << r[i][j]; } cout << "#  "; cout << endl;
	}
	cout << "  #########  " << endl;
	cout << endl;
}

ll dfs_bt(vector<vector<char>> r, vector<char> h, int RH) {
	ll s = 9999999999999999LL;
	ll fs = 0;
	
	bool was;
	do{
		was = false;
		// Check if you can pass to the destination form hall
		for(int i=0;i<h.size();i++){
			char c = h[i];
			if(c == '.') continue;
			int tor = c-'A';
			int to = (tor+1)*2; // A->2, B->4, C->6, D->8
			int from = i;
			bool good = true;
			int step = 0;
			for(int j=from;j!=to;j+=(to<from ? -1 : 1)){ // Go to "to"
				if(!step++) continue;
				if(h[j] != '.') {
					good = false;
					break;
				}
			}
			int lvl;
			for(lvl=RH-1;lvl>=0;lvl--){
				if(r[tor][lvl] == '.') break;
				if(r[tor][lvl] != c) good = false;
			}
			if(good){
				was = true;
				fs += abs(to-from)*scores[tor];
				// exit the hall
				h[from] = '.';
				// enter the room
				fs += scores[tor]*(lvl+1);
				r[tor][lvl] = c;
			}
		}
	} while(was); // Try to move fish to its room as long as it possible
	
	// Check if everything set
	bool allset = true;
	for(int i=0;i<4;i++){
		for(int j=0;j<RH;j++){
			if(r[i][j]-'A' != i) allset = false;
		}
	}
	if(allset) {
		return fs;
	}
	
	// Move from room to hall and recurse
	for(int i=0;i<4;i++){
		bool lgood = true;
		for(int l=RH-1;l>=0;l--){
			if(r[i][l]-'A' != i && r[i][l] != '.') lgood = false;
		}
		if(lgood) continue;
		for(int k=0;k<RH;k++){
			char c = r[i][k];
			if(c == '.') continue;
			if(k && r[i][k-1] != '.') continue; // cant move
			int from = i*2+2;
			for(int j=0;j<h.size();j++){
				if(j == 2 || j == 4 || j == 6 || j == 8) continue;
				bool good = true;
				for(int l=j;l!=from;l+=(l<from ? 1 : -1)){
					if(h[l] != '.') good = false;
				}
				if(good){
					// move fish
					r[i][k] = '.';
					h[j] = c;
					// check answer
					int ls = (abs(from-j)+k+1)*scores[c-'A'];
					s = min(s, dfs_bt(r,h,RH) + ls);
					// move fish back
					r[i][k] = c;
					h[j] = '.';
				}
			}
		}
	}
	
	return s+fs;
}

ll first() {
	return dfs_bt(rooms, hall, 2);
}

ll second() {
	vector<vector<char>> additionals = { {'D', 'D'}, {'C', 'B'}, {'B', 'A'}, {'A', 'C'} };
	for(int i=0;i<4;i++){
		rooms[i][3] = rooms[i][1];
		rooms[i][1] = additionals[i][0];
		rooms[i][2] = additionals[i][1];
	}

	return dfs_bt(rooms, hall, 4);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
