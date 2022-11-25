#include <bits/stdc++.h>

using namespace std;

const int COUNT = 1000;

struct inp{
	int from, to;
	char c;
	string password;
};
vector<inp> input;

void prepare()
{
	for(int i=0;i<COUNT;i++){
		string a,b,c;
		cin >> a >> b >> c;
		inp p;
		int delim = a.find("-");
		p.from = stoi(a.substr(0,delim));
		p.to = stoi(a.substr(delim+1));
		p.c = b[0];
		p.password = c;
		input.push_back(p);
	}
}

int first()
{
	int res = 0;
	for(auto& it : input){
		int cnt = 0;
		for(int i=0;i<it.password.size();i++){
			if(it.password[i] == it.c){
				cnt++;
			}
		}
		if(cnt >= it.from && cnt <= it.to){
			++res;
		}
	}
	return res;
}

int second()
{
	int res = 0;
	for(auto &it : input){
		if(it.password[it.from-1] == it.c && it.password[it.to-1] != it.c || it.password[it.from-1] != it.c && it.password[it.to-1] == it.c ){
			++res;
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
