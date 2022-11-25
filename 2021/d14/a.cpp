#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

string templ;
map<string,char> poly;

void prepare() {
	string s;
	getline(cin, templ);
	getline(cin, s); // empty line
	while(getline(cin, s)){
		auto arr = split_line(s, " -> ");
		poly[arr[0]] = arr[1][0];
	}
}

map<string, ll> smart_step(map<string, ll>& pairs) {
	map<string, ll> new_pairs;
	for(auto& it : pairs) {
		if(poly.count(it.first)) {
			string s1="",s2="";
			s1.push_back(it.first[0]);
			s1.push_back(poly[it.first]);
			s2.push_back(poly[it.first]);
			s2.push_back(it.first[1]);
			new_pairs[s1] += it.second;
			new_pairs[s2] += it.second;
		} else {
			throw "wtf";
		}
	}
	return new_pairs;
}

vector<ll> get_chars_count(map<string, ll>& pairs) {
	map<char, ll> counts;
	for(auto& it : pairs) {
		counts[it.first[0]] += it.second;
		counts[it.first[1]] += it.second;
	}
	counts[templ[0]]++;
	counts[templ[templ.size()-1]]++;
	
	vector<ll> cnts;
	for(auto& it : counts) {
		cnts.push_back(it.second/2);
	}
	return cnts;
}

ll first() {
	string t = templ;
	map<string, ll> pairs;
	for(int i=0;i<t.size()-1;i++){
		pairs[t.substr(i,2)]++;
	}
	for(int i=0;i<10;i++) {
		pairs = smart_step(pairs);
	}
	
	auto chars_count = get_chars_count(pairs);
	sort(chars_count.begin(), chars_count.end());
	
	return chars_count[chars_count.size()-1] - chars_count[0];
}

ll second() {
	string t = templ;
	map<string, ll> pairs;
	for(int i=0;i<t.size()-1;i++){
		pairs[t.substr(i,2)]++;
	}
	for(int i=0;i<40;i++) {
		pairs = smart_step(pairs);
	}
	
	auto chars_count = get_chars_count(pairs);
	sort(chars_count.begin(), chars_count.end());
	
	return chars_count[chars_count.size()-1] - chars_count[0];
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
