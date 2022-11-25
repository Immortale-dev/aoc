#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

const int SIZE = 220;
string enhance_map;
vector<vector<bool>> input(SIZE, vector<bool>(SIZE, false));

void prepare() {
	string s;
	getline(cin, enhance_map);
	getline(cin, s); // empty line
	int startx = 60;
	int starty = 60;
	int i=0;
	while(getline(cin, s)){
		for(int j=0;j<s.size();j++) {
			input[starty+i][startx+j] = s[j] == '#';
		}
		i++;
	}
}

void enhance(vector<vector<bool>>& arr, string& emap, bool& outer) {
	vector<vector<bool>> new_arr(SIZE, vector<bool>(SIZE));
	
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			int num = 0;
			for(int k=0;k<9;k++){
				int ry = i+k/3-1;
				int rx = j+k%3-1;
				
				bool bit = outer;
				if(ry >= 0 && ry < SIZE && rx >= 0 && rx < SIZE){
					bit = arr[ry][rx];
				}
				num |= (bit << (8-k));
				new_arr[i][j] = emap[num] == '#';
			}
		}
	}
	if(!outer && emap[0]=='#') outer = true;
	else if(outer && emap[511]=='.') outer = false;
	
	arr = new_arr;
}

void print_image(vector<vector<bool>>& arr, int x1, int y1, int x2, int y2) {
	cout << endl;
	for(int i=y1;i<=y2;i++){
		for(int j=x1;j<=x2;j++){
			cout << (arr[i][j] ? '#' : '.');
		}
		cout << endl;
	}
}

ll first() {
	auto arr = input;
	bool out_pixel = 0;
	
	enhance(arr, enhance_map, out_pixel);
	enhance(arr, enhance_map, out_pixel);
	
	ll res = 0;
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			res += arr[i][j];
		}
	}
	return res;
}

ll second() {
	auto arr = input;
	bool out_pixel = 0;
	
	for(int i=0;i<50;i++){
		enhance(arr, enhance_map, out_pixel);
	}
	
	//print_image(arr, 0,0,210,210);
	
	ll res = 0;
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			res += arr[i][j];
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
