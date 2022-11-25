#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

int X1,X2,Y1,Y2;

void prepare() {
	string s;
	getline(cin, s);
	auto arr = split_line(s.substr(13), ", ");
	auto arrx = split_line(arr[0].substr(2), "..");
	auto arry = split_line(arr[1].substr(2), "..");
	X1 = stoi(arrx[0]);
	X2 = stoi(arrx[1]);
	Y1 = stoi(arry[0]);
	Y2 = stoi(arry[1]);
	if(X1 > X2) swap(X1,X2);
	if(Y1 > Y2) swap(Y1,Y2);
}

pair<map<int, int>, vector<pair<int,int>>> calc() {
	map<int, int> xs;
	for(int i=0;i<=X2;i++) {
		int sum = 0;
		int vel = i;
		int step = 0;
		while(step < 2000) {
			sum += vel;
			--vel;
			if(vel < 0) vel = 0;
			step++;
			if(sum >= X1 && sum <= X2){
				xs[step]++;
			}
		}
	}
	
	vector<pair<int,int>> ys;
	for(int i=-2000;i<2000;i++){
		int sum = 0;
		int vel = i;
		int step = 0;
		int mx = 0;
		while(sum >= Y2) {
			sum += vel;
			--vel;
			step++;
			mx = max(mx, sum);
			if(sum >= Y1 && sum <= Y2){
				ys.push_back(make_pair(step, mx));
			}
		}
	}
	
	return make_pair(xs,ys);
}

ll first() {
	
	auto ret = calc();
	
	auto &ys = ret.second;
	auto &xs = ret.first;
	
	sort(ys.begin(), ys.end(), [](auto& left, auto& right){
		return left.second > right.second;
	});
	
	for(auto& it : ys){
		if(xs.count(it.first)) return it.second;
	}
	
	return -1;
}

ll second() {
	int cnt = 0;
	
	for(int i=1;i<1000;i++){
		for(int j=-500;j<500;j++){
			ll sumx = 0;
			ll sumy = 0;
			int velx = i;
			int vely = j;
			
			while(sumx <= X2 && sumy >= Y1) {
				sumx += velx;
				sumy += vely;
				velx--;
				vely--;
				if(velx < 0) velx = 0;
				if(sumx >= X1 && sumx <= X2 && sumy >= Y1 && sumy <= Y2){
					cnt++;
					break;
				}
			}
		}
	}
	
	return cnt;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
