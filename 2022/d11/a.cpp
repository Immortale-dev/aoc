#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ll;

#include "../helpers/string_helpers.cpp"
#include "monkey.cpp"

//=======================================//

vector<Monkey> monkeys;
vector<ll> all_divs;

void prepare() {
	string s;
	int stage = 0;
	Oper op;
	int test_true, test_false;
	ll divisible;
	queue<ll> list;
	while(getline(cin, s)){
		if (s == "") continue;
		switch(stage) {
			case 0:
				// just monkey index
				break;
			case 1:
			{
				list = queue<ll>();
				vector<string> temp_list = split_line(split_line(s, ": ")[1], ", ");
				for(auto item : temp_list) {
					list.push(stoll(item));
				}
				break;
			}
			case 2:
			{
				auto op_t = split_line(s, " = ")[1];
				auto tmp = split_line(op_t, " ");
				string item_second = tmp[tmp.size()-1];
				char op_c;
				
				if (split_line(op_t, "+").size() > 1) {
					op_c = '+';
				} else {
					op_c = '*';
				}
				op = {op_c, item_second == "old" ? make_pair(true, 0LL) : make_pair(false, stoll(item_second))};
				break; 
			}
			case 3:
			{
				auto arr = split_line(s, " ");
				divisible = stoll(arr[arr.size()-1]);
				break;
			}
			case 4:
			{
				auto arr = split_line(s, " ");
				test_true = stoll(arr[arr.size()-1]);
				break;
			}
			case 5:
			{
				auto arr = split_line(s, " ");
				test_false = stoll(arr[arr.size()-1]);
				all_divs.push_back(divisible);
				monkeys.push_back(Monkey(list, op, divisible, test_true, test_false));
				break;
			}
		}
		stage = (stage+1) % 6;
	}
}

ll first() {
	auto monks = vector<Monkey>(monkeys.begin(), monkeys.end());
	vector<int> m_items(monks.size(), 0);
	for(int i=0;i<20;i++) {
		int m_ind = 0;
		for(auto &m : monks) {
			while(!m.empty()) {
				m_items[m_ind]++;
				auto item = m.throw_item();
				monks[item.second].catch_item(item.first);
			}
			m_ind++;
		}
	}
	sort(m_items.begin(), m_items.end(), greater<int>());
	return m_items[0] * m_items[1];
}

ll second() {
	ll modulo = 1;
	for(auto it : all_divs) {
		modulo *= it;
	}
	auto monks = vector<Monkey>(monkeys.begin(), monkeys.end());
	vector<ll> m_items(monks.size(), 0);
	for(int i=0;i<10000;i++) {
		int m_ind = 0;
		for(auto &m : monks) {
			while(!m.empty()) {
				m_items[m_ind]++;
				auto item = m.throw_item(1);
				monks[item.second].catch_item(item.first%modulo);
			}
			m_ind++;
		}
	}
	sort(m_items.begin(), m_items.end(), greater<int>());
	return m_items[0] * m_items[1];
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
