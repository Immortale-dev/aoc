#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

vector<int> input;

void prepare() {
	string s;
	while(getline(cin, s)){
		input.push_back(stoi(s));
	}
}

int calc(vector<int> arr) {
	int ret = 0;
	for(int i=1;i<arr.size();i++){
		if(arr[i] > arr[i-1]) ++ret;
	}
	return ret;
}

int first() {
	return calc(input);
}

int second() {
	vector<int> sums;
	for(int i=2;i<input.size();i++){
		sums.push_back(input[i] + input[i-1] + input[i-2]);
	}
	return calc(sums);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
