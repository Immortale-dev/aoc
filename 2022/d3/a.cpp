#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<int>> rucksacks;

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<int> rucksack;
		for(size_t i=0;i<s.size();i++) {
			int prior;
			if (s[i]-'a' < 0) {
				prior = s[i]-'A'+26+1;
			} else {
				prior = s[i]-'a'+1;
			}
			rucksack.push_back(prior);
		}
		rucksacks.push_back(rucksack);
	}
}

ll first() {
	ll sum = 0;
	for(auto& ruck : rucksacks) {
		unordered_set<int> rset;
		for(size_t i=0;i<ruck.size()/2;i++) {
			rset.insert(ruck[i]);
		}
		for(size_t i=ruck.size()/2;i<ruck.size();i++) {
			if (rset.count(ruck[i])) {
				sum += ruck[i];
				break;
			}
		}
	}
	return sum;
}

ll second() {
	ll sum=0;
	int ind=0;
	unordered_map<int, int> rset;
	for(auto& ruck : rucksacks) {
		for(int item : ruck) {
			if (rset[item] == ind) {
				rset[item]++;
			}
		}
		if(ind == 2) {
			bool found = false;
			for(auto& it : rset) {
				if (it.second == 3) {
					sum += it.first;
					found = true;
				}
			}
			rset.clear();
			if (!found) {
				throw logic_error("Badge not found");
			}
		}
		ind = (ind+1)%3;
	}
	return sum;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
