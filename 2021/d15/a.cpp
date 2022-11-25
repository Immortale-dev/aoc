#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<vector<int>> input;

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

ll calc(vector<vector<int>>& risks) {
	int W=risks[0].size(), H=risks.size();
	vector<vector<int>> scores(H, vector<int>(W, 999999));
	scores[0][0] = 0;
	
	queue<pair<int,int>> q;
	q.push(make_pair(0,0));
	
	while(!q.empty()) {
		pair<int,int> it = q.front();
		q.pop();
		int y = it.first;
		int x = it.second;
		if(y > 0 && scores[y][x] + risks[y-1][x] < scores[y-1][x]) {
			scores[y-1][x] = scores[y][x]+risks[y-1][x];
			q.push(make_pair(y-1,x));
		}
		if(y < H-1 && scores[y][x] + risks[y+1][x] < scores[y+1][x]) {
			scores[y+1][x] = scores[y][x] + risks[y+1][x];
			q.push(make_pair(y+1,x));
		}
		if(x > 0 && scores[y][x] + risks[y][x-1] < scores[y][x-1]) {
			scores[y][x-1] = scores[y][x] + risks[y][x-1];
			q.push(make_pair(y,x-1));
		}
		if(x < W-1 && scores[y][x] + risks[y][x+1] < scores[y][x+1]) {
			scores[y][x+1] = scores[y][x] + risks[y][x+1];
			q.push(make_pair(y,x+1));
		}
	}
	
	return scores[H-1][W-1];
}

ll first() {
	return calc(input);
}

ll second() {
	int H = input.size();
	int W = input[0].size();
	int NH = H*5;
	int NW = W*5;
	vector<vector<int>> new_input(NH, vector<int>(NW, 0));
	for(int i=0;i<NH;i++){
		for(int j=0;j<NW;j++){
			int y = i%H;
			int x = j%W;
			int plus = i/H + j/W;
			new_input[i][j] = input[y][x]+plus;
			if(new_input[i][j] > 9) {
				new_input[i][j] = (new_input[i][j]%10)+1;
			}
		}
	}
	
	return calc(new_input);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
