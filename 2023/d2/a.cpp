#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Turn {
	int r;
	int g;
	int b;
};

struct Game {
	int id;
	vector<Turn> turns;
};

vector<Game> games;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, ": ");
		int id = stoi(split_line(arr[0], " ")[1]);
		auto turnsArr = split_line(arr[1], "; ");
		vector<Turn> turns;
		for (auto turn : turnsArr) {
			auto ballsArr = split_line(turn, ", ");
			int r,g,b;
			r = g = b = 0;
			for (auto ball : ballsArr) {
				auto bArr = split_line(ball, " ");
				int n = stoi(bArr[0]);
				if (bArr[1] == "red") {
					r = n;
				} else if (bArr[1] == "blue") {
					b = n;
				} else {
					g = n;
				}
			}
			turns.push_back(Turn{r,g,b});
		}
		games.push_back(Game{id, turns});
	}
}

ll first() {
	int res = 0;
	for(auto& game : games) {
		bool possible = true;
		for(auto& turn : game.turns) {
			if (turn.r > 12 || turn.g > 13 || turn.b > 14) {
				possible = false;
				break;
			}
		}
		if (possible) {
			res += game.id;
		}
	}
	return res;
}

ll second() {
	ll res = 0;
	for(auto& game : games) {
		int minr, ming, minb;
		minr = ming = minb = 0;
		for(auto& turn : game.turns) {
			minr = max(minr, turn.r);
			ming = max(ming, turn.g);
			minb = max(minb, turn.b);
		}
		assert(minr > 0);
		assert(ming > 0);
		assert(minb > 0);
		res += minr * ming * minb;
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
