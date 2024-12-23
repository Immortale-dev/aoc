#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Connection) {
	PARSE_SETUP;
	PARSE(char) from = THROUGH('-');
	PARSE(char) to = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Connection) connections = UNTIL_END();
};

Input input(std::cin);

map<string,int> pcs;
vector<string> names;
int id = 0;
vector<vector<int>> network;

bool vector_has(vector<int> &vec, int k) {
	for (auto v : vec) {
		if (v == k) return true;
	}
	return false;
}

void prepare() {
	for (auto &con : input.connections) {
		string from(con.from.begin(), con.from.end());
		string to(con.to.begin(), con.to.end());
		assert(from.size() == 2);
		assert(to.size() == 2);
		if (!pcs.count(from)) {
			names.push_back(from);
			pcs[from] = id++;
		}
		if (!pcs.count(to)) {
			names.push_back(to);
			pcs[to] = id++;
		}
	}
	network.resize(id);
	for (auto &con : input.connections) {
		string from(con.from.begin(), con.from.end());
		string to(con.to.begin(), con.to.end());
		network[pcs[from]].push_back(pcs[to]);
		network[pcs[to]].push_back(pcs[from]);
	}
}

void dfs(int c, vector<int> &cluster_ids, int cid) {
	if (cluster_ids[c] >= 0) return;
	cluster_ids[c] = cid;
	for (auto nid : network[c]) {
		dfs(nid, cluster_ids, cid);
	}
}

ll first() {
	set<string> connected;

	int res = 0;
	for (int i=0;i<id;i++) {
		for (int j=0;j<network[i].size();j++) {
			for (int k=j+1;k<network[i].size();k++) {
				int jj=network[i][j];
				int kk=network[i][k];
				if (vector_has(network[jj], kk) && names[i][0] == 't') {
					vector<string> conn{names[i], names[jj], names[kk]};
					sort(conn.begin(), conn.end());
					string conn_res = conn[0] + conn[1] + conn[2];
					if (connected.count(conn_res)) continue;
					connected.insert(conn_res);
					res++;
				}
			}
		}
	}

	return res;
}

ll second() {
	vector<set<int>> all_cliques;
	for (int i=0;i<network.size();i++) {
		all_cliques.push_back({i});
	}
	for (int l=2;l<20;l++) {
		bool added = false;
		vector<set<int>> new_cliques;
		for (int i=0;i<network.size();i++) {
			set<int> edges(network[i].begin(), network[i].end());
			for (auto &s : all_cliques) {
				if (s.count(i)) continue;
				bool good = true;
				for (auto e : s) {
					if (!edges.count(e)) {
						good = false;
						break;
					}
				}
				if (good) {
					auto cs = s;
					cs.insert(i);
					new_cliques.push_back(cs);
					added = true;
				}
			}
		}
		if (!added) break;
		vector<set<int>> unique_cliques;
		set<vector<int>> unique;
		for (auto &s : new_cliques) {
			vector<int> vc(s.begin(), s.end());
			if (!unique.count(vc)) {
				unique.insert(vc);
				unique_cliques.push_back(s);
			}
		}
		swap(all_cliques, unique_cliques);
	}

	string result;
	for (auto &s : all_cliques) {
		vector<string> alp;
		for (auto e : s) {
			alp.push_back(names[e]);
		}
		sort(alp.begin(), alp.end());
		for (auto n : alp) {
			if (result.size()) result.push_back(',');
			result += n;
		}
	}
	cout << result << endl;

	return 0;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
