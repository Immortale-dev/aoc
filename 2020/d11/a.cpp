#include <bits/stdc++.h>

using namespace std;

vector<string> input;
int W,H;

void prepare()
{
	string s;
	while(getline(cin,s)){
		input.push_back(s);
	}
	W = input[0].size();
	H = input.size();
}

bool differ(vector<string> a, vector<string> b)
{
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(a[i][j] != b[i][j])
				return true;
		}
	}
	return false;
}

vector<string> next(vector<string> a)
{
	vector<string> res(H);
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			char c = a[i][j];
			
			int cf = 0;
			if(i-1 >= 0 && j-1 >= 0 && a[i-1][j-1] == '#') cf++;
			if(i-1 >= 0 && a[i-1][j] == '#') cf++;
			if(i-1 >= 0 && j+1 < W && a[i-1][j+1] == '#') cf++;
			if(i+1 < H && j-1 >= 0 && a[i+1][j-1] == '#') cf++;
			if(i+1 < H && a[i+1][j] == '#') cf++;
			if(i+1 < H && j+1 < W && a[i+1][j+1] == '#') cf++;
			if(j-1 >= 0 && a[i][j-1] == '#') cf++;
			if(j+1 < W && a[i][j+1] == '#') cf++;
			
			if(c == 'L' && cf == 0){
				res[i].push_back('#');
			} else if(c == '#' && cf >= 4) {
				res[i].push_back('L');
			} else {
				res[i].push_back(c);
			}
		}
	}
	return res;
}

bool occupied_direction(vector<string>& a, int i, int j, int pi, int pj)
{
	do{
		i+=pi;
		j+=pj;
		if(i < 0 || i >= H || j < 0 || j >= W) return false;
		if(a[i][j] == 'L') return false;
		if(a[i][j] == '#') return true;
		if(a[i][j] == '.') continue;
	}while(true);
	return false;
}

vector<string> next_second(vector<string> a)
{
	vector<string> res(H);
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			char c = a[i][j];
			
			int cf = 0;
			if(occupied_direction(a,i,j,-1,-1)) cf++;
			if(occupied_direction(a,i,j,-1,0)) cf++;
			if(occupied_direction(a,i,j,-1,1)) cf++;
			if(occupied_direction(a,i,j,1,-1)) cf++;
			if(occupied_direction(a,i,j,1,0)) cf++;
			if(occupied_direction(a,i,j,1,1)) cf++;
			if(occupied_direction(a,i,j,0,-1)) cf++;
			if(occupied_direction(a,i,j,0,1)) cf++;
			
			if(c == 'L' && cf == 0){
				res[i].push_back('#');
			} else if(c == '#' && cf >= 5) {
				res[i].push_back('L');
			} else {
				res[i].push_back(c);
			}
		}
	}
	return res;
}

void prnt(vector<string> a)
{
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			cout << a[i][j];
		}
		cout << endl;
	}
}

int first()
{
	auto a = input;
	auto b = a;
	do{
		a = b;
		b = next(a);
	}while(differ(a,b));
	
	int res = 0;
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(a[i][j] == '#')
				res++;
		}
	}
	
	return res;
}

int second()
{
	auto a = input;
	auto b = a;
	do{
		a = b;
		b = next_second(a);
	}while(differ(a,b));
	
	int res = 0;
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(a[i][j] == '#')
				res++;
		}
	}
	
	return res;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
