#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "../helpers/terminal.cpp"

typedef long long int ll;

//=======================================//

struct BluePrint {
	int ore;
	int clay;
	pair<int,int> obsidian;
	pair<int,int> geode;
};

vector<BluePrint> blueprints;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, ".");
		auto oreArr = split_line(arr[0], " ");
		auto clayArr = split_line(arr[1], " ");
		auto obsArr = split_line(arr[2], " ");
		auto geoArr = split_line(arr[3], " ");
		
		int ore = stoi(oreArr[oreArr.size()-2]);
		int clay = stoi(clayArr[clayArr.size()-2]);
		pair<int,int> obs = make_pair(stoi(obsArr[obsArr.size()-5]), stoi(obsArr[obsArr.size()-2]));
		pair<int,int> geo = make_pair(stoi(geoArr[geoArr.size()-5]), stoi(geoArr[geoArr.size()-2]));
		
		blueprints.push_back({ore, clay, obs, geo});
	}
}

void print_progress(int size, float coof) {
	int pt = size*coof;
	cout << "[";
	for(int i=0;i<pt;i++) cout << "#";
	for(int i=pt+1;i<size;i++) cout << " ";
	cout << "]";
}

int get_state(int ore, int clay, int obs, int geo) {
	return ore * 32 * 32 * 32 + clay * 32 * 32 + obs * 32 + geo;
}

int get_m_state(int ore, int clay, int obs, int geo) {
	return obs*32+clay;
}

void calc_dp(BluePrint& bp, vector<map<int, map<int, int>>>& dp, int time,
				int oreCnt, int clayCnt, int obsCnt, int geoCnt,
				int ore, int clay, int obs, int geo,
				int maxOre, int maxClay, int maxObs, int maxTime)
{
	if (time > maxTime) return;
	int state = get_state(oreCnt, clayCnt, obsCnt, geoCnt);
	int m_state = get_m_state(ore, clay, obs, geo);
	if (dp[time].count(state) && dp[time][state].count(m_state) && dp[time][state][m_state] >= geo) return;

	dp[time][state][m_state] = geo;
	
	if (oreCnt < maxOre && ore >= bp.ore) {
		calc_dp(bp, dp, time+1,
				oreCnt+1, clayCnt, obsCnt, geoCnt,
				ore+oreCnt-bp.ore, clay+clayCnt, obs+obsCnt, geo+geoCnt,
				maxOre, maxClay, maxObs, maxTime);
	}
	if (clayCnt < maxClay && ore >= bp.clay) {
		calc_dp(bp, dp, time+1,
				oreCnt, clayCnt+1, obsCnt, geoCnt,
				ore+oreCnt-bp.clay, clay+clayCnt, obs+obsCnt, geo+geoCnt,
				maxOre, maxClay, maxObs, maxTime);
	}
	if (obsCnt < maxObs && ore >= bp.obsidian.first && clay >= bp.obsidian.second) {
		calc_dp(bp, dp, time+1,
				oreCnt, clayCnt, obsCnt+1, geoCnt,
				ore+oreCnt-bp.obsidian.first, clay+clayCnt-bp.obsidian.second, obs+obsCnt, geo+geoCnt,
				maxOre, maxClay, maxObs, maxTime);
	}
	if (ore >= bp.geode.first && obs >= bp.geode.second) {
		calc_dp(bp, dp, time+1,
				oreCnt, clayCnt, obsCnt, geoCnt+1,
				ore+oreCnt-bp.geode.first, clay+clayCnt, obs+obsCnt-bp.geode.second, geo+geoCnt,
				maxOre, maxClay, maxObs, maxTime);
	}
	calc_dp(bp, dp, time+1,
			oreCnt, clayCnt, obsCnt, geoCnt,
			ore+oreCnt, clay+clayCnt, obs+obsCnt, geo+geoCnt,
			maxOre, maxClay, maxObs, maxTime);
}

int calc_max_blue(BluePrint bp, int maxTime) {
	vector<map<int, map<int, int>>> dp(maxTime+1);
	int maxOre = max(max(bp.ore, bp.clay), max(bp.obsidian.first, bp.geode.first));
	int maxClay = bp.obsidian.second;
	int maxObs = bp.geode.second;
	
	calc_dp(bp, dp, 0,
		1, 0, 0, 0,
		0, 0, 0, 0,
		maxOre, maxClay, maxObs, maxTime);
	
	int maxGeo = 0;
	for(auto& its : dp[maxTime]) {
		for(auto& itm : its.second) {
			maxGeo = max(maxGeo, itm.second);
		}
	}
	
	return maxGeo;
}

ll first() {
	int result = 0;
	int ind=1;
	
	save_cursor();
	for(auto& bp : blueprints) {
		erase_to_end();
		print_progress(10, ((float)ind-1)/blueprints.size());
		cout << flush;
		result += (ind++)*calc_max_blue(bp, 24);
		restore_cursor();
	}
	erase_to_end();
	
	return result;
}

ll second() {
	int result=1;
	
	save_cursor();
	for(int i=0;i<3;i++) {
		erase_to_end();
		print_progress(10, ((float)i)/3);
		cout << flush;
		result *= calc_max_blue(blueprints[i], 32);
		restore_cursor();
	}
	erase_to_end();
	
	return result;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
