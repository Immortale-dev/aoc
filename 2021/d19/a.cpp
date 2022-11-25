#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "./scanner.cpp"

typedef long long int ll;

vector<Scanner> input;
vector<bool> done;
vector<Beacon> positions;

void prepare() {
	string s;
	Scanner scan;
	while(getline(cin, s)){
		if(s == ""){
			input.push_back(scan);
		} else if(s[1] == '-') {
			scan = Scanner();
		} else {
			auto arr = split_line(s, ",");
			scan.add_beacon({stoi(arr[0]), stoi(arr[1]), stoi(arr[2])});
		}
	}
	input.push_back(scan);
	
	done = vector<bool>(input.size(), false);
	positions = vector<Beacon>(input.size(), {0,0,0});
}

ll get_beacon_id(Beacon b){
	return ((ll)(b.x * 100000000LL)) + ((ll)(b.y * 10000LL)) + ((ll)(b.z));
}

bool try_resolve(int ia, int ib) {
	auto& scanA = input[ia];
	auto& scanB = input[ib];
	
	set<ll> ids;
	for(auto& it : scanA.get_beacons()){
		ids.insert(get_beacon_id(it));
	}
	
	for(int xi=0;xi<4;xi++) {
		for(int yi=0;yi<4;yi++){
			for(int zi=0;zi<4;zi++){
				// Try to match scans
				for(auto& itA : scanA.get_beacons()){
					for(auto& itB : scanB.get_beacons()){
						int mx = itB.x-itA.x;
						int my = itB.y-itA.y;
						int mz = itB.z-itA.z;
						
						int matchCount = 0;
						for(auto& itC : scanB.get_beacons()){
							Beacon b{itC.x-mx, itC.y-my, itC.z-mz};
							if(ids.count(get_beacon_id(b))){
								matchCount++;
							}
						}
						if(matchCount >= 12){
							// Found!
							done[ib] = true;
							positions[ib] = {positions[ia].x+mx, positions[ia].y+my, positions[ia].z+mz};
							return true;
						}
					}
				}
				
				scanB.rotateZ(1);
			}
			scanB.rotateY(1);
		}
		scanB.rotateX(1);
	}
	return false;
}

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

ll first() {
	done[0] = true;
	
	queue<int> q;
	q.push(0);
	
	int cnt = 0;
	
	while(!q.empty()) {
		int ind = q.front();
		q.pop();
		
		print_progress((double)(++cnt)/input.size());
		
		for(int j=0;j<input.size();j++){
			if(!done[j]) {
				if(try_resolve(ind, j)) {
					q.push(j);
				}
			}
		}
	}
	
	cout << "\033[K"; // erase line
	
	for(auto it : done){
		assert(it);
	}
	
	int sz = 0;
	for(auto& scan : input){
		sz += scan.get_beacons().size();
	}
	
	set<ll> ids;
	for(int i=0;i<input.size();i++){
		auto& scan = input[i];
		for(auto& it : scan.get_beacons()){
			ids.insert(get_beacon_id( {it.x-positions[i].x, it.y-positions[i].y, it.z-positions[i].z} ));
		}
	}
	
	return ids.size();
}

ll second() {
	int mx = 0;
	for(auto& ita : positions) {
		for(auto& itb : positions) {
			mx = max(mx, abs(ita.x-itb.x) + abs(ita.y-itb.y) + abs(ita.z-itb.z));
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
