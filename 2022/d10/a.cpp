#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "./device.cpp"

typedef long long int ll;

//=======================================//

vector<Device::Command> commands;
set<int> checks{20, 60, 100, 140, 180, 220};
const int SCREEN_W = 40, SCREEN_H = 6;
vector<bool> screen(SCREEN_H*SCREEN_W, false);

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " ");
		if (arr[0] == "addx") {
			commands.push_back({arr[0], {stoi(arr[1])}});
		} else {
			commands.push_back({arr[0], {}});
		}
	}
}

ll first() {
	ll sum = 0;
	Device device;
	for(auto& com : commands) {
		device.input(com);
	}
	int step = 1;
	while(!device.empty()) {
		if (checks.count(step)) {
			sum += device.get_x() * step;
		}
		device.tick();
		step++;
	}
	return sum;
}

string second() {
	Device device;
	for(auto& com : commands) {
		device.input(com);
	}
	int step = 0;
	while(!device.empty()) {
		if((step%SCREEN_W) >= device.get_x()-1 && (step%SCREEN_W) <= device.get_x()+1) {
			screen[step] = true;
		}
		device.tick();
		step++;
	}
	cout << endl;
	for(int i=0;i<SCREEN_H;i++) {
		for(int j=0;j<SCREEN_W;j++) {
			cout << (screen[i*SCREEN_W+j] ? '#' : '.');
		}
		cout << endl;
	}
	return "";
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
