#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<vector<int> > input;

void prepare() {
	string s;
	while(getline(cin, s)){
		vector<int> line;
		for(int i=0;i<s.size();i++){
			line.push_back(s[i]-'0');
		}
		input.push_back(line);
	}
}

vector<pair<int, int> > get_basins_list() {
	vector<pair<int, int> > ret;
	
	int max_y = input.size();
	int max_x = input[0].size();
	
	int res = 0;
	
	for(int i=0;i<max_y;i++) {
		for(int j=0;j<max_x;j++) {
			int val = input[i][j];
			bool good = true;
			if(i > 0 && val >= input[i-1][j]) {
				good = false;
			}
			if(j > 0 && val >= input[i][j-1]) {
				good = false;
			}
			if(i < max_y-1 && val >= input[i+1][j]) {
				good = false;
			}
			if(j < max_x-1 && val >= input[i][j+1]) {
				good = false;
			}
			
			if(good) {
				ret.push_back(make_pair(i,j));
			}
		}
	}
	
	return ret;
}

void print_matrix(vector<vector<int> >& matrix) {
	cout << endl;
	for(auto& it : matrix) {
		for(auto& ix : it) {
			if(!ix) cout << '.'; else cout << ix;
		}
		cout << endl;
	}
}

ll first() {
	auto basins = get_basins_list();
	
	int res = 0;
	for(auto& it : basins) {
		res += input[it.first][it.second]+1;
	}
	
	return res;
}

ll second() {
	auto basins = get_basins_list();
	
	int max_y = input.size();
	int max_x = input[0].size();
	
	vector<vector<int>> areas(max_y, vector<int>(max_x));
	
	int id = 1;
	queue<pair<int,int> > q;
	for(auto& it : basins) {
		id++;
		q.push(it);
		
		while(!q.empty()) {
			pair<int,int> cell = q.front();
			q.pop();
			if(cell.first < 0 || cell.first >= max_y || cell.second < 0 || cell.second >= max_x || input[cell.first][cell.second] == 9 || areas[cell.first][cell.second] != 0) {
				continue;
			}
			areas[cell.first][cell.second] = id;
			q.push(make_pair(cell.first+1,cell.second));
			q.push(make_pair(cell.first-1,cell.second));
			q.push(make_pair(cell.first,cell.second+1));
			q.push(make_pair(cell.first,cell.second-1));
		}
	}
	
	//print_matrix(areas);
	
	vector<int> area_sizes(id+10, 0);
	for(int i=0;i<max_y;i++){
		for(int j=0;j<max_x;j++){
			if(areas[i][j]) {
				area_sizes[areas[i][j]]++;
			}
		}
	}
	
	sort(area_sizes.begin(), area_sizes.end(), greater<int>());
	
	return (ll)area_sizes[0] * area_sizes[1] * area_sizes[2];
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
