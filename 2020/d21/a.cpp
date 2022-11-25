#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

struct Case{
	unordered_set<string> ingr;
	unordered_set<string> alle;
};

vector<Case> input;

void prepare()
{
	string s;
	while(getline(cin, s)){
		Case c;
		auto arr = split_line(s, " (");
		auto ingr_vec = split_line(arr[0], " ");
		string str = arr[1];
		str.pop_back();
		str = str.substr(9);
		auto alle_vec = split_line(str, ", ");
		c.ingr = unordered_set<string>(ingr_vec.begin(), ingr_vec.end());
		c.alle = unordered_set<string>(alle_vec.begin(), alle_vec.end());
		input.push_back(c);
	}
}

string find_ingr(string a)
{
	unordered_set<string> ss;
	bool inited = false;
	for(auto& it : input){
		if(!it.alle.count(a)) continue;
		if(!inited){
			inited = true;
			ss = unordered_set<string>(it.ingr.begin(), it.ingr.end());
			continue;
		}
		
		vector<string> del;
		for(auto& v : ss){
			if(!it.ingr.count(v)){
				del.push_back(v);
			}
		}
		for(auto& v : del){
			ss.erase(v);
		}
	}
	
	if(ss.empty()) throw runtime_error("No Way!");
	if(ss.size() > 1) return "";
	
	return *ss.begin();
}

void remove_alle(string a)
{
	for(auto& it : input){
		it.alle.erase(a);
	}
}

void remove_ingr(string a)
{
	for(auto& it : input){
		it.ingr.erase(a);
	}
}

vector<pair<string, string>> lst;

bool prepared = false;
void prepare_other()
{
	if(prepared) return;
	
	prepared = true;
	unordered_set<string> ss;
	for(auto& it : input){
		for(auto& v : it.alle){
			ss.insert(v);
		}
	}
	
	vector<string> vec(ss.begin(), ss.end());
	
	for(int i=0;i<vec.size();i++){
		for(int j=0;j<vec.size();j++){
			string a = vec[j];
			if(!ss.count(a)) continue;
			
			string b = find_ingr(a);
			if(b != ""){
				lst.push_back(make_pair(a,b));
				ss.erase(a);
				remove_alle(a);
				remove_ingr(b);
			}
		}
	}
}

int first()
{
	prepare_other();

	int res = 0;
	for(auto& it : input){
		res += it.ingr.size();
	}
	
	return res;
}

string second()
{
	prepare_other();
	
	sort(lst.begin(), lst.end());
	
	string ss = "";
	for(auto& it : lst){
		ss += it.second + ",";
	}
	ss.pop_back();
	
	return ss;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
