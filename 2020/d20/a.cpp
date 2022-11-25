#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

struct Tile{
	ll id;
	vector<string> pattern;
	
	int width, height;
	
	Tile(){ throw runtime_error("No Way!"); }
	Tile(ll id, vector<string> pattern) : id(id), pattern(pattern){
		height = pattern.size();
		width = pattern[0].size(); 
	}
	void flipx(){
		for(int i=0;i<height;i++){
			for(int j=0;j<width/2;j++){
				swap(pattern[i][j], pattern[i][width-j-1]);
			}
		}
	}
	void flipy(){
		for(int i=0;i<height/2;i++){
			swap(pattern[i], pattern[height-i-1]);
		}
	}
	void rotate()
	{
		vector<string> res;
		for(int i=0;i<width;i++){
			string s;
			for(int j=0;j<height;j++){
				s.push_back(pattern[j][i]);
			}
			reverse(s.begin(), s.end());
			res.push_back(s);
		}
		pattern = res;
	}
};

unordered_map<ll, Tile> input;

void prepare()
{
	string s;
	vector<string> pat;
	ll id;
	while(getline(cin, s)){
		if(s[0] == 'T'){
			string str = split_line(s, " ")[1];
			id = stoll(str.substr(0, str.size()-1));
			continue;
		}
		if(s == ""){
			input.insert(make_pair(id, Tile(id, pat)));
			pat.resize(0);
			continue;
		}
		pat.push_back(s);
	}
	input.insert(make_pair(id, Tile(id, pat)));
}

string get_top_line(Tile& t)
{
	return t.pattern[0];
}

string get_left_line(Tile& t)
{
	string s;
	for(int i=t.height-1;i>=0;i--){
		s.push_back(t.pattern[i][0]);
	}
	return s;
}

string get_bottom_line(Tile& t)
{
	string s = t.pattern[t.pattern.size()-1];
	reverse(s.begin(), s.end());
	return s;
}

string get_right_line(Tile& t)
{
	string s;
	for(int i=0;i<t.height;i++){
		s.push_back(t.pattern[i][9]);
	}
	return s;
}

ll line_to_num(string s)
{
	ll n = 0;
	for(int i=0;i<s.size();i++){
		if(s[i] == '#') n = n | 1;
		if(s.size()-1 != i) n <<= 1;
	}
	return n;
}


unordered_map<ll, ll> arr;
unordered_map<ll, vector<int>> cnts;

void prepare_other()
{
	if(arr.size()) return;
	
	string s;
	for(auto& itt : input){
		auto& it = itt.second;
		s = get_top_line(it);
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
		
		reverse(s.begin(), s.end());
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
		
		s = get_bottom_line(it);
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
		
		reverse(s.begin(), s.end());
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
		
		s = get_left_line(it);
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
		
		reverse(s.begin(), s.end());
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
		
		s = get_right_line(it);
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
		
		reverse(s.begin(), s.end());
		arr.insert(make_pair(line_to_num(s), it.id));
		cnts[line_to_num(s)].push_back(it.id);
	}
}

ll first()
{
	prepare_other();
	
	unordered_map<ll, int> garr;
	for(auto& it : cnts){
		if(it.second.size() == 1){
			garr[arr[it.first]]++;
		}
	}
	
	ll res = 1;
	for(auto& it : garr){
		if(it.second == 4){
			res *= it.first;
		}
	}
	
	return res;
}

//////////////////////////////////////////////////////////


struct MT{
	MT *top=nullptr, *right=nullptr, *bottom=nullptr, *left=nullptr;
	ll id;
};

unordered_map<ll, MT*> mt_map;

ll get_else_id(ll a, ll id)
{
	auto& v = cnts[a];
	if(v[0] == id) return v[1];
	return v[0];
}

void transform(ll id, ll a, string side)
{
	Tile& t = input[id];
	for(int i=0;i<8;i++){
		ll b;
		if(side == "top") b = line_to_num(get_top_line(t));
		if(side == "right") b = line_to_num(get_right_line(t));
		if(side == "bottom") b = line_to_num(get_bottom_line(t));
		if(side == "left") b = line_to_num(get_left_line(t));
		
		if(b == a){
			if(side == "top" || side == "bottom"){
				t.flipx();
			} else {
				t.flipy();
			}
			return;
		}
		
		t.rotate();
		if(i == 3){
			t.flipx();
		}
	}
	
	throw runtime_error("No Way!");
}

unordered_set<ll> r_done;

