#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Dep) {
	PARSE_SETUP;
	PARSE(char) from = UNTIL(':');
	SKIP(char) = SINGLE(':');
	PARSE(string) to = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Dep) deps = UNTIL_END();
};

Input input(std::cin);

ll find_paths(unordered_map<string, size_t>& visited, unordered_map<string, vector<string>>& graph, const string& from, const string& to) {
	if (visited.count(to)) return visited[to];
	if (to == from) return 1;
	if (!graph[to].size()) return visited[to] = 0;
	ll res = 0;
	for (auto &s : graph[to]) {
		res += find_paths(visited, graph, from, s);
	}
	return visited[to] = res;
}

ll first() {
	unordered_map<string, vector<string>> graph;
	for (auto &dep : input.deps) {
		string from = string(dep.from.begin(), dep.from.end());
		for (string &s : dep.to) {
			graph[s].push_back(from);
		}
	}
	string from = "you";
	string to = "out";
	unordered_map<string, size_t> visited;
	visited["you"] = 1;
	ll res = find_paths(visited, graph, from, to);
	return res;
}

ll second() {
	unordered_map<string, vector<string>> graph;
	for (auto &dep : input.deps) {
		string from = string(dep.from.begin(), dep.from.end());
		for (string &s : dep.to) {
			graph[s].push_back(from);
		}
	}

	vector<vector<string>> paths{
		{"svr", "dac", "fft", "out"},
		{"svr", "fft", "dac", "out"},
	};

	unordered_map<string, size_t> visited;

	ll res = 0;
	for (auto &path : paths) {
		ll temp = 1;
		for (int i=0;i<path.size()-1;i++) {
			string from = path[i];
			string to = path[i+1];
			visited.clear();
			visited[from] = temp;
			temp = find_paths(visited, graph, from, to);
		}
		res += temp;
	}

	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
