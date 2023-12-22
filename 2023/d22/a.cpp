#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Coord {
	int x,y,z;
};

struct Brick {
	Coord begin, end;
	int id;
};

vector<Brick> original_bricks;

int hash_coord(Coord c) {
	return ((c.x*100+c.y)*1000)+c.z;
}

unordered_map<int, int> generate_bricks_hash(vector<Brick>& bricks) {
	unordered_map<int, int> c_hash;
	for(auto& brick : bricks) {
		int x_begin = min(brick.begin.x, brick.end.x);
		int x_end = max(brick.begin.x, brick.end.x);
		int y_begin = min(brick.begin.y, brick.end.y);
		int y_end = max(brick.begin.y, brick.end.y);
		int z_begin = max(brick.begin.z, brick.end.z);
		int z_end = max(brick.begin.z, brick.end.z);
		for(int x=x_begin;x<=x_end;x++) {
			for(int y=y_begin;y<=y_end;y++) {
				for(int z=z_begin;z<=z_end;z++) {
					c_hash.insert({hash_coord({x,y,z}), brick.id});
				}
			}
		}
	}
	return c_hash;
}

vector<int> gravity_tick(vector<Brick>& bricks) {
	vector<int> changed;
	auto c_hash = generate_bricks_hash(bricks);
	for(auto& brick : bricks) {
		if (brick.begin.z == 1 || brick.end.z == 1) {
			continue; // Brick is on the ground
		}
		vector<Coord> check;
		int x_begin = min(brick.begin.x, brick.end.x);
		int x_end = max(brick.begin.x, brick.end.x);
		int y_begin = min(brick.begin.y, brick.end.y);
		int y_end = max(brick.begin.y, brick.end.y);
		for(int x=x_begin;x<=x_end;x++) {
			for(int y=y_begin;y<=y_end;y++) {
				check.push_back({x,y,min(brick.begin.z, brick.end.z)-1});
			}
		}
		bool can_move = true;
		for(auto &c : check) {
			if (c_hash.count(hash_coord(c))) {
				can_move = false;
				break;
			}
		}
		if (can_move) {
			changed.push_back(brick.id);
			int z_length = abs(brick.begin.z-brick.end.z)+1;
			for(auto &c : check) {
				c_hash.erase(hash_coord({c.x,c.y,c.z-z_length}));
				c_hash.insert({hash_coord(c), brick.id});
			}
			brick.begin.z--;
			brick.end.z--;
		}
	}
	return changed;
}

void prepare() {
	string s;
	int id = 0;
	while(getline(cin, s)){
		auto arr = split_line(s, "~");
		auto startCoords = split_line(arr[0], ",");
		auto endCoords = split_line(arr[1], ",");

		Coord b{stoi(startCoords[0]), stoi(startCoords[1]), stoi(startCoords[2])};
		Coord e{stoi(endCoords[0]), stoi(endCoords[1]), stoi(endCoords[2])};

		original_bricks.push_back({b,e,++id});
	}
}

ll first() {
	vector<Brick> br = original_bricks;
	sort(br.begin(), br.end(), [](auto& left, auto& right){ return min(left.begin.z, left.end.z) < min(right.begin.z, right.end.z); });

	while(gravity_tick(br).size());
	auto c_hash = generate_bricks_hash(br);

	unordered_set<int> can_remove;
	for(auto &b : br) {
		can_remove.insert(b.id);
	}
	for(auto &brick : br) {
		unordered_set<int> ids;
		int x_begin = min(brick.begin.x, brick.end.x);
		int x_end = max(brick.begin.x, brick.end.x);
		int y_begin = min(brick.begin.y, brick.end.y);
		int y_end = max(brick.begin.y, brick.end.y);
		int min_z = min(brick.begin.z, brick.end.z);
		for(int x=x_begin;x<=x_end;x++) {
			for(int y=y_begin;y<=y_end;y++) {
				int hsh = hash_coord({x,y,min_z-1});
				if (!c_hash.count(hsh)) continue;
				ids.insert(c_hash[hsh]);
			}
		}
		if (ids.size() == 1) {
			can_remove.erase(*ids.begin());
		}
	}

	return can_remove.size();
}

ll second() {
	vector<Brick> br = original_bricks;
	sort(br.begin(), br.end(), [](auto& left, auto& right){ return min(left.begin.z, left.end.z) < min(right.begin.z, right.end.z); });

	while(gravity_tick(br).size());

	int res = 0;

	for(int i=0;i<br.size();i++) {
		vector<Brick> new_br;
		for(int j=0;j<br.size();j++) {
			if (i == j) continue;
			new_br.push_back(br[j]);
		}

		unordered_set<int> changed_ids;
		while(true) {
			auto changed = gravity_tick(new_br);
			if (!changed.size()) break;
			for (auto id : changed) {
				changed_ids.insert(id);
			}
		}
		res += changed_ids.size();
	}

	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
