#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> field;

vector<int> commands;

int W,H;

void prepare() {
	string s;
	while(getline(cin, s)){
		if (s == "") {
			// field is done;
			break;
		}
		field.push_back(s);
	}
	
	int maxw = 0;
	for(auto& s : field) {
		maxw = max(maxw, (int)s.size());
	}
	
	H = field.size();
	W = maxw;
	
	for(auto &s : field) {
		while(s.size() < W) {
			s.push_back(' ');
		}
	}
	
	getline(cin, s);
	
	auto arrR = split_line(s, "R");
	int ri = 0;
	for(auto &rs : arrR) {
		auto arrL = split_line(rs, "L");
		int li=0;
		for(auto &ls : arrL) {
			commands.push_back(stoi(ls));
			if (li < arrL.size()-1) {
				commands.push_back(-2);
			}
			li++;
		}
		if (ri < arrR.size()-1) {
			commands.push_back(-1);
		}
		ri++;
	}
}

pair<int,int> get_inc(int dir) {
	int ix=0, iy=0;
	if (dir == 0) {
		++ix;
	} else if (dir == 1) {
		++iy;
	} else if (dir == 2) {
		--ix;
	} else {
		--iy;
	}
	return {ix,iy};
}

pair<int,int> fix_pos(int x, int y, int dir) {
	do {
		if (y < 0) y = field.size()-1;
		if (y >= field.size()) y = 0;
		if (x < 0) x = field[y].size()-1;
		if (x >= field[y].size()) x = 0;
		
		if (field[y][x] != ' ') break;
	
		auto [ix, iy] = get_inc(dir);
		x += ix;
		y += iy;
	} while (true);
	return {x,y};
}

pair<int,int> move(int x, int y, int cnt, int dir) {
	while(cnt--) {
		auto [ix, iy] = get_inc(dir);
		auto [nx, ny] = fix_pos(x+ix, y+iy, dir);
		if (field[ny][nx] == '#') break;
		x = nx;
		y = ny;
	}
	return {x,y};
}

ll first() {
	auto [x,y] = fix_pos(0,0,0);
	int dir = 0;
	
	for(auto &com : commands) {
		if (com == -1) {
			dir = (dir+1)%4;
		} else if (com == -2) {
			dir = (dir-1+4)%4;
		} else {
			auto pos = move(x,y,com,dir);
			x = pos.first;
			y = pos.second;
		}
	}
	
	return (y+1)*1000 + (x+1)*4 + dir;
}



pair<pair<int,int>,int> fix_pos_2(int x, int y, int d) {
	do {
		int fy = y;
		int fx = x;
		int fd = d;

		int ny = y;
		int nx = x;
		int dir = d;

		if (0 <= ny && ny <= 49 && 50 <= nx && nx <= 99) {
			if (d == 3/*"T"*/ && ny == 0) {
				fy = 150 + (nx - 50);
				fx = 0;
				fd = 0;//"R";
			} else if (d == 2/*"L"*/ && nx == 50) {
				fy = 149 - (ny - 0);
				fx = 0;
				fd = 0;//"R";
			}
		} else if (0 <= ny && ny <= 49 && 100 <= nx && nx <= 149) {
			if (d == 3/*"T"*/ && ny == 0) {
				fy = 199;
				fx = 0 + (nx - 100);
				fd = 3;//"T";
			} else if (d == 0/*"R"*/ && nx == 149) {
				fy = 149 - (ny - 0);
				fx = 99;
				fd = 2;//"L";
			} else if (d == 1/*"D"*/ && ny == 49) {
				fy = 50 + (nx - 100);
				fx = 99;
				fd = 2;//"L";
			}
		} else if (50 <= ny && ny <= 99 && 50 <= nx && nx <= 99) {
			if (d == 2/*"L"*/ && nx == 50) {
				fy = 100;
				fx = 0 + (ny - 50);
				fd = 1;//"D";
			} else if (d == 0/*"R"*/ && nx == 99) {
				fy = 49;
				fx = 100 + (ny - 50);
				fd = 3;//"T";
			}
		} else if (100 <= ny && ny <= 149 && 50 <= nx && nx <= 99) {
			if (d == 0/*"R"*/ && nx == 99) {
				fy = 49 - (ny - 100);
				fx = 149;
				fd = 2;//"L";
			} else if (d == 1/*"D"*/ && ny == 149) {
				fy = 150 + (nx - 50);
				fx = 49;
				fd = 2;//"L";
			}
		} else if (100 <= ny && ny <= 149 && 0 <= nx && nx <= 49) {
			if (d == 2/*"L"*/ && nx == 0) {
				fy = 49 - (ny - 100);
				fx = 50;
				fd = 0;//"R";
			} else if (d == 3/*"T"*/ && ny == 100) {
				fy = 50 + (nx - 0);
				fx = 50;
				fd = 0;//"R";
			}
		} else if (150 <= ny && ny <= 199 && 0 <= nx && nx <= 49) {
			if (d == 2/*"L"*/ && nx == 0) {
				fy = 0;
				fx = 50 + (ny - 150);
				fd = 1;//"D";
			} else if (d == 1/*"D"*/ && ny == 199) {
				fy = 0;
				fx = 100 + (nx - 0);
				fd = 1;//"D";
			} else if (d == 0/*"R"*/ && nx == 49) {
				fy = 149;
				fx = 50 + (ny - 150);
				fd = 3;//"T";
			}
		}

		if (ny == fy && nx == fx) {
			auto [ix, iy] = get_inc(d);
			y += iy;
			x += ix;
		} else {
			y = fy;
			x = fx;
			d = fd;
		}
	} while(field[y][x] == ' ');
	
	return {{x, y}, d};
}

pair<int,int> move_2(int x, int y, int cnt, int &dir) {
	while(cnt--) {
		auto npos = fix_pos_2(x, y, dir);
		int ny = npos.first.second;
		int nx = npos.first.first;
		int nd = npos.second;
		if (field[ny][nx] == '#') break;
		x = nx;
		y = ny;
		dir = nd;
	}
	return {x,y};
}

ll second() {
	auto [x,y] = fix_pos(0,0,0);
	int dir = 0;
	
	for(auto &com : commands) {
		if (com == -1) {
			dir = (dir+1)%4;
		} else if (com == -2) {
			dir = (dir-1+4)%4;
		} else {
			auto pos = move_2(x,y,com,dir);
			x = pos.first;
			y = pos.second;
		}
	}
	
	return (y+1)*1000 + (x+1)*4 + dir;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
