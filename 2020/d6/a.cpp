#include <bits/stdc++.h>

typedef long long int ll;

using namespace std;

vector<unordered_map<char, int>> input;
vector<int> counts;

void prepare()
{
	string s;
	unordered_map<char, int> q;
	int cnt = 0;
	while(getline(cin, s)){
		if(s == ""){
			input.push_back(q);
			counts.push_back(cnt);
			q = unordered_map<char, int>();
			cnt = 0;
			continue;
		}
		cnt++;
		for(int i=0;i<s.size();i++){
			q[s[i]]++;
		}
	}
	input.push_back(q);
	counts.push_back(cnt);
}

int first()
{
	int sum = 0;
	for(auto &it : input){
		sum += it.size();
	}
	return sum;
}

int second()
{
	int sum = 0;
	int i=0;
	for(auto &it : input){
		for(auto &p : it){
			if(p.second == counts[i])
				sum++;
		}
		i++;
	}
	return sum;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
