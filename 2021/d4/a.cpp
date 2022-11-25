#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<int> numbers;
vector<vector<pair<int, bool> > > boards;
map<int, int> wins;

void prepare() {
	string s;
	getline(cin, s);
	auto arr_numbers = split_line(s, ",");
	transform(arr_numbers.begin(), arr_numbers.end(), back_inserter(numbers), [](string n)->int{ return stoi(n); });
	
	getline(cin, s); // \n
	
	string other="";
	while(getline(cin, s)){
		if(s == "") {
			other.pop_back();
			vector<pair<int, bool> > b;
			stringstream st(other);
			for(int i=0;i<25;i++) {
				int a;
				st >> a;
				b.push_back(make_pair(a, false));
			}
			boards.push_back(b);
			other = "";
		} else {
			other += s+" ";
		}
	}
	
	for(auto& it : boards) {
		assert(it.size() == 25);
	}
}

void reset() {
	for(auto& b : boards) {
		for(auto& it : b) {
			it.second = false;
		}
	}
}

void mark_boards(int n) {
	for(auto& b : boards) {
		for(int i=0;i<b.size();i++) {
			if(b[i].first == n) {
				b[i].second = true;
			}
		}
	}
}

vector<pair<int, bool>>* get_first_win_board() {
	for(auto& b : boards) {
		for(int i=0;i<5;i++) {
			bool good = true;
			for(int j=0;j<5;j++) {
				good &= b[i*5+j].second;
			}
			if(good){
				return &b;
			}
			
			good = true;
			for(int j=0;j<5;j++) {
				good &= b[j*5+i].second;
			}
			if(good){
				return &b;
			}
		}
	}
	return nullptr;
}

vector<pair<int, bool>>* get_last_win_board() {
	bool allwin = true;
	int b_ind = 0;
	for(auto& b : boards) {
		bool was_win = false;
		for(int i=0;i<5;i++) {
			bool good = true;
			for(int j=0;j<5;j++) {
				good &= b[i*5+j].second;
			}
			was_win |= good;
			
			good = true;
			for(int j=0;j<5;j++) {
				good &= b[j*5+i].second;
			}
			was_win |= good;
		}
		if(was_win){
			wins[b_ind]++;
		}
		allwin &= was_win;
		b_ind++;
	}
	if(allwin) {
		for(auto& it : wins){
			if(it.second == 1){
				return &boards[it.first];
			}
		}
	}
	return nullptr;
}

ll first() {
	for(auto n : numbers) {
		mark_boards(n);
		auto* win_board = get_first_win_board();
		if(win_board) {
			auto& b = *win_board;
			ll sum_unmarked = 0;
			for(auto& it : b){
				if(!it.second) {
					sum_unmarked += it.first;
				}
			}
			return sum_unmarked * n;
		}
	}
	assert(false);
	return 0;
}

ll second() {
	reset();
	for(auto n : numbers) {
		mark_boards(n);
		auto* win_board = get_last_win_board();
		if(win_board) {
			auto& b = *win_board;
			ll sum_unmarked = 0;
			for(auto& it : b){
				if(!it.second) {
					sum_unmarked += it.first;
				}
			}
			return sum_unmarked * n;
		}
	}
	assert(false);
	return 0;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
