#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(string) codes = UNTIL_END();
};

Input input(std::cin);

map<char, pair<int,int>> keypad{
	{'7',{0,0}}, {'8',{0,1}}, {'9',{0,2}},
	{'4',{1,0}}, {'5',{1,1}}, {'6',{1,2}},
	{'1',{2,0}}, {'2',{2,1}}, {'3',{2,2}},
	             {'0',{3,1}}, {'A',{3,2}},
};

map<char, pair<int,int>> remote{
	            {'^',{0,1}},{'A',{0,2}},
	{'<',{1,0}},{'v',{1,1}},{'>',{1,2}},
};

pair<string,string> pos_to_dirs(pair<int,int> curr, pair<int,int> targ) {
	auto [cy,cx] = curr;
	auto [ty,tx] = targ;
	char pv = cy < ty ? 'v' : '^';
	char ph = cx < tx ? '>' : '<';
	string h = "";
	string v = "";
	for (int i=0;i<abs(ty-cy);i++) v.push_back(pv);
	for (int i=0;i<abs(tx-cx);i++) h.push_back(ph);
	return {v,h};
}

string keypad_dirs(char curr, char targ) {
	auto [v,h] = pos_to_dirs(keypad[curr], keypad[targ]);
	if (!v.size()) return h;
	if (!h.size()) return v;
	if ((curr == '7' || curr == '4' || curr == '1') && (targ == '0' || targ == 'A')) return h+v;
	if ((curr == '0' || curr == 'A') && (targ == '7' || targ == '4' || targ == '1')) return v+h;
	if (h[0] == '<') return h+v;
	return v+h;
}

string remote_dirs(char curr, char targ) {
	auto [v,h] = pos_to_dirs(remote[curr], remote[targ]);
	if (!v.size()) return h;
	if (!h.size()) return v;
	if (curr == '<' && (targ == '^' || targ == 'A')) return h+v;
	if ((curr == '^' || curr == 'A') && targ == '<') return v+h;
	if (h[0] == '<') return h+v;
	return v+h;
}

int get_hash(char curr, char targ) {
	return curr * 1000 + targ;
}

vector<map<string,ll>> dp(30);
ll get_size(string str, int depth) {
	if (dp[depth].count(str)) return dp[depth][str];
	if (depth == 0) return str.size();
	ll res = 0;
	for (int i=0;i<str.size();i++) {
		char curr = i > 0 ? str[i-1] : 'A';
		char targ = str[i];
		res += get_size(remote_dirs(curr, targ)+"A", depth-1);
	}
	dp[depth][str] = res;
	return res;
}

string get_keys(string &code, function<string(char,char)> fn_dirs, char& pos) {
	string res;
	for (auto c : code) {
		string keys = fn_dirs(pos, c);
		res += keys + "A";
		pos = c;
	}
	return res;
}

string keypad_keys(string code, char &pos) {
	return get_keys(code, keypad_dirs, pos);
}

string remote_keys(string code, char &pos) {
	return get_keys(code, remote_dirs, pos);
}

struct Step {
	int v,h,o;
};

ll first() {
	ll res = 0;
	char r0 = 'A';
	char r1 = 'A';
	char r2 = 'A';

	for (auto s : input.codes) {
		string str = s;
		str = keypad_keys(str, r0);
		str = remote_keys(str, r1);
		str = remote_keys(str, r2);
		res += stoi(s) * str.size();
	}

	return res;
}

ll second() {
	ll res = 0;
	char r0 = 'A';
	for (auto s : input.codes) {
		string str = s;
		str = keypad_keys(str, r0);
		ll lres = get_size(str, 25);
		res += lres * stoi(s);
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
