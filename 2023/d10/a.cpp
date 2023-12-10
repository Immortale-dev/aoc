#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> field;
vector<vector<int>> lenghts;
size_t W,H;

void prepare() {
	string s;
	while(getline(cin, s)){
		field.push_back(s);
	}
	H = field.size();
	W = field[0].size();
	lenghts = vector<vector<int>>(H, vector<int>(W, -1));
}

vector<pair<int,int>> get_moves(pair<int,int> pos) {
	char tile = field[pos.first][pos.second];
	if (tile == '-') {
		return vector<pair<int,int>>{{pos.first, pos.second-1},{pos.first, pos.second+1}};
	} else if (tile == '|') {
		return vector<pair<int,int>>{{pos.first-1, pos.second},{pos.first+1, pos.second}};
	} else if (tile == 'L') {
		return vector<pair<int,int>>{{pos.first-1, pos.second},{pos.first, pos.second+1}};
	} else if (tile == 'F') {
		return vector<pair<int,int>>{{pos.first+1, pos.second},{pos.first, pos.second+1}};
	} else if (tile == 'J') {
		return vector<pair<int,int>>{{pos.first-1, pos.second},{pos.first, pos.second-1}};
	} else if (tile == '7') {
		return vector<pair<int,int>>{{pos.first+1, pos.second},{pos.first, pos.second-1}};
	}
	string err = "wrong tile: ";
	err.push_back(tile);
	throw logic_error(err);
}

bool has_common_pos(vector<pair<int,int>> p1, vector<pair<int,int>> p2) {
	return (p1[0] == p2[0] || p1[0] == p2[1] || p1[1] == p2[0] || p1[1] == p2[1]);
}

bool is_ground(pair<int,int> pos) {
	return field[pos.first][pos.second] == '.';
}

char get_connection_tile(pair<int,int> pos) {
	if (pos.second > 0 && pos.second < W-1 && !is_ground({pos.first, pos.second+1}) && !is_ground({pos.first, pos.second-1}) && has_common_pos(get_moves({pos.first, pos.second+1}), get_moves({pos.first, pos.second-1}))) {
		return '-';
	}
	if (pos.first < H-1 && pos.first > 0 && !is_ground({pos.first+1, pos.second}) && !is_ground({pos.first-1, pos.second}) && has_common_pos(get_moves({pos.first-1, pos.second}), get_moves({pos.first+1, pos.second}))) {
		return '|';
	}
	if (pos.first > 0 && pos.second < W-1 && !is_ground({pos.first-1, pos.second}) && !is_ground({pos.first, pos.second+1}) && has_common_pos(get_moves({pos.first-1, pos.second}), get_moves({pos.first, pos.second+1}))) {
		return 'L';
	}
	if (pos.first < H-1 && pos.second < W-1 && !is_ground({pos.first+1, pos.second}) && !is_ground({pos.first, pos.second+1}) && has_common_pos(get_moves({pos.first+1, pos.second}), get_moves({pos.first, pos.second+1}))) {
		return 'F';
	}
	if (pos.first > 0 && pos.second > 0 && !is_ground({pos.first-1, pos.second}) && !is_ground({pos.first, pos.second-1}) && has_common_pos(get_moves({pos.first-1, pos.second}), get_moves({pos.first, pos.second-1}))) {
		return 'J';
	}
	if (pos.first < H-1 && pos.second > 0 && !is_ground({pos.first+1, pos.second}) && !is_ground({pos.first, pos.second-1}) && has_common_pos(get_moves({pos.first+1, pos.second}), get_moves({pos.first, pos.second-1}))) {
		return '7';
	}
	throw logic_error("Cannot figure out starting tile");
}

ll first() {
	pair<int,int> start{-1,-1};
	for(size_t i=0;i<H;i++) {
		for(size_t j=0;j<W;j++) {
			if (field[i][j] == 'S') {
				start = {i,j};
			}
		}
	}
	assert(start.first != -1);
	field[start.first][start.second] = get_connection_tile(start);

	queue<pair<int,int>> q;
	lenghts[start.first][start.second] = 0;
	q.push(start);
	while(!q.empty()) {
		auto pos = q.front();
		q.pop();
		auto moves = get_moves(pos);
		for(auto& move : moves) {
			if (lenghts[move.first][move.second] >= 0) continue;
			lenghts[move.first][move.second] = lenghts[pos.first][pos.second] + 1;
			q.push(move);
		}
	}

	int res = 0;
	for(size_t i=0;i<H;i++) {
		for(size_t j=0;j<W;j++) {
			res = max(res, lenghts[i][j]);
		}
	}

	return res;
}

ll second() {
	int cnt = 0;
	for(size_t i=0;i<H;i++) {
		bool in = false;
		for(size_t j=0;j<W;j++) {
			if (lenghts[i][j] >= 0) {
				if (field[i][j] == '|') {
					in = !in;
					continue;
				}
				char begin = field[i][j];
				while(field[i][++j] == '-') continue;
				char end = field[i][j];
				if ((begin == 'L' && end == '7') || (begin == 'F' && end == 'J')) {
					in = !in;
					continue;
				}
				continue;
			}
			if (in) {
				field[i][j] = '#';
				cnt++;
			}
		}
	}
	return cnt;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
