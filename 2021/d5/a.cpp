#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

struct pt {
	int x;
	int y;
};

struct pipe {
	pt start;
	pt finish;
};

vector<pipe> input;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " -> ");
		auto start_arr = split_line(arr[0], ",");
		auto finish_arr = split_line(arr[1], ",");
		
		pt pt_start = {stoi(start_arr[0]), stoi(start_arr[1])};
		pt pt_end = {stoi(finish_arr[0]), stoi(finish_arr[1])};
		
		input.push_back({pt_start, pt_end});
	}
}

int count_overlap(vector<pipe>& inp) {
	vector<vector<int>> field(1000, vector<int>(1000));
	for(auto& it : inp) {
		if(it.start.x == it.finish.x) {
			for(int i=min(it.start.y, it.finish.y);i<=max(it.start.y, it.finish.y);i++) {
				field[i][it.start.x]++;
			}
		} else if(it.start.y == it.finish.y) {
			for(int i=min(it.start.x, it.finish.x);i<=max(it.finish.x, it.start.x);i++) {
				field[it.start.y][i]++;
			}
		} else {
			int length = abs(it.start.x-it.finish.x);
			for(int i=0;i<=length;i++){
				int x = it.start.x + i*(it.start.x > it.finish.x ? -1 : 1);
				int y = it.start.y + i*(it.start.y > it.finish.y ? -1 : 1);
				field[y][x]++;
			}
		}
	}
	
	int res = 0;
	for(int i=0;i<1000;i++) {
		for(int j=0;j<1000;j++) {
			if(field[i][j] > 1) {
				res++;
			}
		}
	}
	
	return res;
}

ll first() {
	vector<pipe> input_filtered;
	for(auto& it : input) {
		if(it.start.x == it.finish.x || it.start.y == it.finish.y) {
			input_filtered.push_back(it);
		}
	}
	
	return count_overlap(input_filtered);
}

ll second() {
	return count_overlap(input);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
