#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<int>> field;

int R;
int C;

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<int> row;
		for(char c : s) {
			row.push_back(c-'0');
		}
		field.push_back(row);
	}
	R = field.size();
	C = field[0].size();
}

vector<vector<bool>> vis;

ll first() {
	vis = vector<vector<bool>>(R, vector<bool>(C, false));
	for(int i=0;i<R;i++) {
		int maxH = field[i][0];
		vis[i][0] = true;
		for(int j=1;j<C;j++){
			if (field[i][j] > maxH) {
				vis[i][j] = true;
				maxH = field[i][j];
			}
		}
		vis[i][C-1] = true;
		maxH = field[i][C-1];
		for(int j=C-2;j>=0;j--) {
			if (field[i][j] > maxH) {
				vis[i][j] = true;
				maxH = field[i][j];
			}
		}
	}
	for(int i=0;i<C;i++) {
		int maxH = field[0][i];
		vis[0][i] = true;
		for(int j=1;j<R;j++) {
			if (field[j][i] > maxH) {
				vis[j][i] = true;
				maxH = field[j][i];
			}
		}
		maxH = field[R-1][i];
		vis[R-1][i] = true;
		for(int j=R-2;j>=0;j--) {
			if (field[j][i] > maxH) {
				vis[j][i] = true;
				maxH = field[j][i];
			}
		}
	}
	ll result = 0;
	for(int i=0;i<R;i++) {
		for(int j=0;j<C;j++) {
			result += vis[i][j];
		}
	}
	return result;
}

ll findCountDir(int r, int c, int dir) {
	int maxH = field[r][c];
	ll cnt = 0;
	int rp = (dir%2) * (dir > 1 ? 1 : -1);
	int cp = ((dir+1)%2) * (dir > 1 ? 1 : -1);
	for(int k=1;k<1000;k++) {
		int rr = r+k*rp;
		int rc = c+k*cp;
		if (rr < 0 || rr >= R || rc < 0 || rc >= C) return cnt;
		if (field[rr][rc] >= maxH) return cnt+1;
		cnt++; 
	}
	return cnt;
}

ll second() {
	ll maxC = 0;
	for(int i=0;i<R;i++) {
		for(int j=0;j<C;j++) {
			maxC = max(maxC, findCountDir(i,j,0) * findCountDir(i,j,1) * findCountDir(i,j,2) * findCountDir(i,j,3));
		}
	}
	return maxC;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
