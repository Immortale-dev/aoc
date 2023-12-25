#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "../helpers/terminal.cpp"

typedef long long int ll;

//=======================================//

unordered_map<string, unordered_map<string, int>> graph_m;
unordered_map<int, pair<string, string>> edge_map;
int eid = 0;
vector<string> names;

vector<vector<int>> graph;
unordered_map<string, int> name_ids;

int edge_id(int from, int to) {
	if (from > to) swap(from, to);
	return from * 10000 + to;
}

pair<int,int> edge_from_id(int id) {
	return {id/10000, id%10000};
}

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, ": ");
		string name = arr[0];
		auto nodes = split_line(arr[1], " ");
		for(auto n : nodes) {
			if (graph_m[name].count(n)) continue;
			eid++;
			graph_m[name].insert({n, eid});
			graph_m[n].insert({name, eid});
			edge_map[eid] = {name, n};
		}
	}
	for(auto& it : graph_m) {
		name_ids[it.first] = names.size();
		names.push_back(it.first);
	}

	for(auto name : names) {
		vector<int> edges;
		for(auto &it : graph_m[name]) {
			edges.push_back(name_ids[it.first]);
		}
		graph.push_back(edges);
	}
}

vector<int> shortest_path(int from, int to) {
	vector<pair<int ,int>> nodes(names.size(), {0, 999999});
	nodes[from] = {from, 0};
	queue<int> q;
	q.push(from);

	while(!q.empty()) {
		int name = q.front();
		q.pop();

		int current = nodes[name].second;
		for(auto& it : graph[name]) {
			if (nodes[it].second > current+1) {
				nodes[it] = {name, current+1};
				q.push(it);
			}
		}
	}

	vector<int> edges;
	int name = to;
	while(name != from) {
		edges.push_back(edge_id(name, nodes[name].first));
		name = nodes[name].first;
	}
	return edges;
}

void visit(int name, unordered_set<int>& visited) {
	visited.insert(name);
	for(auto n : graph[name]) {
		if (!visited.count(n)) {
			visit(n, visited);
		}
	}
}

ll first() {
	save_cursor();
	for(int k=0;k<3;k++) {
		unordered_map<int, int> most_used;
		for(int i=0;i<names.size();i++) {
			/// printing ///
			restore_cursor();
			erase_to_end();
			double perc = floor((double)(k*names.size() + i)/(3 * names.size()) * 10000)/100;
			cout << perc << "%" << flush;
			/// printing ///
			for(int j=i+1;j<names.size();j++) {
				auto path = shortest_path(i, j);
				for(auto& p : path) {
					most_used[p]++;
				}
			}
		}

		int used = 0;
		int most_used_edge;
		for(auto& it : most_used) {
			if (it.second > used) {
				used = it.second;
				most_used_edge = it.first;
			}
		}

		auto edge = edge_from_id(most_used_edge);

		for(int i=0;i<graph[edge.first].size();i++) {
			if (graph[edge.first][i] == edge.second) {
				graph[edge.first].erase(graph[edge.first].begin()+i);
				break;
			}
		}
		for(int i=0;i<graph[edge.second].size();i++) {
			if (graph[edge.second][i] == edge.first) {
				graph[edge.second].erase(graph[edge.second].begin()+i);
				break;
			}
		}
	}

	unordered_set<int> visited;
	visit(0, visited);

	restore_cursor();
	erase_to_end();

	return visited.size() * (names.size()-visited.size());
}

ll second() {
	cout << "PUSH THE BUTTON!" << endl;
	return 0;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
