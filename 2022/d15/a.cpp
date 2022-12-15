#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Sensor {
	int x;
	int y;
	int fx;
	int fy;
};

struct Segment {
	int begin;
	int end;
};

vector<Sensor> sensors;
vector<int> distances;

int distance(int x, int y, int fx, int fy) {
	return abs(y-fy) + abs(x-fx);
}

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, ": ");
		auto posarr = split_line(arr[0].substr(10), ", ");
		auto findarr = split_line(arr[1].substr(21), ", ");
		sensors.push_back({stoi(split_line(posarr[0], "=")[1]), stoi(split_line(posarr[1], "=")[1]), stoi(split_line(findarr[0], "=")[1]), stoi(split_line(findarr[1], "=")[1])});
	}
	for(auto &sensor : sensors) {
		distances.push_back(distance(sensor.x, sensor.y, sensor.fx, sensor.fy));
	}
}

vector<Segment> join_segments(vector<Segment> segments) {
	vector<Segment> result;
	sort(segments.begin(), segments.end(), [](auto& left, auto& right){
		return left.begin < right.begin;
	});
	Segment current = segments[0];
	for(int i=1;i<segments.size();i++) {
		if(segments[i].begin <= current.end+1) {
			current.end = max(current.end, segments[i].end);
			continue;
		}
		result.push_back(current);
		current = segments[i];
	}
	result.push_back(current);
	return result;
}

vector<Segment> get_row_segs(int row) {
	vector<Segment> covered_segs;
	int j=0;
	for(auto &sensor : sensors) {
		int y_dist = distance(sensor.x, sensor.y, sensor.x, row);
		if (y_dist <= distances[j]) {
			int dist_plus = distances[j]-y_dist;
			covered_segs.push_back({sensor.x-dist_plus, sensor.x+dist_plus});
		}
		j++;
	}
	return join_segments(covered_segs);
}

ll first() {
	const int Y_CALC = 2000000;
	
	vector<Segment> covered_segs = get_row_segs(Y_CALC);
	
	set<int> found_x;
	int sum = 0;
	for(auto& seg : covered_segs) {
		sum += seg.end-seg.begin+1;
	}
	for(auto& sensor : sensors) {
		for(auto &seg : covered_segs) {
			if (sensor.y == Y_CALC && sensor.x >= seg.begin && sensor.x <= seg.end) {
				sum--;
				break;
			}
		}
		for(auto &seg : covered_segs) {
			if (sensor.fy == Y_CALC && sensor.fx >= seg.begin && sensor.fx <= seg.end && !found_x.count(sensor.fx)) {
				found_x.insert(sensor.fx);
				sum--;
				break;
			}
		}
	}
	
	return sum;
}

ll get_frek(ll x, ll y) {
	return x * 4000000LL + y;
}

ll second() {
	ll F_X_START = 0;
	ll F_X_END = 4000000;
	ll F_Y_START = 0;
	ll F_Y_END = 4000000;
	
	for(int i=F_Y_START;i<=F_Y_END;i++) {
		auto segs = get_row_segs(i);
		int start = 0;
		int finish = segs.size()-1;
		while(segs[finish].begin > F_X_END) {
			finish--;
		}
		while(segs[start].end < F_X_START) {
			start++;
		}
		if (segs[start].begin > F_X_START) {
			return get_frek(F_X_START, i);
		}
		if (segs[finish].end < F_X_END) {
			return get_frek(F_X_END, i);
		}
		if (start != finish) {
			return get_frek(segs[start].end+1, i);
		}
	}
	
	return 0;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
