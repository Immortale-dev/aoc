#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

unordered_map<string, unordered_map<string, int>> arr;
unordered_set<string> checked;
unordered_set<string> arr_has;

const string FIND = "shiny gold";

void prepare()
{
	string s;
	while(getline(cin, s)){
		auto l = split_line(s, " contain ");
		
		// bag
		auto f = split_line(l[0], " ");
		f.pop_back();
		string bag = join_line(f, " ");
		
		//cout << "BAG: " << bag << endl;
		
		// contains
		unordered_map<string, int> bags;
		auto tArr = split_line(l[1], ", ");
		for(auto b : tArr){
			auto sbag = split_line(b, " ");
			sbag.pop_back();
			//cout << "---" << sbag[0] << endl;
			if(sbag[0] == "no") break;
			int c = stoi(sbag[0]);
			sbag.erase(sbag.begin());
			string bag = join_line(sbag, " ");
			bags[bag] = c;
		}
		
		arr[bag] = bags;
	}
}

bool dfsHas(string start)
{
	if(checked.count(start)) return arr_has.count(start);
	
	checked.insert(start);
	if(arr[start].count(FIND)){
		arr_has.insert(start);
		return true;
	}
	
	bool has = false;
	for(auto it : arr[start]){
		has |= dfsHas(it.first);
	}
	
	if(has){
		arr_has.insert(start);
		return true;
	}
	
	return false;
}

int dfsCount(string a)
{
	int res = 1;
	for(auto& it : arr[a]){
		res += it.second * dfsCount(it.first);
	}
	return res;
}

int first()
{
	for(auto& it : arr){
		if(it.first == FIND) continue;
		dfsHas(it.first);
	}
	return arr_has.size();
}

int second()
{
	return dfsCount(FIND)-1;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
