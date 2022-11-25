#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

int W,H;

vector<string> input;

void prepare() {
	string s;
	while(getline(cin, s)){
		W = s.size();
		input.push_back(s);
	}
	H = input.size();
}

void print_cuc(vector<string> a) {
	cout << endl;
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			cout << a[i][j];
		}
		cout << endl;
	}
}

vector<string> step(vector<string> a) {
	vector<string> ret(H, string(W, '.'));
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(a[i][j] == '>'){
				int jj = (j+1)%W;
				if(a[i][jj] == '.'){
					ret[i][jj] = a[i][j];
				} else {
					ret[i][j] = a[i][j];
				}
			}
			if(a[i][j] == 'v'){
				ret[i][j] = a[i][j];
			}
		}
	}
	a = ret;
	ret = vector<string>(H,string(W, '.'));
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(a[i][j] == 'v'){
				int ii = (i+1)%H;
				if(a[ii][j] == '.'){
					ret[ii][j] = a[i][j];
				} else {
					ret[i][j] = a[i][j];
				}
			}
			if(a[i][j] == '>'){
				ret[i][j] = a[i][j];
			}
		}
	}
	return ret;
}

bool isEq(vector<string> a, vector<string> b){
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(a[i][j] != b[i][j]) return false;
		}
	}
	return true;
}

ll first() {
	int st = 0;
	auto a = input;
	while(true){
		st++;
		auto b = step(a);
		if(isEq(a,b)){
			// print_cuc(b); // for printing final state
			return st;
		}
		a = b;
	}
	return -1;
}

ll second() {
	cout << "That's all folks ;)" << endl;
	return 0;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
