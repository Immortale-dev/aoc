#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Pt3 {
	int x,y,z;
};

vector<Pt3> pts;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, ",");
		pts.push_back({stoi(arr[0]), stoi(arr[1]), stoi(arr[2])});
	}
}

int calc_area(vector<Pt3>& pts) {
	int spare = 0;
	for(int i=0;i<pts.size();i++) {
		for(int j=0;j<pts.size();j++) {
			if (i == j) continue;
			auto& p1 = pts[i];
			auto& p2 = pts[j];
			if (abs(p1.x-p2.x) + abs(p1.y-p2.y) + abs(p1.z-p2.z) == 1) {
				spare++;
			}
		}
	}
	return pts.size()*6-spare;
}

ll first() {
	return calc_area(pts);
}

ll second() {
	int minX, maxX, minY, maxY, minZ, maxZ;
	minX = maxX = pts[0].x;
	minY = maxY = pts[0].y;
	minZ = maxZ = pts[0].z;
	for(auto &it : pts) {
		minX = min(minX, it.x);
		maxX = max(maxX, it.x);
		minY = min(minY, it.y);
		maxY = max(maxY, it.y);
		minZ = min(minZ, it.z);
		maxZ = max(maxZ, it.z);
	}
	
	vector<vector<vector<int>>> space(maxX+1, vector<vector<int>>(maxY+1, vector<int>(maxZ+1, 0)));
	for(auto &pt : pts) {
		space[pt.x][pt.y][pt.z] = 1;
	}
	
	queue<Pt3> expand;
	for(int x=minX;x<=maxX;x++) {
		for(int y=minY;y<=maxY;y++) {
			for(int z=minZ;z<=maxZ;z++) {
				if (x == minX || x == maxX || y == minY || y == maxY || z == minZ || z == maxZ) {
					expand.push({x,y,z});
				}
			}
		}
	}
	
	while(!expand.empty()) {
		Pt3 pt = expand.front();
		expand.pop();
		
		if (pt.x < minX || pt.x > maxX || pt.y < minY || pt.y > maxY || pt.z < minZ || pt.z > maxZ) continue;
		if (space[pt.x][pt.y][pt.z]) continue;
		
		space[pt.x][pt.y][pt.z] = 1;
		expand.push({pt.x+1,pt.y,pt.z});
		expand.push({pt.x-1,pt.y,pt.z});
		expand.push({pt.x,pt.y+1,pt.z});
		expand.push({pt.x,pt.y-1,pt.z});
		expand.push({pt.x,pt.y,pt.z+1});
		expand.push({pt.x,pt.y,pt.z-1});
	}
	
	vector<Pt3> trapped;
	for(int x=minX;x<=maxX;x++) {
		for(int y=minY;y<=maxY;y++) {
			for(int z=minZ;z<=maxZ;z++) {
				if (!space[x][y][z]) {
					trapped.push_back({x,y,z});
				}
			}
		}
	}
	
	return calc_area(pts) - calc_area(trapped);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
