#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

struct node{
	node(int label, node* left, node* right) : label(label), left(left), right(right){}
	int label;
	node *left, *right;
};

string s;
unordered_map<int, node*> access;

void prepare()
{
	cin >> s;
}

node* build_list(string s)
{
	access.clear();
	node* current = nullptr;
	
	node* c;
	for(int i=0;i<s.size();i++){
		int l = s[i]-'0';
		node* n = new node(l, nullptr, nullptr);
		
		access[l] = n;
		
		if(!current){
			current = n;
			n->left = n;
			n->right = n;
			c = n;
			continue;
		}
		
		c->right = n;
		n->left = c;
		n->right = current;
		current->left = n;
		
		c = n;
	}
	
	return current;
}

void step(node* n)
{
	node *p1, *p2, *p3;
	p1 = n->right;
	p2 = p1->right;
	p3 = p2->right;
	
	int nl = n->label;
	
	nl = nl == 1 ? access.size() : nl-1;
	while(nl == p1->label || nl == p2->label || nl == p3->label){
		nl = nl == 1 ? access.size() : nl-1;
	}
	
	n->right = p3->right;
	p3->right->left = n;
	
	node* dest = access[nl];
	node* dest_right = dest->right;
	
	dest->right = p1;
	p1->left = dest;
	
	dest_right->left = p3;
	p3->right = dest_right;
}

int first()
{	
	node* current = build_list(s);
	
	for(int i=0;i<100;i++){
		step(current);
		current = current->right;
	}
	
	while(current->label != 1) current = current->right;
	
	int res = 0;
	current = current->right;
	do{
		res = (res*10)+current->label;
		current = current->right;
	}while(current->label != 1);
	
	return res;
}

ll second()
{
	node* current = build_list(s);
	node* c = current;
	for(int i=0;i<8;i++){
		c = c->right;
	}
	for(int i=10;i<=1000000;i++){
		node* n = new node(i,nullptr, nullptr);
		
		access[i] = n;
		
		c->right = n;
		n->left = c;
		
		n->right = current;
		current->left = n;
		
		c = n;
	}
	
	for(int i=0;i<10000000;i++){
		step(current);
		current = current->right;
	}
	
	while(current->label != 1) current = current->right;
	
	return (ll)current->right->label * (ll)current->right->right->label;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
