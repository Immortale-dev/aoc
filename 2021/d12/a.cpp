#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

struct Node {
	int index;
	bool big;
	bool visited;
};

map<string, int> cave_index;

vector<int> cave_links[50];

vector<Node> caves;

int START, FINISH;

int get_index(string name) {
	if(!cave_index.count(name)) {
		caves.push_back({(int)caves.size(), name[0] < 'a', false});
		cave_index[name] = caves.size()-1;
	}
	return cave_index[name];
}

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, "-");
		int from = get_index(arr[0]);
		int to = get_index(arr[1]);
		cave_links[from].push_back(to);
		cave_links[to].push_back(from);
	}
	START = get_index("start");
	FINISH = get_index("end");
}

int dfs(int index) {
	if(index == FINISH) return 1;
	if(!caves[index].big && caves[index].visited) return 0;
	caves[index].visited = true;
	int count = 0;
	for(auto ind : cave_links[index]) {
		count += dfs(ind);
	}
	caves[index].visited = false;
	return count;
}

int dfs2(int index, bool visited_twise) {
	if(index == FINISH) return 1;
	int count = 0;
	for(auto ind : cave_links[index]) {
		if(!caves[ind].visited || caves[ind].big) {
			caves[ind].visited = true;
			count += dfs2(ind, visited_twise);
			caves[ind].visited = false;
		}
		else if(!caves[ind].big && caves[ind].visited && !visited_twise && ind != START) {
			count += dfs2(ind, true);
		}
	}
	return count;
}

ll first() {
	return dfs(START);
}

ll second() {
	caves[START].visited = true;
	return dfs2(START, false);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
