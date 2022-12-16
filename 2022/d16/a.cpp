#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Valve {
	string name;
	int flow;
	vector<string> pipes;
	int pos_ind = -1;
};

vector<Valve> valves;
int aa_pos = -1;
int positive_flows = 0;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, "; ");
		auto arrf = split_line(arr[0], " ");
		auto arrs = split_line(arr[1], "valves ");
		string name = arrf[1];
		int flow = stoi(split_line(arrf[4], "=")[1]);
		valves.push_back({name, flow, arrs.size() == 1 ? vector<string>{1, split_line(arrs[0], " ")[4]} : split_line(arrs[1], ", ")});
	}
	for (int i=0;i<valves.size();i++) {
		if (valves[i].name == "AA") {
			aa_pos = i;
			break;
		}
	}
	int pos_ind = 0;
	for(auto& v : valves) {
		if (v.flow) {
			positive_flows++;
			v.pos_ind = pos_ind++;
		}
	}
}

vector<vector<int>> create_graph() {
	map<string, int> indexes;
	for(int i=0;i<valves.size();i++) {
		indexes.insert({valves[i].name, i});
	}
	vector<vector<int>> res(valves.size());
	for(int i=0;i<valves.size();i++) {
		for(string& pipe : valves[i].pipes) {
			res[i].push_back(indexes[pipe]);
		}
	}
	return res;
}

int release_pressure(int opened) {
	int res = 0;
	int ind = 0;
	while(opened) {
		while(!valves[ind].flow) {
			ind++;
		}
		if (opened & 1) {
			res += valves[ind].flow;
		}
		ind++;
		opened >>= 1;
	}
	return res;
}

int get_flow_pos(int pos) {
	return valves[pos].pos_ind;
}

bool is_opened(int opened, int pos) {
	return opened & (1 << get_flow_pos(pos));
}

int open_flow(int opened, int pos) {
	return opened | (1 << get_flow_pos(pos));
}

struct req_args {
	int opened;
	int pos;
	int time;
	int pressure;
};

void dfs(vector<vector<int>>& graph, vector<vector<int>>& dp, int opened, int pos, int time, int pressure) {
	if (time > 30) return;
	if (dp[pos][time] >= pressure) return;
	
	dp[pos][time] = pressure;
	
	if (valves[pos].flow && !is_opened(opened, pos)) {
		dfs(graph, dp, open_flow(opened, pos), pos, time+1, pressure + release_pressure(opened));
	}
	for (int new_pos : graph[pos]) {
		dfs(graph, dp, opened, new_pos, time+1, pressure + release_pressure(opened));
	}
}

void dfs_2(vector<vector<int>>& graph, vector<vector<int>>& dp, int opened, int pos, int epos, int time, int pressure) {
	if (time > 26) return;
	int rpos = pos * valves.size() + epos;
	if (dp[rpos][time] >= pressure) return;
	
	dp[rpos][time] = pressure;
	
	for(int i=-1;i<(int)graph[pos].size();i++) {
		if (i == -1 && (!valves[pos].flow || is_opened(opened, pos))) continue;
		int n_pos = i < 0 ? pos : graph[pos][i];
		int n_opened = i < 0 ? open_flow(opened, pos) : opened;
		for(int j=-1;j<(int)graph[epos].size();j++) {
			if (j == -1 && (!valves[epos].flow || is_opened(n_opened, epos))) continue;
			int n_epos = j < 0 ? epos : graph[epos][j];
			int n_eopened = j < 0 ? open_flow(n_opened, epos) : n_opened;
			dfs_2(graph, dp, n_eopened, n_pos, n_epos, time+1, pressure + release_pressure(opened));
		}
	}
}

ll first() {
	vector<vector<int>> graph = create_graph();
	
	int max_opened = (1 << positive_flows);
	
	//[(1 << (positive_flows-1))+1][valves.size()][30];
	vector<vector<int>> dp(vector<vector<int>>(valves.size(), vector<int>(32, -1)));
	
	
	dfs(graph, dp, 0, aa_pos, 0, 0);
	
	int res = 0;
	for(int i=0;i<max_opened;i++) {
		for(int j=0;j<valves.size();j++) {
			res = max(res, dp[j][30]);
		}
	}
	
	return res;
}

ll second() {
	vector<vector<int>> graph = create_graph();
	
	int max_opened = (1 << positive_flows);
	
	vector<vector<int>> dp(vector<vector<int>>(valves.size() * valves.size(), vector<int>(32, -1)));
	
	dfs_2(graph, dp, 0, aa_pos, aa_pos, 0, 0);
	
	int res = 0;
	for(int i=0;i<max_opened;i++) {
		for(int j=0;j<valves.size()*valves.size();j++) {
			res = max(res, dp[j][26]);
		}
	}
	
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
