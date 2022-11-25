#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<ll> input;
int bitnum;

void prepare() {
	string s;
	while(getline(cin, s)){
		ll num = 0;
		bitnum = s.size();
		for(int i=0;i<s.size();i++) {
			num <<= 1;
			num |= (s[i]-'0');
		}
		input.push_back(num);
	}
}

ll first() {
	ll gamma=0, epsilon=0;
	for(int i=bitnum-1;i>=0;i--) {
		int onec = 0;
		for(int j=0;j<input.size();j++) {
			onec += (input[j] >> i) & 1;
		}
		gamma <<= 1;
		gamma |= (onec > (input.size()/2));
		
		epsilon <<= 1;
		epsilon |= !(onec > (input.size()/2));
	}
	return gamma * epsilon;
}

ll second() {
	ll oxy, co;
	
	vector<ll> oxyvec = input;
	for(int i=bitnum-1;i>=0;i--) {
		int onec = 0;
		int zerc = 0;
		for(int j=0;j<oxyvec.size();j++) {
			onec += (oxyvec[j] >> i) & 1;
			zerc += !((oxyvec[j] >> i) & 1);
		}
		vector<ll> newvec;
		for(int j=0;j<oxyvec.size();j++) {
			if( (onec >= zerc && ((oxyvec[j] >> i) & 1)) || (onec < zerc && !((oxyvec[j] >> i) & 1)) ) {
				newvec.push_back(oxyvec[j]);
			}
		}
		oxyvec = newvec;
	}
	oxy = oxyvec[0];
	
	vector<ll> covec = input;
	for(int i=bitnum-1;i>=0;i--) {
		int onec = 0;
		int zerc = 0;
		for(int j=0;j<covec.size();j++) {
			onec += (covec[j] >> i) & 1;
			zerc += !((covec[j] >> i) & 1);
		}
		vector<ll> newvec;
		for(int j=0;j<covec.size();j++) {
			if( (onec < zerc && ((covec[j] >> i) & 1)) || (onec >= zerc && !((covec[j] >> i) & 1)) ) {
				newvec.push_back(covec[j]);
			}
		}
		covec = newvec;
	}
	co = covec[0];
	
	return oxy * co;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
