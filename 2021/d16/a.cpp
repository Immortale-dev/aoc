#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "./bits.cpp"

typedef long long int ll;

string input;

void prepare() {
	getline(cin, input);
}

int dfs(shared_ptr<BITS::BIT> node) {
	int res = node->version;
	for(auto it : node->childs) {
		res += dfs(it);
	}
	return res;
}

ll dfs2(shared_ptr<BITS::BIT> node) {
	ll res = 0;
	switch(node->type) {
		case 0: 
			for(auto it : node->childs) res += dfs2(it);
			break;
		case 1:
			res = 1;
			for(auto it : node->childs) res *= dfs2(it);
			break;
		case 2:
			res = 999999999999999;
			for(auto it : node->childs) res = min(res, dfs2(it));
			break;
		case 3:
			for(auto it : node->childs) res = max(res, dfs2(it));
			break;
		case 4:
			res = node->val;
			break;
		case 5:
			res = (ll)(dfs2(node->childs[0]) > dfs2(node->childs[1]));
			break;
		case 6:
			res = (ll)(dfs2(node->childs[0]) < dfs2(node->childs[1]));
			break;
		case 7:
			res = (ll)(dfs2(node->childs[0]) == dfs2(node->childs[1]));
			break;
	}
	return res;
}

ll first() {
	return dfs(BITS::fromString(input));
}

ll second() {
	return dfs2(BITS::fromString(input)); 
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
