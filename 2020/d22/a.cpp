#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

vector<int> p1,p2;

void prepare()
{
	string s;
	int st = 0;
	while(getline(cin, s)){
		if(s == "") {st++; continue;}
		if(s[0] == 'P') continue;
		int a = stoi(s);
		if(st){
			p2.push_back(a);
		} else {
			p1.push_back(a);
		}
	}
}

ll calc_score(queue<int> q)
{
	ll res = 0;
	ll v = q.size();
	while(v--){
		res += (v+1)*q.front();
		q.push(q.front());
		q.pop();
	}
	return res;
}

ll first()
{
	queue<int> q1,q2;
	for(auto it : p1){
		q1.push(it);
	}
	for(auto it : p2){
		q2.push(it);
	}
	
	while(!q1.empty() && !q2.empty()){
		int a1 = q1.front();
		int a2 = q2.front();
		
		q1.pop();
		q2.pop();
		
		if(a1 > a2){
			q1.push(a1);
			q1.push(a2);
		} else {
			q2.push(a2);
			q2.push(a1);
		}
	}
	
	auto q = q1.empty() ? q2 : q1;
	
	return calc_score(q);
}

queue<int> copy_queue(queue<int> q, int sz=-1)
{
	queue<int> nq;
	int size = sz < 0 ? q.size() : sz;
	while(size--){
		int a = q.front();
		q.pop();
		
		q.push(a);
		nq.push(a);
	}
	return nq;
}

bool queue_equals(queue<int> q1, queue<int> q2)
{
	if(q1.size() != q2.size()) return false;
	int sz = q1.size();
	bool ok = true;
	while(sz--){
		if(q1.front() != q2.front()) ok = false;
		q1.push(q1.front());
		q2.push(q2.front());
		q1.pop();
		q2.pop();
	}
	return ok;
}

unordered_map<ll, vector< pair< pair<queue<int>, queue<int>>, pair<ll, ll>> > > global_states;

int gi = 0;

pair<ll, ll> game(queue<int> q1, queue<int> q2)
{
	ll score = calc_score(q1) + calc_score(q2);
	if(global_states.count(score)){
		for(auto& it : global_states[score]){
			if(queue_equals(it.first.first, q1) && queue_equals(it.first.second, q2)) return it.second;
		}
	}
	queue<int> cq1 = copy_queue(q1), cq2 = copy_queue(q2);
	
	unordered_map<ll, vector< pair<queue<int>, queue<int>> > > states;
	
	while(!q1.empty() && !q2.empty()){
		
		ll score = calc_score(q1) + calc_score(q2);
		if(states.count(score)){
			for(auto& it : states[score]){
				if(queue_equals(it.first, q1) && queue_equals(it.second, q2)){
					return make_pair(1, calc_score(q1));
				}
			}
		}
		
		states[score].push_back(make_pair(copy_queue(q1), copy_queue(q2)));
		
		int a1 = q1.front();
		int a2 = q2.front();
		
		q1.pop();
		q2.pop();
		
		int w;
		
		if(q1.size() >= a1 && q2.size() >= a2){
			w = game(copy_queue(q1, a1), copy_queue(q2, a2)).first;
		} else {
			w = a1 > a2 ? 1 : 2;
		}
		
		if(w == 1){
			q1.push(a1);
			q1.push(a2);
		} else {
			q2.push(a2);
			q2.push(a1);
		}
	}
	
	pair<ll, ll> res;
	res = q1.empty() ? make_pair(2, calc_score(q2)) : make_pair(1, calc_score(q1));
	
	global_states[score].push_back(make_pair( make_pair(cq1, cq2), res ));
	
	return res;
}

ll second()
{
	queue<int> q1,q2;
	for(auto it : p1){
		q1.push(it);
	}
	for(auto it : p2){
		q2.push(it);
	}
	
	return game(q1, q2).second;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
