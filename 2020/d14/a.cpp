#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef unsigned long long int ull;

struct comm{
	bool is_mem;
	string mask;
	ull mem;
	ull val;
};

vector<comm> input;

void prepare()
{
	string s;
	while(getline(cin, s)){
		auto parts = split_line(s, " = ");
		if(parts[0] == "mask"){
			input.push_back({false, parts[1], 0, 0});
		} else {
			input.push_back({true, "", stoull(parts[0].substr(4,parts[0].size()-5)), stoull(parts[1])});
		}
	}
}

ull first()
{
	unordered_map<ull, ull> mem;
	string mask;
	for(auto& it : input){
		if(!it.is_mem){
			mask = it.mask;
		} else {
			ull bit = 1;
			ull val = it.val;
			for(int i=mask.size()-1;i>=0;i--,bit<<=1){
				if(mask[i] == 'X') continue;
				if(mask[i] == '1' && !(val & bit) ){
					val = val | bit;
				}
				if(mask[i] == '0' && (val & bit)){
					val = val ^ bit;
				}
			}
			mem[it.mem] = val;
		}
	}
	ull res = 0;
	for(auto& it : mem){
		res += it.second;
	}
	return res;
}

void req(ull v, string& mask, int i, unordered_map<ull, ull>& mem, ull val)
{
	if(i >= mask.size()){
		mem[v] = val;
		return;
	}
	int ind = mask.size()-i-1;
	if(mask[ind] == '0'){
		req(v, mask, i+1, mem, val);
		return;
	}
	if(mask[ind] == '1'){
		req(v | (1LL << i), mask, i+1, mem, val);
		return;
	}
	req(v | (1LL << i), mask, i+1, mem, val);
	req(v & (((1LL<<50)-1LL)-(1LL<<i)), mask, i+1, mem, val);
}

ull second()
{
	unordered_map<ull, ull> mem;
	string mask;
	for(auto& it : input){
		if(!it.is_mem){
			mask = it.mask;
		} else {
			req(it.mem, mask, 0, mem, it.val);
		}
	}
	ull res = 0;
	for(auto& it : mem){
		res += it.second;
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
