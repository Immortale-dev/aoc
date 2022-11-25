#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//////////////////////// SNAILFISH ///////////////////////////
struct Snailfish {
	bool regular = false;
	int value;
	Snailfish* left = nullptr;
	Snailfish* right = nullptr;
	Snailfish* parent = nullptr;
	
	Snailfish* plus(Snailfish*);
};


bool snailexplode_dfs(Snailfish* n, int depth) {
	if(n->regular) {
		return false;
	}
	if(depth == 4) {
		Snailfish* t;
		
		// explode to the left
		t = n;
		while(t->parent) {
			auto* p = t->parent;
			if(p->left == t) {
				t = p;
				continue;
			}
			p = p->left;
			while(!p->regular){
				p = p->right;
			}
			p->value += n->left->value;
			break;
		}
		
		// explode to the right
		t = n;
		while(t->parent) {
			auto* p = t->parent;
			if(p->right == t){
				t = p;
				continue;
			}
			p = p->right;
			while(!p->regular) {
				p = p->left;
			}
			p->value += n->right->value;
			break;
		}
		
		// update links
		n->regular = true;
		n->value = 0;
		n->left = nullptr;
		n->right = nullptr;
		
		return true;
	}
	if(snailexplode_dfs(n->left, depth+1) || snailexplode_dfs(n->right, depth+1)){
		return true;
	}
	return false;
}

bool snailexplode(Snailfish* n) {
	return snailexplode_dfs(n, 0);
}

bool snailsplit_dfs(Snailfish* n) {
	if(n->regular) {
		if(n->value > 9) {
			n->regular = false;
			
			n->left = new Snailfish();
			n->left->regular = true;
			n->left->parent = n;
			n->left->value = n->value/2;
			
			n->right = new Snailfish();
			n->right->regular = true;
			n->right->parent = n;
			n->right->value = (n->value-1)/2+1;
			
			return true;
		}
		return false;
	}
	if(snailsplit_dfs(n->left)) return true;
	if(snailsplit_dfs(n->right)) return true;
	return false;
}

bool snailsplit(Snailfish* n) {
	return snailsplit_dfs(n);
}

void snailfix(Snailfish* n) {
	while(true) {
		if(snailexplode(n)) continue;
		if(snailsplit(n)) continue;
		break;
	}
}

Snailfish* Snailfish::plus(Snailfish* second) {
	auto* ret = new Snailfish();
	ret->left = this;
	ret->right = second;
	
	this->parent = ret;
	second->parent = ret;
	
	snailfix(ret);
	return ret;
}

void snailfish_print(Snailfish* n) {
	if(n->regular){
		cout << n->value;
		return;
	}
	cout << "[";
	snailfish_print(n->left);
	cout << ",";
	snailfish_print(n->right);
	cout << "]";
}

Snailfish* parse_snailfish(string& s, int& ind) {
	auto* ret = new Snailfish();
	while(ind<s.size()){
		if(s[ind] == '[') {
			ret->left = parse_snailfish(s, ++ind);
			ret->left->parent = ret;
		}
		else if(s[ind] == ']') {
			++ind;
			return ret;
		}
		else if(s[ind] == ',') {
			ret->right = parse_snailfish(s, ++ind);
			ret->right->parent = ret;
		} else {
			ret->regular = true;
			ret->value = s[ind]-'0';
			++ind;
			return ret;
		}
	}
	throw "wtf";
}

Snailfish* clone(Snailfish* n) {
	auto* ret = new Snailfish();
	if(n->regular) {
		ret->regular = true;
		ret->value = n->value;
		return ret;
	}
	ret->left = clone(n->left);
	ret->right = clone(n->right);
	ret->left->parent = ret;
	ret->right->parent = ret;
	return ret;
}

////////////////////////////////////////////////////////////

vector<Snailfish*> input;

ll calc_magnitude(Snailfish* n) {
	if(n->regular){
		return n->value;
	}
	return calc_magnitude(n->left)*3 + calc_magnitude(n->right)*2;
}

void prepare() {
	string s;
	while(getline(cin, s)){
		int index = 0;
		input.push_back(parse_snailfish(s, index));
		assert(index == s.size());
	}
}

ll first() {
	auto* a = clone(input[0]);
	for(int i=1;i<input.size();i++){
		a = a->plus(clone(input[i]));
	}
	
	//cout << endl;
	//snailfish_print(a);
	//cout << endl;
	
	return calc_magnitude(a);
}

ll second() {
	ll mx = 0;
	for(int i=0;i<input.size();i++){
		for(int j=0;j<input.size();j++){
			if(i == j) continue;
			mx = max( mx, calc_magnitude(clone(input[i])->plus(clone(input[j]))) );
		}
	}
	return mx;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
