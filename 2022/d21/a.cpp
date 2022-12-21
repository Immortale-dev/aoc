#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Monkey {
	string name;
	bool yelling;
	ll number;
	pair<string, string> monks;
	string op;
};

vector<Monkey> monkeys;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, ": ");
		auto arrn = split_line(arr[1], " ");
		if (arrn.size() == 1) {
			// yelling
			monkeys.push_back({arr[0], true, stoi(arr[1])});
		} else {
			monkeys.push_back({arr[0], false, 0, {arrn[0], arrn[2]}, arrn[1]});
		}
	}
}

ll req_mon(map<string, Monkey>& hash, map<string, ll>& res, string name) {
	if (res.count(name)) return res[name];
	auto &monk = hash[name];
	if (monk.yelling) {
		res[name] = monk.number;
		return monk.number;
	}
	ll res_num;
	if (monk.op == "+") {
		res_num = req_mon(hash, res, monk.monks.first) + req_mon(hash, res, monk.monks.second);
	} else if (monk.op == "-") {
		res_num = req_mon(hash, res, monk.monks.first) - req_mon(hash, res, monk.monks.second);
	} else if (monk.op == "*") {
		res_num = req_mon(hash, res, monk.monks.first) * req_mon(hash, res, monk.monks.second);
	} else if (monk.op == "/") {
		res_num = req_mon(hash, res, monk.monks.first) / req_mon(hash, res, monk.monks.second);
	} else {
		throw logic_error("Wrong operation");
	}
	res[name] = res_num;
	return res_num;
}

ll first() {
	map<string, Monkey> monkey_hash;
	map<string, ll> monkey_res;
	
	for(auto &m : monkeys) {
		monkey_hash.insert({m.name, m});
	}
	
	return req_mon(monkey_hash, monkey_res, "root");
}

ll second() {
	ll mn = 0, mx = 300000000000000;
	
	map<string, Monkey> monkey_hash;
	map<string, ll> monkey_res;
	
	for(auto &m : monkeys) {
		monkey_hash.insert({m.name, m});
	}
	
	string M1 = monkey_hash["root"].monks.first;
	string M2 = monkey_hash["root"].monks.second;
	
	monkey_hash["humn"].number = mn;
	ll mon1mn = req_mon(monkey_hash, monkey_res, M1);
	ll mon2mn = req_mon(monkey_hash, monkey_res, M2);
	
	monkey_res.clear();
	monkey_hash["humn"].number = mx;
	ll mon1mx = req_mon(monkey_hash, monkey_res, M1);
	ll mon2mx = req_mon(monkey_hash, monkey_res, M2);
	
	bool do_swap = mon1mn == mon1mx;
	bool dir = mon1mn == mon1mx ? mon2mn > mon1mn : mon1mn > mon2mn;
	
	while(mn < mx) {
		ll md = (mn+mx)/2;
		
		monkey_res.clear();
		monkey_hash["humn"].number = md;
		
		ll mon1 = req_mon(monkey_hash, monkey_res, M1);
		ll mon2 = req_mon(monkey_hash, monkey_res, M2);
		
		if (do_swap) swap(mon1, mon2);
		
		if (mon1 > mon2 && dir || mon1 < mon2 && !dir) {
			mn = md+1;
		} else {
			mx = md;
		}
	}
	
	return mn;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
