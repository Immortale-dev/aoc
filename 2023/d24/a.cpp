#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;
typedef long double ld;

//=======================================//

struct Pt {
	ld x,y,z;
};

struct Line {
	Pt pos;
	Pt vel;
};

vector<Line> lines;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " @ ");
		auto posArr = split_line(arr[0], ", ");
		auto velArr = split_line(arr[1], ", ");
		ld x = stoll(posArr[0]);
		ld y = stoll(posArr[1]);
		ld z = stoll(posArr[2]);
		ld vx = stoll(velArr[0]);
		ld vy = stoll(velArr[1]);
		ld vz = stoll(velArr[2]);

		lines.push_back({{x,y,z},{vx,vy,vz}});
	}
}

Pt intersect2d(Line& l1, Line& l2) {
	ld a1 = l1.vel.y;
	ld b1 = -l1.vel.x;
	ld c1 = a1 * l1.pos.x + b1 * l1.pos.y;

	ld a2 = l2.vel.y;
	ld b2 = -l2.vel.x;
	ld c2 = a2 * l2.pos.x + b2 * l2.pos.y;

	ld d = a1 * b2 - a2 * b1;

	if (d == 0) {
		return {0,0,0};
	}

	ld x = (b2*c1 - b1*c2) / d;
	ld y = (a1*c2 - a2*c1) / d;
	return {x,y,0};
}

ll first() {
	ll MN = 200000000000000;
	ll MX = 400000000000000;
	int res = 0;
	for(int i=0;i<lines.size();i++) {
		for(int j=i+1;j<lines.size();j++) {
			auto& l1 = lines[i];
			auto& l2 = lines[j];

			auto c = intersect2d(l1, l2);
			if (c.x - l1.pos.x > 0 && l1.vel.x < 0 || c.x - l1.pos.x < 0 && l1.vel.x > 0) {
				// line1 intersects in the past
				continue;
			}
			if (c.x - l2.pos.x > 0 && l2.vel.x < 0 || c.x - l2.pos.x < 0 && l2.vel.x > 0) {
				// line2 intersects in the past
				continue;
			}
			if (c.x < MN || c.x > MX || c.y < MN || c.y > MX) {
				// intersection outside of test area
				continue;
			}

			res++;
		}
	}

	return res;
}

ll second() {
	int cntx = 0;
	int cnty = 0;
	int cntz = 0;
	unordered_map<int, int> vx;
	unordered_map<int, int> vy;
	unordered_map<int, int> vz;
	vector<int> rvx;
	vector<int> rvy;
	vector<int> rvz;
	for(int i=0;i<lines.size();i++) {
		for(int j=i+1;j<lines.size();j++) {
			if (lines[i].vel.x == lines[j].vel.x) {
				++cntx;
				for(int v = -1000;v<=1000;v++) {
					if (v == (ll)lines[i].vel.x) continue;
					if ( ((ll)(lines[i].pos.x - lines[j].pos.x) % (v - (ll)lines[i].vel.x)) == 0 ) {
						vx[v]++;
					}
				}
			}
			if (lines[i].vel.y == lines[j].vel.y) {
				++cnty;
				for(int v=-1000;v<=1000;v++) {
					if (v == (ll)lines[i].vel.y) continue;
					if ( (ll)(lines[i].pos.y - lines[j].pos.y) % ( v- (ll)lines[i].vel.y) == 0 ) {
						vy[v]++;
					}
				}
			}
			if (lines[i].vel.z == lines[j].vel.z) {
				++cntz;
				for(int v=-1000;v<=1000;v++) {
					if (v == (ll)lines[i].vel.z) continue;
					if ( (ll)(lines[i].pos.z - lines[j].pos.z) % (v - (ll)lines[i].vel.z) == 0 ) {
						vz[v]++;
					}
				}
			}
		}
	}
	for(auto& p : vx) {
		if (p.second == cntx) {
			rvx.push_back(p.first);
		}
	}
	for(auto& p : vy) {
		if (p.second == cnty) {
			rvy.push_back(p.first);
		}
	}
	for(auto& p : vz) {
		if (p.second == cntz) {
			rvz.push_back(p.first);
		}
	}

	assert(rvx.size() == 1);
	assert(rvy.size() == 1);
	assert(rvz.size() == 1);

	ld r_vx = rvx[0];
	ld r_vy = rvy[0];
	ld r_vz = rvz[0];

	ld r1 = (lines[0].vel.y-r_vy)/(lines[0].vel.x-r_vx);
	ld r2 = (lines[1].vel.y-r_vy)/(lines[1].vel.x-r_vx);
	ld c1 = lines[0].pos.y - lines[0].pos.x * r1;
	ld c2 = lines[1].pos.y - lines[1].pos.x * r2;

	ll res_x = (c2-c1)/(r1-r2);
	ll res_y = r1 * res_x + c1;
	ll res_z = lines[0].pos.z + (lines[0].vel.z - r_vz) * ((res_x - lines[0].pos.x) / (lines[0].vel.x - r_vx));

	return res_x + res_y + res_z;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
