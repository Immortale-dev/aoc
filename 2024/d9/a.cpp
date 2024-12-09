#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(string) str = SINGLE();
};

Input input(std::cin);

ll prog(ll cnt, ll start, ll id) {
	return ((start+cnt)*(start+cnt-1)/2 - start*(start-1)/2) * id;
}

ll first() {
	vector<int> all(input.str().size());
	transform(input.str().begin(), input.str().end(), all.begin(), [](char c)->int{ return c-'0'; });

	ll res = 0;
	int id=0;
	int lastInd = all.size()-1;
	int ind = 0;
	while (ind<=lastInd) {
		if (ind & 1) {
			int cnt = min(all[lastInd], all[ind]);
			res += prog(cnt, id, lastInd/2);
			if(!(all[lastInd] -= cnt)) lastInd-=2;
			if (!(all[ind] -= cnt)) ++ind;
			id += cnt;
		} else {
			res += prog(all[ind], id, ind/2);
			id += all[ind];
			++ind;
		}
	}
	return res;
}

struct File {
	int id,pos,size;
};

ll second() {
	vector<int> all(input.str().size());
	transform(input.str().begin(), input.str().end(), all.begin(), [](char c)->int{ return c-'0'; });
	vector<File> files;
	map<int, set<int>> spaces;

	int pos = 0;
	for (int i=0;i<all.size();++i) {
		if (i & 1) {
			spaces[all[i]].insert(pos);
		} else {
			files.push_back({i/2, pos, all[i]});
		}
		pos += all[i];
	}

	ll res = 0;
	for (auto it=files.rbegin();it!=files.rend();++it) {
		int minPos = it->pos;
		auto minIt = spaces.lower_bound(it->size);
		for (auto lit=minIt;lit!=spaces.end();++lit) {
			if (*lit->second.begin() < minPos) {
				minIt = lit;
				minPos = *lit->second.begin();
			}
		}
		if (minPos < it->pos) {
			int diff = minIt->first - it->size;
			minIt->second.erase(minIt->second.begin());
			if (!minIt->second.size()) spaces.erase(minIt);
			if (diff) {
				spaces[diff].insert(minPos+it->size);
			}
		}
		res += prog(it->size, minPos, it->id);
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
