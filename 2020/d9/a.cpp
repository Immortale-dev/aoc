#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

vector<ll> input;

void prepare()
{
	string s;
	while(getline(cin, s)){
		input.push_back(stoll(s));
	}
}

ll first()
{
	queue<ll> q;
	unordered_set<ll> vals;
	for(int i=0;i<25;i++){
		q.push(input[i]);
		vals.insert(input[i]);
	}
	for(int i=25;i<input.size();i++){
		ll val = input[i];
		bool found = false;
		for(auto it : vals){
			if(it*2 == val)
				continue;
			if(vals.count(val-it))
				found = true;
		}
		if(!found)
			return val;
		vals.erase(q.front());
		q.pop();
		q.push(val);
		vals.insert(val);
	}
	return 0;
}

ll second()
{
	ll a = first();
	int start = 0, finish=0;
	ll sum = input[0];
	while(start < input.size() && finish < input.size()){
		if(sum < a){
			sum += input[++finish];
		} else if (sum > a) {
			sum -= input[start++];
		} else {
			// found
			vector<int> nums;
			for(int i=start;i<=finish;i++){
				nums.push_back(input[i]);
			}
			sort(nums.begin(), nums.end());
			return nums[0]+nums[nums.size()-1];
		}
	}
	return 0;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
