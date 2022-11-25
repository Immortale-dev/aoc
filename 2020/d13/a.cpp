#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#include "../helpers/string_helpers.cpp"

int a;
vector<ll> arr;
vector<ll> offsets;
ll MX = 100000000000000;

void prepare()
{
	string s;
	cin >> a >> s;
	auto res = split_line(s,",");
	int off = 0;
	for(auto& it : res){
		if(it == "x"){
			off++;
			continue;
		}
		arr.push_back(stoi(it));
		offsets.push_back(off);
		off++;
	}
}

int first()
{
	int min_ind = 0;
	int min = 99999999;
	for(int i=0;i<arr.size();i++){
		int it = arr[i];
		int b = (it-a%it);
		if(b < min){
			min = b;
			min_ind = i;
		}
	}
	return arr[min_ind] * (arr[min_ind]-a%arr[min_ind]);
}

ll second()
{
	int sz = arr.size();
	vector<pair<int,int>> nums;
	for(int i=0;i<sz;i++){
		if(!i) continue;
		nums.push_back(make_pair(arr[i], arr[i] - offsets[i]%arr[i]));
	}
	sort(nums.begin(), nums.end());
	
	ll tm = 0;
	ll m = arr[0];
	for(auto& it : nums){
		while( (tm % it.first) != it.second ){
			tm += m;
		}
		m *= it.first;
	}
	return tm;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
