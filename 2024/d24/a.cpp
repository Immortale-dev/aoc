#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Gate) {
	PARSE_SETUP;
	PARSE(char) name = THROUGH(':');
	PARSE(int) state = SINGLE();
	SKIP(char) = SINGLE('\n');
};

DEFINE_PARSE_INTERFACE(Cond) {
	PARSE_SETUP;
	PARSE(string) left = SINGLE();
	PARSE(string) op = SINGLE();
	PARSE(string) right = SINGLE();
	SKIP(char) = COUNT(4);
	PARSE(string) out = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Gate) gates = THROUGH('\n');
	PARSE(Cond) conds = UNTIL_END();
};

Input input(std::cin);

struct Condition {
	int left, right;
	string op;
};

ll calc_gate(int gate, vector<Condition> &graph, vector<int> &values) {
	if (values[gate] >= 0) return values[gate];
	auto &condition = graph[gate];
	bool left = calc_gate(condition.left, graph, values);
	bool right = calc_gate(condition.right, graph, values);
	bool res;
	if (condition.op == "AND") res = left & right;
	if (condition.op == "OR") res = left | right;
	if (condition.op == "XOR") res = left ^ right;
	values[gate] = res;
	return res;
}

int xy_ids = 0;
int length = 0;
unordered_map<string, int> ids;
vector<int> values(1000,-1);
vector<Condition> graph(1000);
map<int,int> zvals;
vector<string> id_names(1000);

void prepare() {
	int id=0;
	for (auto &g : input.gates) {
		string name(g.name.begin(), g.name.end());
		ids[name] = id++;
		values[ids[name]] = (g.state() > 0);
		id_names[ids[name]] = name;
	}
	xy_ids=id;
	for (auto &cond : input.conds) {
		if (!ids.count(cond.out())) {
			ids[cond.out()] = id++;
			id_names[ids[cond.out()]] = cond.out();
		}
		if (!ids.count(cond.left())) {
			ids[cond.left()] = id++;
			id_names[ids[cond.left()]] = cond.left();
		}
		if (!ids.count(cond.right())) {
			ids[cond.right()] = id++;
			id_names[ids[cond.right()]] = cond.right();
		}
		graph[ids[cond.out()]] = {ids[cond.left()], ids[cond.right()], cond.op()};
		if (cond.out()[0] == 'z') {
			zvals[stoi(string(cond.out().begin()+1, cond.out().end()))] = ids[cond.out()];
		}
	}
	length = id;
}

ll calc(vector<Condition> &graph, vector<int> &values) {
	vector<int> result;
	for (auto id : zvals) {
		result.push_back(calc_gate(id.second, graph, values));
	}
	ll res = 0;
	for (auto it=result.rbegin();it!=result.rend();++it) {
		res <<= 1L;
		res += *it;
	}
	return res;
}

ll first() {
	auto l_values = values;
	return calc(graph, l_values);
}

bool detect(int gate, vector<Condition> &graph, vector<int> &qc) {
	if (qc[gate]) return true;
	qc[gate] = true;
	bool res = false;
	if (values[gate] < 0) {
		res = detect(graph[gate].left, graph, qc) || detect(graph[gate].right, graph, qc);
	}
	qc[gate] = false;
	return res;
}

bool detect_cycle(vector<Condition> &graph) {
	vector<int> qc(length);
	for (auto id : zvals) {
		if (detect(id.second, graph, qc)) return true;
	}
	return false;
}

pair<ll, vector<int>> random_bits(int cnt) {
	vector<int> bits(cnt);
	ll num = 0;
	for (int i=0;i<cnt;i++) {
		bits[i] = ((rand() % 1000) < 500);
		num = (num << 1) + bits[i];
	}
	reverse(bits.begin(), bits.end());
	return {num,bits};
}

ll check_correct_bits(vector<Condition> &graph) {
	ll cnt = 50;
	auto lvalues = values;
	for (int i=0;i<xy_ids;i++) {
		lvalues[i] = 0;
	}
	ll z;
	for (int j=0;j<100;j++) {
		auto rlvalues = lvalues;
		auto [x,xbits] = random_bits(45);
		auto [y,ybits] = random_bits(45);
		for (int i=0;i<45;i++) {
			rlvalues[i] = xbits[i];
			rlvalues[45+i] = ybits[i];
		}
		z = x+y;
		ll rz = calc(graph, rlvalues);
		for (int i=0;i<=50;i++) {
			if ( ((1L << i) & z) != ((1L << i) & rz) ) {
				cnt = min(cnt, (ll)i);
			}
		}
	}
	return cnt;
}

ll second() {
	auto lgraph = graph;

	vector<string> result;
	for (int l=0;l<4;l++) {
		int correct = check_correct_bits(lgraph);

		vector<pair<int,int>> valid_swaps;
		for (int i=xy_ids;i<length;i++) {
			for (int j=i+1;j<length;j++) {
				swap(lgraph[i], lgraph[j]);
				if (!detect_cycle(lgraph)) {
					int new_correct = check_correct_bits(lgraph);
					if (new_correct > correct) {
						valid_swaps.push_back({i,j});
					}
				}
				swap(lgraph[i], lgraph[j]);
			}
		}
		if (valid_swaps.size() == 1) {
			swap(lgraph[valid_swaps[0].first], lgraph[valid_swaps[0].second]);
			result.push_back(id_names[valid_swaps[0].first]);
			result.push_back(id_names[valid_swaps[0].second]);
		} else {
			throw std::logic_error("kurwa");
		}
	}

	sort(result.begin(), result.end());

	string ret;
	for (auto r : result) {
		if (ret.size()) ret.push_back(',');
		ret += r;
	}
	cout << ret << endl;

	return 0;
}

int main() {
	srand(123);
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
