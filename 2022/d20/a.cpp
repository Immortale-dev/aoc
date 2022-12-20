#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<int> values;

void prepare() {
	string s;
	while(getline(cin, s)){
		values.push_back(stoi(s));
	}
}

void print_q(list<ll>& q) {
	for(auto& it : q) {
		cout << it << " ";
	}
	cout << endl;
}

list<ll>::iterator does_move(list<ll>& q, list<ll>::iterator it) {
	auto nit = it;
	ll num = *it;
	ll moves = abs(num)%(values.size()-1);
	if (num >= 0) moves++;
	while(moves--) {
		num >= 0 ? ++nit : --nit;
		if (nit == it) moves++;
		if (nit == q.end()) moves++;
	}
	auto rit = q.insert(nit, *it);
	q.erase(it);
	return rit;
}

ll first() {
	list<ll> q(values.begin(), values.end());
	vector<list<ll>::iterator> its;
	auto it = q.begin();
	do {
		its.push_back(it);
		++it;
	} while(it != q.end());
	
	for(auto &it : its) {
		it = does_move(q, it);
	}
	
	it = q.begin();
	while(it != q.end() && (*it) != 0) ++it;
	
	ll result = 0;
	for(int j=0;j<3;j++) {
		for(int i=0;i<1000;i++) {
			++it;
			if (it == q.end()) { 
				it = q.begin();
			}
		}
		result += *it;
	}
	
	return result;
}

ll second() {
	vector<ll> new_values(values.size());
	transform(values.begin(), values.end(), new_values.begin(), [](auto& value){ return (ll)value*811589153LL; });
	
	list<ll> q(new_values.begin(), new_values.end());
	vector<list<ll>::iterator> its;
	auto it = q.begin();
	do {
		its.push_back(it);
		++it;
	} while(it != q.end());
	
	for(int i=0;i<10;i++) {
		for(auto &it : its) {
			it = does_move(q, it);
		}
	}
	
	it = q.begin();
	while(it != q.end() && (*it) != 0) ++it;
	
	ll result = 0;
	for(int j=0;j<3;j++) {
		for(int i=0;i<1000;i++) {
			++it;
			if (it == q.end()) { 
				it = q.begin();
			}
		}
		result += *it;
	}
	
	return result;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
