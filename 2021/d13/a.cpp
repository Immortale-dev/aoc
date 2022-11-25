#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<pair<int,int>> dots;
vector<pair<char,int>> folds;

const int S_Y = 1500;
const int S_X = 1500;
const int W = 3000;
const int H = 3000;
vector<vector<bool>> paper(H, vector<bool>(W, false));


void prepare() {
	string s;
	while(getline(cin, s)){
		if(s == "") {
			break;
		}
		auto arr = split_line(s, ",");
		dots.push_back(make_pair(stoi(arr[0]), stoi(arr[1])));
	}
	
	while(getline(cin, s)){
		auto arr = split_line(s, " ");
		auto arr_fold = split_line(arr[2], "=");
		folds.push_back(make_pair(arr_fold[0][0], stoi(arr_fold[1])));
	}
	
	for(auto& it : dots) {
		paper[S_Y+it.second][S_X+it.first] = true;
	}
}

void fold_y(int line) {
	for(int i=S_Y+line+1;i<H;i++) {
		for(int j=0;j<W;j++) {
			if(paper[i][j]) {
				paper[S_Y+line-(i-S_Y-line)][j] = true;
				paper[i][j] = false;
			}
		}
	}
}

void fold_x(int line) {
	for(int i=0;i<H;i++) {
		for(int j=S_X+line+1;j<W;j++) {
			if(paper[i][j]) {
				paper[i][S_X+line-(j-S_X-line)] = true;
				paper[i][j] = false;
			}
		}
	}
}

void print_paper() {
	int top = H, right = 0, bottom = 0, left = W;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if(paper[i][j]) {
				top = min(top, i);
				right = max(right, j);
				bottom = max(bottom ,i);
				left = min(left, j);
			}
		}
	}
	
	cout << endl;
	for(int i=top;i<=bottom;i++) {
		for(int j=left;j<=right;j++) {
			if(paper[i][j]) cout << "#";
			else cout << " ";
		}
		cout << endl;
	}
}

ll first() {
	auto& fold = folds[0];
	if(fold.first == 'y') {
		fold_y(fold.second);
	} else {
		fold_x(fold.second);
	}
	
	ll res = 0;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			res += paper[i][j];
		}
	}
	
	return res;
}

ll second() {
	for(int i=1;i<folds.size();i++) {
		auto& fold = folds[i];
		if(fold.first == 'y') {
			fold_y(fold.second);
		} else {
			fold_x(fold.second);
		}
	}
	print_paper();
	return 0;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
