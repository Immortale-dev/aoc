#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<ll>> seqs;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " ");
		vector<ll> seq;
		for (auto val : arr) {
			seq.push_back(stoll(val));
		}
		seqs.push_back(seq);
	}
}

void add_new_val(vector<ll>& seq) {
	bool all_zero = true;
	for(size_t i=0;i<seq.size();i++) {
		if (seq[i] != 0) {
			all_zero = false;
			break;
		}
	}
	if (all_zero) {
		seq.push_back(0);
		return;
	}
	vector<ll> n_seq(seq.size()-1);
	for(size_t i=0;i<seq.size()-1;i++) {
		n_seq[i] = seq[i+1] - seq[i];
	}
	add_new_val(n_seq);
	seq.push_back(n_seq.back() + seq.back());
}

void add_new_first_val(deque<ll>& seq) {
	bool all_zero = true;
	for(size_t i=0;i<seq.size();i++) {
		if (seq[i] != 0) {
			all_zero = false;
			break;
		}
	}
	if (all_zero) {
		seq.push_front(0);
		return;
	}
	deque<ll> n_seq(seq.size()-1);
	for(size_t i=0;i<seq.size()-1;i++) {
		n_seq[i] = seq[i+1] - seq[i];
	}
	add_new_first_val(n_seq);
	seq.push_front(-n_seq.front() + seq.front());
}

ll first() {
	ll res = 0;
	for(auto& seq : seqs) {
		vector<ll> new_s(seq.begin(), seq.end());
		add_new_val(new_s);
		res += new_s.back();
	}
	return res;
}

ll second() {
	ll res = 0;
	for(auto& seq : seqs) {
		deque<ll> new_s(seq.begin(), seq.end());
		add_new_first_val(new_s);
		res += new_s.front();
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
