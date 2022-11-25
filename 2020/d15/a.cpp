#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

vector<int> input;

void prepare()
{
	string s;
	cin >> s;
	auto arr = split_line(s, ",");
	for(auto& it : arr){
		input.push_back(stoi(it));
	}
}

int first()
{
	unordered_map<int,int> arr;
	int turn = 1;
	int last = input[input.size()-1];
	for(int i=0;i<input.size()-1;i++){
		int it = input[i];
		arr[it] = turn;
		turn++;
	}
	while(turn < 2020){
		int newlast;
		if(arr.count(last)){
			newlast = turn-arr[last];
		} else {
			newlast = 0;
		}
		arr[last] = turn;
		last = newlast;
		turn++;
	}
	return last;
}

int second()
{
	unordered_map<int,int> arr;
	int turn = 1;
	int last = input[input.size()-1];
	for(int i=0;i<input.size()-1;i++){
		int it = input[i];
		arr[it] = turn;
		turn++;
	}
	while(turn < 30000000){
		int newlast;
		if(arr.count(last)){
			newlast = turn-arr[last];
		} else {
			newlast = 0;
		}
		arr[last] = turn;
		last = newlast;
		turn++;
	}
	return last;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
