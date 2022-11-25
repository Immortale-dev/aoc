#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

vector<string> mess;

struct rule{
	bool end;
	char c;
	vector<vector<int>> r;
};

unordered_map<int, rule> rules;
unordered_map<int, unordered_set<string>> dp;

void prepare()
{
	bool msgs = false;
	string s;
	while(getline(cin, s)){
		if(s == ""){
			msgs = true;
			continue;
		}
		if(!msgs){
			auto rl = split_line(s, ": ");
			int ri = stoi(rl[0]);
			
			if(rl[1][0] == '"'){
				rules[ri] = {true, rl[1][1], {}};
			} else {
				auto rls = split_line(rl[1], " | ");
				vector<vector<int>> list;
				for(auto& it : rls){
					auto vec = split_line(it, " ");
					vector<int> v;
					for(auto& k : vec){
						v.push_back(stoi(k));
					}
					list.push_back(v);
				}
				
				rules[ri] = {false, '.', list};
			}
		} else {
			mess.push_back(s);
		}
	}
}

unordered_set<string> prepare_valid(int r)
{
	if(dp.count(r)) return dp[r];
	if(rules[r].end){
		unordered_set<string> res;
		string ss = "";
		ss.push_back(rules[r].c);
		res.insert(ss);
		return dp[r] = res;
	}
	unordered_set<string> res;
	for(auto& it : rules[r].r){
		unordered_set<string> loc;
		for(auto& rr : it){
			auto rs = prepare_valid(rr);
			if(loc.empty()){
				loc = rs;
				continue;
			}
			unordered_set<string> new_loc;
			for(auto& lr : loc){
				for(auto& ln : rs){
					new_loc.insert(lr+ln);
				}
			}
			loc = new_loc;
		}
		for(auto& lc : loc){
			res.insert(lc);
		}
	}
	return dp[r] = res;
}

bool check_valid_first(string s)
{
	if(s.size() != 24) return false;
	return dp[42].count(s.substr(0,8)) && dp[42].count(s.substr(8,8)) && dp[31].count(s.substr(16,8));
}

int first()
{
	//auto vec = prepare_valid(0);
	
	prepare_valid(42);
	prepare_valid(31);
	
	int res = 0;
	for(auto& it : mess){
		if(check_valid_first(it)) res++;
	}
	return res;
	
}

////////////////////////////////////////////////////////

bool check_valid_left(string s)
{
	for(int i=0;i<s.size();i+=8){
		if(!dp[42].count(s.substr(i,8))) return false;
	}
	return true;
}

bool check_valid_right(string s)
{
	if(s.size()%16) return false;
	if(!check_valid_left(s.substr(0, s.size()/2))) return false;
	for(int i=s.size()/2;i<s.size();i+=8){
		if(!dp[31].count(s.substr(i,8))) return false;
	}
	return true;
}

bool check_valid(string s){
	for(int i=8;i<s.size();i+=8){
		if(check_valid_left(s.substr(0,i)) && check_valid_right(s.substr(i))) return true;
	}
	return false;
}

int second()
{	
	prepare_valid(42);
	prepare_valid(31);
	
	int res = 0;
	for(auto& it : mess){
		if(check_valid(it)){
			res++;
		}
	}
	return res;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
