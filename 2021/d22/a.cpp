#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

struct pt {
	int from;
	int to;
};

struct Request {
	pt x;
	pt y;
	pt z;
	bool on;
};

vector<Request> input;

// Optimize axis
map<int, int> sx, sy, sz;
vector<int> osx, osy, osz;

// Reverse axis
vector<int> rsx, rsy, rsz;

// Grid
vector<vector<vector<bool>>> grid;

// Keep track of ons
ll total_on = 0;

void print_progress(double coof) {
	
	cout << "\033[s"; // save pos
	cout << "\033[K"; // erase line
	
	cout << "[";
	for(int i=0;i<=30;i++){
		if((double)i/30 < coof) cout << "*"; else cout <<" ";
		
	}
	cout << "]";
	cout << flush;
	
	cout << "\033[u"; // restore pos
}

void precalc() {
	// Get all unique axis
	for(auto& it : input){
		sx.insert({it.x.from, 0});
		sx.insert({it.x.to, 0});
		sy.insert({it.y.from, 0});
		sy.insert({it.y.to, 0});
		sz.insert({it.z.from, 0});
		sz.insert({it.z.to, 0});
	}
	sx.insert({-50, 0});
	sx.insert({51, 0});
	sy.insert({-50, 0});
	sy.insert({51, 0});
	sz.insert({-50, 0});
	sz.insert({51, 0});
	
	// Sort all unique axis
	for(auto& it : sx) osx.push_back(it.first);
	for(auto& it : sy) osy.push_back(it.first);
	for(auto& it : sz) osz.push_back(it.first);
	sort(osx.begin(), osx.end());
	sort(osy.begin(), osy.end());
	sort(osz.begin(), osz.end());
	rsx.resize(osx.size()+1);
	rsy.resize(osy.size()+1);
	rsz.resize(osz.size()+1);
	for(int i=0;i<osx.size();i++) {
		sx[osx[i]] = i;
		if(i < osx.size()-1){
			rsx[i] = osx[i+1]-osx[i];
		}
	}
	for(int i=0;i<osy.size();i++) {
		sy[osy[i]] = i;
		if(i < osy.size()-1){
			rsy[i] = osy[i+1]-osy[i];
		}
	}
	for(int i=0;i<osz.size();i++) {
		sz[osz[i]] = i;
		if(i < osz.size()-1){
			rsz[i] = osz[i+1]-osz[i];
		}
	}
	
	// Prepare grid
	grid = vector<vector<vector<bool>>>(sx.size()+1, vector<vector<bool>>(sy.size()+1, vector<bool>(sz.size()+1, false)));
	
	// Apply requests
	int r=0;
	for(auto& it : input) {
		print_progress((double)r++/input.size()); // print progress line
		
		for(int i=sx[it.x.from];i<sx[it.x.to];i++){
			for(int j=sy[it.y.from];j<sy[it.y.to];j++){
				for(int k=sz[it.z.from];k<sz[it.z.to];k++){
					ll cnt = (ll)rsx[i]*rsy[j]*rsz[k];
					if(it.on && !grid[i][j][k]){
						total_on += cnt;
					} else if(!it.on && grid[i][j][k]) {
						total_on -= cnt;
					}
					grid[i][j][k] = it.on;
				}
			}
		}
	}
	
	cout << "\033[K"; // clear line
}

void prepare() {
	string s;
	while(getline(cin, s)){
		auto line = split_line(s, " ");
		bool on = line[0] == "on";
		auto arr = split_line(line[1], ",");
		auto arrx = split_line(arr[0].substr(2), "..");
		auto arry = split_line(arr[1].substr(2), "..");
		auto arrz = split_line(arr[2].substr(2), "..");
		input.push_back(
			{ {stoi(arrx[0]), stoi(arrx[1])+1}, {stoi(arry[0]), stoi(arry[1])+1}, {stoi(arrz[0]), stoi(arrz[1])+1}, on } // [from,to)
		);
	}
	
	// Precalculate the grid
	precalc();
}

ll first() {
	ll res = 0;
	for(int i=sx[-50];i<sx[51];i++){
		for(int j=sy[-50];j<sy[51];j++){
			for(int k=sz[-50];k<sz[51];k++){
				res += ((ll)grid[i][j][k])*rsx[i]*rsy[j]*rsz[k];
			}
		}
	}
	return res;
}

ll second() {
	return total_on;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
