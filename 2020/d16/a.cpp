#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef unsigned long long int ll;
struct rule{
	string name;
	vector<pair<int,int>> ranges;
};

struct {
	vector<rule> rules;
	vector<int> ticket;
	vector<vector<int>> tickets;
} input;

void prepare()
{
	int state = 0;
	string s;
	while(getline(cin, s)){
		if(s == ""){
			state++;
			continue;
		}
		if(state == 0){
			auto r = split_line(s, ": ");
			rule ru;
			ru.name = r[0];
			
			auto rngs = split_line(r[1], " or ");
			auto r1 = split_line(rngs[0], "-");
			auto r2 = split_line(rngs[1], "-");
			ru.ranges.push_back(make_pair(stoi(r1[0]), stoi(r1[1])));
			ru.ranges.push_back(make_pair(stoi(r2[0]), stoi(r2[1])));
			
			input.rules.push_back(ru);
		}
		if(state == 1){
			if(s == "your ticket:") continue;
			auto arr = split_line(s, ",");
			for(auto& it : arr){
				input.ticket.push_back(stoi(it));
			}
		}
		if(state == 2){
			if(s == "nearby tickets:") continue;
			vector<int> vec;
			auto arr = split_line(s, ",");
			for(auto& it : arr){
				vec.push_back(stoi(it));
			}
			input.tickets.push_back(vec);
		}
	}
}

int first()
{
	vector<int> nums;
	vector<vector<int>> new_tickets;
	for(auto& it : input.tickets){
		bool t_good = true;
		for(auto& n : it){
			bool good = false;
			for(auto& k : input.rules){
				if(n >= k.ranges[0].first && n <= k.ranges[0].second || n >= k.ranges[1].first && n <= k.ranges[1].second){
					good = true;
					break;
				}
			}
			if(!good){
				nums.push_back(n);
				t_good = false;
			}
		}
		if(t_good){
			new_tickets.push_back(it);
		}
	}
	int res = 0;
	for(auto& it : nums){
		res += it;
	}
	input.tickets = new_tickets;
	return res;
}

ll second()
{
	unordered_map<string, unordered_set<int>> m;
	for(int r=0;r<input.rules.size();r++){
		for(int i=0;i<input.ticket.size();i++){
			bool good = true;
			for(int j=0;j<input.tickets.size();j++){
				int val = input.tickets[j][i];
				if( (val < input.rules[r].ranges[0].first || val > input.rules[r].ranges[0].second) && (val < input.rules[r].ranges[1].first || val > input.rules[r].ranges[1].second) ){
					good = false;
					break;
				}
			}
			if(good){
				m[input.rules[r].name].insert(input.ticket[i]);
			}
		}
	}
	
	unordered_map<string, int> result;
	
	while(!m.empty()){
		for(auto& it : m){
			if(it.second.size() == 1){
				int val = *it.second.begin();
				result[it.first] = val;
				for(auto& r : m){
					r.second.erase(val);
				}
				m.erase(it.first);
				break;
			}
		}
	}
	
	ll res = 1;
	for(auto& it : result){
		if(it.first.find("departure") == 0){
			res = res * (ll)it.second;
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
