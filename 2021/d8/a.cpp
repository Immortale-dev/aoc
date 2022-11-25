#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

struct Inp {
	vector<string> in;
	vector<string> out;
};

vector<Inp> input;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " | ");
		input.push_back({split_line(arr[0], " "), split_line(arr[1], " ")});
	}
}

vector<string> filter_input_digits(vector<string>& words, int length, string chars) {
	vector<string> ret;
	for(string w : words) {
		bool good = true;
		if(w.size() != length) continue;
		for(auto c : chars){
			string fs;
			fs.push_back(c);
			if(w.find(fs) == string::npos){
				good = false;
			}
		}
		if(good){
			ret.push_back(w);
		}
	}
	return ret;
}

ll first() {
	ll ret = 0;
	for(auto& it : input) {
		for(auto& o : it.out) {
			if(o.size() == 2 || o.size() == 3 || o.size() == 4 || o.size() == 7) {
				ret ++;
			}
		}
	}
	return ret;
}

ll second() {
	int ret = 0;
	for(auto& it : input){
		// define all digits
		vector<string> digits(10);
		digits[1] = filter_input_digits(it.in, 2, "")[0];
		digits[4] = filter_input_digits(it.in, 4, "")[0];
		digits[7] = filter_input_digits(it.in, 3, "")[0];
		digits[8] = filter_input_digits(it.in, 7, "")[0];
		digits[3] = filter_input_digits(it.in, 5, digits[1])[0];
		digits[9] = filter_input_digits(it.in, 6, digits[4])[0];
		
		string four_else = "";
		for(int i=0;i<digits[4].size();i++){
			char c = digits[4][i];
			if(c != digits[1][0] && c != digits[1][1]) {
				four_else += c;
			}
		}
		
		digits[5] = filter_input_digits(it.in, 5, four_else)[0];
		
		vector<string> maybe_two = filter_input_digits(it.in, 5, "");
		for(auto& x : maybe_two) {
			if(x != digits[5] && x != digits[3]) {
				digits[2] = x;
			}
		}
		
		vector<string> maybe_zero = filter_input_digits(it.in, 6, digits[1]);
		if(maybe_zero[0] == digits[9]) {
			digits[0] = maybe_zero[1];
		} else {
			digits[0] = maybe_zero[0];
		}
		
		vector<string> maybe_six = filter_input_digits(it.in, 6, four_else);
		if(maybe_six[0] == digits[9]) {
			digits[6] = maybe_six[1];
		} else {
			digits[6] = maybe_six[0];
		}
		
		// Get number
		int number = 0;
		for(auto& x : it.out) {
			for(int i=0;i<10;i++){
				vector<string> temp_input = {x};
				if(filter_input_digits(temp_input, digits[i].size(), digits[i]).size()) {
					number *= 10;
					number += i;
					break;
				}
			}
		}
		ret += number;
	}
	return ret;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
