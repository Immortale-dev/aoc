#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Mod {
	string name;
	int type;
	vector<string> dirs;
};

struct Comm {
	string from;
	string to;
	bool command;
};

class Mo {
	public:
		Mo(string nm, int t, vector<string> inps, vector<string> outs) : name(nm), type(t), inputs(inps), outputs(outs) {}
		virtual vector<Comm> process(Comm c) { return {}; }

		string name;
		int type;
		vector<string> inputs, outputs;
};

class FlipMo : public Mo{
	public:
		using Mo::Mo;

		vector<Comm> process(Comm c) override {
			vector<Comm> res;
			if (!c.command) {
				state = !state;
				for(auto des : this->outputs) {
					res.push_back({this->name, des, state});
				}
			}
			return res;
		}

		bool state = false;
};

class ConnMo : public Mo{
	public:
		using Mo::Mo;

		vector<Comm> process(Comm c) override {
			vector<Comm> res;

			mem[c.from] = c.command;

			bool state = true;
			for(auto dest : this->inputs) {
				state &= mem[dest];
			}
			for(auto dest : this->outputs) {
				res.push_back({this->name, dest, !state});
			}

			return res;
		}

		map<string, bool> mem;
};

class BroMo : public Mo {
	public:
		using Mo::Mo;

		vector<Comm> process(Comm c) override {
			vector<Comm> res;

			for(auto dest : this->outputs) {
				res.push_back({this->name, dest, c.command});
			}

			return res;
		};
};

vector<Mod> mods;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " -> ");
		int t = 0;
		string name = arr[0];
		if (name[0] == '%') {
			t = 1;
			name = name.substr(1);
		} else if (name[0] == '&') {
			t = 2;
			name = name.substr(1);
		}
		auto dirArr = split_line(arr[1], ", ");
		mods.push_back({name, t, dirArr});
	}
}

map<string, Mo*> generate_mod_map() {
	map<string, Mo*> mod_map;
	for(auto& m : mods) {
		vector<string> inps;
		for(auto &n : mods) {
			for(auto des : n.dirs) {
				if (des == m.name) {
					inps.push_back(n.name);
				}
			}
		}
		Mo* mo;
		if (m.type == 0) {
			mo = new BroMo(m.name, m.type, inps, m.dirs);
		} else if (m.type == 1) {
			mo = new FlipMo(m.name, m.type, inps, m.dirs);
		} else {
			mo = new ConnMo(m.name, m.type, inps, m.dirs);
		}
		mod_map[m.name] = mo;
	}
	return mod_map;
}

vector<int> findDivs(int a) {
	vector<int> res;
	for(int i=2;i<sqrt(a);i++) {
		while ((a%i) == 0) {
			res.push_back(i);
			a/=i;
		}
	}
	if (a > 1) {
		res.push_back(a);
	}
	return res;
}

ll lcm(vector<int> results) {
	vector<map<int,int>> divs;
	for(int a : results) {
		map<int,int> local_divs;
		for(auto d : findDivs(a)){
			local_divs[d]++;
		}
		divs.push_back(local_divs);
	}
	set<int> udivs;
	for(auto &dv : divs) {
		for(auto &d : dv) {
			udivs.insert(d.first);
		}
	}
	ll res = 1;
	for(auto d : udivs) {
		int dn = 0;
		for(auto& dv : divs) {
			dn = max(dn, dv[d]);
		}
		for(int i=0;i<dn;i++) {
			res *= (ll)d;
		}
	}
	return res;
}

ll first() {
	auto mod_map = generate_mod_map();
	queue<Comm> q;

	ll l_cnt=0, h_cnt=0;

	int pushes = 1000;
	while(pushes--) {
		q.push({"button", "broadcaster", 0});
		while(!q.empty()) {
			auto c = q.front();
			q.pop();
			if (c.command) {
				h_cnt++;
			} else {
				l_cnt++;
			}
			if (!mod_map.count(c.to)) continue;
			for(auto nc : mod_map[c.to]->process(c)) {
				q.push(nc);
			}
		}
	}

	return l_cnt * h_cnt;
}

ll second() {
	auto mod_map = generate_mod_map();

	vector<string> inps;
	for(auto &n : mods) {
		for(auto des : n.dirs) {
			if (des == "rx") {
				inps.push_back(n.name);
			}
		}
	}
	mod_map["rx"] = new FlipMo("rx", 1, inps, {});
	queue<Comm> q;

	unordered_map<string, set<int>> childs;
	for(auto &c : mod_map[inps[0]]->inputs) {
		childs[c] = {};
	}

	ll cnt = 10000;
	int ii = 0;
	while(cnt--) {
		ii++;
		q.push({"button", "broadcaster", 0});
		while(!q.empty()) {
			auto c = q.front();
			q.pop();
			if (c.to == "rx" && !c.command) return cnt; // just in case :P
			if (childs.count(c.from) && c.command) {
				childs[c.from].insert(ii);
			}
			if (!mod_map.count(c.to)) continue;
			for(auto nc : mod_map[c.to]->process(c)) {
				q.push(nc);
			}
		}
	}

	vector<int> results;
	for(auto& child : childs) {
		results.push_back(*child.second.begin());
	}

	return lcm(results);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
