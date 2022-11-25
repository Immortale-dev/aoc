#include <bits/stdc++.h>

using namespace std;

vector<int> input;

typedef long long int ll;

void prepare()
{
	string s;
	while(getline(cin, s)){
		input.push_back(stoi(s));
	}
	input.push_back(0);
	sort(input.begin(), input.end());
	input.push_back(input[input.size()-1]+3);
}

int first()
{
	int j1 = 0;
	int j3 = 0;
	
	for(int i=0;i<input.size()-1;i++){
		if(input[i+1] - input[i] == 1){
			j1++;
		} else if(input[i+1] - input[i] == 3){
			j3++;
		}
	}
	
	return j1*j3;
}

ll second()
{
	int mx = input[input.size()-1];
	ll dp[mx+5];
	for(int i=1;i<=mx;i++){
		dp[i] = 0;
	}
	dp[0] = 1;
	for(auto &it : input){
		for(int j=1;j<=3;j++){
			if(it-j >= 0){
				dp[it] += dp[it-j];
			}
		}
	}
	return dp[mx];
}

int main()
{
	prepare();
	cout << "First: " << first() << endl; 
	cout << "Second: " << second() << endl;
	return 0;
}