void req(MT* a)
{
	if(!a) return;
	if(r_done.count(a->id)) return;
	r_done.insert(a->id);
	Tile& t = input[a->id];
	
	ll top = line_to_num(get_top_line(t));
	ll right = line_to_num(get_right_line(t));
	ll bottom = line_to_num(get_bottom_line(t));
	ll left = line_to_num(get_left_line(t));
	
	MT *mt_top = nullptr, *mt_right = nullptr, *mt_bottom = nullptr, *mt_left = nullptr;
	if(cnts[top].size() > 1){
		ll id = get_else_id(top, a->id);
		if(mt_map.count(id)){ 
			a->top = mt_map[id];
		} else {
			mt_top = new MT;
			mt_map[id] = mt_top;
			mt_top->id = id;
			a->top = mt_top;
			transform(id, top, "bottom");
		}
	}
	if(cnts[right].size() > 1){
		ll id = get_else_id(right, a->id);
		if(mt_map.count(id)){ 
			a->right = mt_map[id];
		} else {
			mt_right = new MT;
			mt_map[id] = mt_right;
			mt_right->id = id;
			a->right = mt_right;
			transform(id, right, "left");
		}
	}
	if(cnts[bottom].size() > 1){
		ll id = get_else_id(bottom, a->id);
		if(mt_map.count(id)){ 
			a->bottom = mt_map[id];
		} else {
			mt_bottom = new MT;
			mt_map[id] = mt_bottom;
			mt_bottom->id = id;
			a->bottom = mt_bottom;
			transform(id, bottom, "top");
		}
	}
	if(cnts[left].size() > 1){
		ll id = get_else_id(left, a->id);
		if(mt_map.count(id)){ 
			a->left = mt_map[id];
		} else {
			mt_left = new MT;
			mt_map[id] = mt_left;
			mt_left->id = id;
			a->left = mt_left;
			transform(id, left, "right");
		}
	}
	
	req(a->top);
	req(a->right);
	req(a->bottom);
	req(a->left);
}


bool done[12][12];
char image[12*8][12*8];

void fill(Tile& t, int x, int y)
{
	if(x > 11 || y > 11) throw runtime_error("No Way!");
	for(int i=1;i<t.height-1;i++){
		for(int j=1;j<t.width-1;j++){
			image[y*8+i-1][x*8+j-1] = t.pattern[i][j];
		}
	}
}

void req_build(MT* a, int x, int y)
{
	if(!a) return;
	if(done[x][y]) return;
	
	done[x][y] = true;
	fill(input[a->id], x, y);
	
	req_build(a->right, x+1, y);
	req_build(a->bottom, x, y+1);
}

void print_image()
{
	for(int i=0;i<12*8;i++){
		cout << "_";
	}
	cout << endl;
	for(int i=0;i<12*8;i++){
		for(int j=0;j<12*8;j++){
			cout << image[i][j];
		}
		cout << endl;
	}
}

void rotate_image()
{
	int W = 8*12;
	char new_image[W][W];
	for(int i=0;i<W;i++){
		for(int j=0;j<W;j++){
			new_image[i][j] = image[j][i];
		}
		for(int j=0;j<W/2;j++){
			swap(new_image[i][j], new_image[i][W-j-1]);
		}
	}
	
	for(int i=0;i<W;i++){
		for(int j=0;j<W;j++){
			image[i][j] = new_image[i][j];
		}
	}
}

void flip_image()
{
	int W = 8*12;
	for(int i=0;i<W;i++){
		for(int j=0;j<W/2;j++){
			swap(image[i][j], image[i][W-j-1]);
		}
	}
}

vector<string> monster = {
	"                  # ",
	"#    ##    ##    ###",
	" #  #  #  #  #  #   "
};

int find_monsters()
{
	int res = 0;
	int W = 8*12;
	int MW = monster[0].size();
	int MH = monster.size();
	for(int i=0;i<W;i++){
		for(int j=0;j<W;j++){
			if(W-i >= MH && W-j >= MW){
				bool found = true;
				for(int ii=0;ii<MH;ii++){
					for(int jj=0;jj<MW;jj++){
						if(monster[ii][jj] == '#' && image[i+ii][j+jj] != '#'){
							found = false;
							break;
						}
					}
				}
				if(found){
					res++;
					for(int ii=0;ii<MH;ii++){
						for(int jj=0;jj<MW;jj++){
							if(monster[ii][jj] == '#'){
								image[i+ii][j+jj] = 'O';
							}
						}
					}
				}
			}
		}
	}
	return res;
}

ll second()
{
	// preapre other things
	prepare_other();

	// Build an image
	ll one_id = input.begin()->first;
	MT* part = new MT;
	part->id = one_id;
	mt_map[one_id] = part;
	req(part);
	
	// write image to array
	while(part->top){ part = part->top; }
	while(part->left){ part = part->left; }
	req_build(part,0,0);
	
	// Find monsters
	bool found = false;
	for(int i=0;i<10;i++){
		if(find_monsters()){
			found = true;
			break;
		}
		rotate_image();
		if(i == 4) flip_image();
	}
	
	if(!found){
		throw runtime_error("Not Found Monsters :(");
	}
	
	int res = 0;
	for(int i=0;i<8*12;i++){
		for(int j=0;j<8*12;j++){
			if(image[i][j] == '#') res++;
		}
	}
	
	return res;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	
	// Print image with monsters
	print_image();
	
	return 0;
}
