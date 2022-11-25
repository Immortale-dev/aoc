#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

struct MT{
	bool mem;
	int val;
};

struct Ins{
	int op;
	int m;
	MT w;
};

vector<Ins> input;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " ");
		Ins ins;
		
		string op =  arr[0];
		if(op == "inp") ins.op = 0;
		if(op == "add") ins.op = 1;
		if(op == "mul") ins.op = 2;
		if(op == "div") ins.op = 3;
		if(op == "mod") ins.op = 4;
		if(op == "eql") ins.op = 5;
		
		ins.m = arr[1][0]-'w';
		if(arr[0] != "inp"){
			MT mt;
			if(arr[2][0] == '-' || arr[2][0] >= '0' && arr[2][0] <= '9'){
				mt.mem = false;
				mt.val = stoi(arr[2]);
			} else {
				mt.mem = true;
				mt.val = arr[2][0]-'w';
			}
			ins.w = mt;
		}
		input.push_back(ins);
	}
}

int process(vector<Ins>& input, queue<int>& model, ll& res) {
	
	vector<int> found;
	
	vector<int> mem(4,0);
	
	ll result = 0;
	
	for(int i=0;i<input.size();i++){
		auto& it = input[i];
		int val = it.w.mem ? mem[it.w.val] : it.w.val;
		int op = it.op;
		
		switch(op){
			case 0:
				int get;
				if(input[i+4].w.val == 1){
					get = model.front();
					model.pop();
				} else {
					get = (mem[3]%26)+input[i+5].w.val;
					if(get > 9 || get < 1) return 1;
				}
				mem[it.m] = get;
				result = (result*10LL)+get;
				break;
			case 1:
				// add
				mem[it.m] += val;
				break;
			case 2:
				// mul
				mem[it.m] *= val;
				break;
			case 3:
				// div
				mem[it.m] /= val;
				break;
			case 4:
				// mod
				mem[it.m] %= val;
				break;
			case 5:
				// eql
				mem[it.m] = mem[it.m] == val;
				break;
		}
	}
	
	res = result;
	return mem[3];
}

vector<int> to_digit_vector(int val){
	int tmo = val;
	vector<int> temp_model;
	while(tmo){
		int d = tmo%10;
		tmo/=10;
		temp_model.push_back(d);
	}
	reverse(temp_model.begin(), temp_model.end());
	return temp_model;
}

bool valid_model(vector<int>& model){
	for(auto& d : model){
		if(!d) return false;
	}
	return true;
}

queue<int> model_to_queue(vector<int>& temp_model){
	queue<int> model;
	for(auto& it : temp_model){
		model.push(it);
	}
	return model;
}

ll first() {
	for(int mo=9999999;mo>1000000;mo--){
		auto v = to_digit_vector(mo);
		if(!valid_model(v)) continue;
		auto q = model_to_queue(v);
		ll result;
		if(!process(input, q, result)){
			return result;
		}
	}
	return -1; // fail
}

ll second() {
	for(int mo=1000000;mo<9999999;mo++){
		auto v = to_digit_vector(mo);
		if(!valid_model(v)) continue;
		auto q = model_to_queue(v);
		ll result;
		if(!process(input, q, result)){
			return result;
		}
	}
	return -1; // fail
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
