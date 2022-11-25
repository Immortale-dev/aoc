#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

vector<string> input;

void prepare()
{
	string s;
	while(getline(cin,s)){
		input.push_back(s);
	}
}

pair<int,int> findPass(string s)
{
	int mn=0,mx=127,md;
	int mnh=0,mxh=7,mdh;
	for(int i=0;i<s.size();i++){
		char c = s[i];
		if(c == 'F') mx = (mn+mx)/2;
		if(c == 'B') mn = (mn+mx)/2+1;
		if(c == 'L') mxh = (mnh+mxh)/2;
		if(c == 'R') mnh = (mnh+mxh)/2+1;
	}
	return make_pair(mn,mnh);
}

int first()
{
	int maxpass = 0;
	for(auto &pass : input){
		auto p = findPass(pass);
		maxpass = max(maxpass, p.first*8+p.second);
	}
	return maxpass;
}

int second()
{
	bool arr[128*8];
	for(int i=0;i<128*8;i++) arr[i] = false;
	for(auto& pass : input){
		auto p = findPass(pass);
		arr[p.first*8+p.second] = true;
	}
	for(int i=1;i<128*8;i++){
		if(!arr[i] && arr[i-1]){
			return i;
		}
	}
	return -1;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
