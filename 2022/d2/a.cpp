#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<pair<char,char>> guide;

int RPS_result(char a, char b) {
	if (a == b) return 0;
	if (a == 'A' && b == 'B') return 1;
	if (a == 'A' && b == 'C') return -1;
	if (a == 'B' && b == 'A') return -1;
	if (a == 'B' && b == 'C') return 1;
	if (a == 'C' && b == 'A') return 1;
	if (a == 'C' && b == 'B') return -1;
	throw logic_error("Something is wrong here");
}

int calc_your_score(char move, int result) {
	return (move-'A'+1) + (result+1)*3;
}

void prepare() {
	string s;
	while(getline(cin, s)){
		guide.push_back(make_pair(s[0], s[2]));
	}
}

ll first() {
	ll scores = 0;
	for(auto &round : guide) {
		char move = round.second-'X'+'A';
		scores += calc_your_score(move, RPS_result(round.first, move));
	}
	return scores;
}

ll second() {
	ll scores = 0;
	for(auto &round : guide) {
		char move = '-';
		int result = (round.second-'X'-1);
		for(char c='A';c<='C';c++){
			if (RPS_result(round.first, c) == result) {
				move = c;
				break;
			}
		}
		scores += calc_your_score(move, RPS_result(round.first, move));
	}
	return scores;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
