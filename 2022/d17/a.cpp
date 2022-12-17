#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

string input;

void prepare() {
	string s;
	while(getline(cin, s)){
		input = s;
	}
}

vector<vector<bool>> create_field(int height) {
	return vector<vector<bool>>(height, vector<bool>(7, false));
}

bool collides(vector<vector<bool>>& field, int fig_type, int x, int y) {
	if (y < 0 || x < 0) return true;
	if (fig_type == 0) {
		if (x >= 4) return true;
		return (field[y][x] || field[y][x+1] || field[y][x+2] || field[y][x+3]);
	}
	if (fig_type == 1) {
		if (x >= 5) return true;
		return (field[y][x+1] || field[y+1][x+1] || field[y+1][x] || field[y+1][x+2] || field[y+2][x+1]);
	}
	if (fig_type == 2) {
		if (x >= 5) return true;
		return (field[y][x] || field[y][x+1] || field[y][x+2] || field[y+1][x+2] || field[y+2][x+2]);
	}
	if (fig_type == 3) {
		if (x >= 7) return true;
		return (field[y][x] || field[y+1][x] || field[y+2][x] || field[y+3][x]);
	}
	if (fig_type == 4) {
		if (x >= 6) return true;
		return (field[y][x] || field[y][x+1] || field[y+1][x] || field[y+1][x+1]);
	}
	throw logic_error("Wrong figure ot check");
}

int find_max(vector<vector<bool>>& field, int prev_max) {
	for(int i=prev_max;;i++) {
		bool found = false;
		for(int j=0;j<7;j++) {
			if (field[i][j]) {
				found = true;
				break;
			}
		}
		if (!found) return i;
	}
	throw logic_error("Something went wrong");
}

int get_shift(int ind) {
	return input[ind] == '<' ? -1 : 1;
}

void put_fig(vector<vector<bool>>& field, int fig_type, int x, int y) {
	if (fig_type == 0) {
		field[y][x] = field[y][x+1] = field[y][x+2] = field[y][x+3] = true;
	} else if (fig_type == 1) {
		field[y][x+1] = field[y+1][x+1] = field[y+1][x] = field[y+1][x+2] = field[y+2][x+1] = true;
	} else if (fig_type == 2) {
		field[y][x] = field[y][x+1] = field[y][x+2] = field[y+1][x+2] = field[y+2][x+2] = true;
	} else if (fig_type == 3) {
		field[y][x] = field[y+1][x] = field[y+2][x] = field[y+3][x] = true;
	} else if (fig_type == 4) {
		field[y][x] = field[y][x+1] = field[y+1][x] = field[y+1][x+1] = true;
	} else {
		throw logic_error("Wrong figure to put");
	}
}

ll first() {
	auto field = create_field(10000);
	int max_h = 0;
	
	int fig = 0;
	int ind = 0;
	for(int i=0;i<2022;i++) {
		//cout << "I: " << i << endl;
		int figx = 2;
		int figy = max_h+3;
		while(true) {
			//cout << "F: " << fig << " " << ind << " " << figx << "x" << figy << endl;
			if (!collides(field, fig, figx + get_shift(ind), figy)) {
				figx += get_shift(ind);
			}
			ind = (ind+1)%input.size();
			if (!collides(field, fig, figx, figy-1)) {
				figy--;
			} else {
				put_fig(field, fig, figx, figy);
				break;
			}
		}
		fig = (fig+1)%5;
		max_h = find_max(field, max_h);
	}
	
	return max_h;
}

bool fields_equal(vector<vector<bool>>& field, vector<vector<bool>>& field2, int max_h) {
	int h = field2.size();
	for(int i=0;i<h;i++) {
		for(int j=0;j<7;j++) {
			if (field[max_h-i][j] != field2[field2.size()-1-i][j]){
				return false;
			}
		}
	}
	return true;
}

ll second() {
	auto field = create_field(200000);
	ll max_h = 0;
	
	int fig = 0;
	int ind = 0;
	
	int saved_fig = 0;
	int saved_ind = 0;
	int saved_max_h = 0;
	int saved_size = 100;
	int saved_i = 0;
	vector<vector<bool>> saved_field = create_field(saved_size);
	
	ll max_h_plus = 0;
	
	ll need_figures = 1000000000000LL;
	
	for(ll i=0;i<need_figures;i++) {
		int figx = 2;
		int figy = max_h+3;
		while(true) {
			if (!collides(field, fig, figx + get_shift(ind), figy)) {
				figx += get_shift(ind);
			}
			ind = (ind+1)%input.size();
			if (!collides(field, fig, figx, figy-1)) {
				figy--;
			} else {
				put_fig(field, fig, figx, figy);
				break;
			}
		}
		fig = (fig+1)%5;
		max_h = find_max(field, max_h);
		
		if (i == 100000) {
			saved_max_h = max_h;
			saved_fig = fig;
			saved_ind = ind;
			saved_i = i;
			for(int j=0;j<saved_size;j++) {
				for(int k=0;k<7;k++) {
					saved_field[saved_size-1-j][k] = field[max_h-j][k];
				}
			}
		}
		if (i > 100000) {
			if (ind == saved_ind && fig == saved_fig && fields_equal(field, saved_field, max_h)) {
				ll left = need_figures - i;
				ll i_diff = i - saved_i;
				ll h_diff = max_h - saved_max_h;
				max_h_plus = (left/i_diff)*h_diff;
				i = need_figures - left%i_diff;
			}
		}
	}
	
	return max_h + max_h_plus;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
