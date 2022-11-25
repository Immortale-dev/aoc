#include <bits/stdc++.h>

using namespace std;

const int DM = 30;

using Cube = vector<vector<vector<vector<bool>>>>;

Cube empty_cube()
{
	return Cube(DM, vector<vector<vector<bool>>>(DM, vector<vector<bool>>(DM, vector<bool>(DM, false))));
}

Cube cube;

void prepare()
{
	cube = empty_cube();
	
	string s;
	int y = 10;
	while(getline(cin, s)){
		for(int i=0;i<s.size();i++){
			cube[10][10][y][i+10] = (s[i] == '#');
		}
		y++;
	}
}

Cube step_3(Cube cube)
{
	Cube nc = empty_cube();
	
	for(int i=1;i<DM-1;i++){
		for(int j=1;j<DM-1;j++){
			for(int k=1;k<DM-1;k++){
				int c = 0;
				for(int li=i-1;li<=i+1;li++){
					for(int lj=j-1;lj<=j+1;lj++){
						for(int lk=k-1;lk<=k+1;lk++){
							if(i == li && j == lj && k == lk) continue;
							if(cube[10][li][lj][lk]) c++;
						}
					}
				}
				if(!cube[10][i][j][k]){
					if(c == 3){
						nc[10][i][j][k] = 1;
					} else {
						nc[10][i][j][k] = 0;
					}
				} else {
					if(c == 2 || c == 3){
						nc[10][i][j][k] = 1;
					} else {
						nc[10][i][j][k] = 0;
					}
				}
			}
		}
	}
	
	return nc;
}

Cube step_4(Cube cube)
{
	Cube nc = empty_cube();
	
	for(int i=1;i<DM-1;i++){
		for(int j=1;j<DM-1;j++){
			for(int k=1;k<DM-1;k++){
				for(int w=1;w<DM-1;w++){
					int c = 0;
					for(int li=i-1;li<=i+1;li++){
						for(int lj=j-1;lj<=j+1;lj++){
							for(int lk=k-1;lk<=k+1;lk++){
								for(int lw=w-1;lw<=w+1;lw++){
									if(i == li && j == lj && k == lk && w == lw) continue;
									if(cube[li][lj][lk][lw]) c++;
								}
							}
						}
					}
					if(!cube[i][j][k][w]){
						if(c == 3){
							nc[i][j][k][w] = 1;
						} else {
							nc[i][j][k][w] = 0;
						}
					} else {
						if(c == 2 || c == 3){
							nc[i][j][k][w] = 1;
						} else {
							nc[i][j][k][w] = 0;
						}
					}
				}
			}
		}
	}
	
	return nc;
}

int first()
{
	Cube cb = cube;
	for(int i=0;i<6;i++){
		cb = step_3(cb);
	}
	
	int res = 0;
	for(int i=0;i<DM;i++){
		for(int j=0;j<DM;j++){
			for(int k=0;k<DM;k++){
				if(cb[10][i][j][k]){
					res++;
				}
			}
		}
	}
	
	return res;
}

int second()
{
	Cube cb = cube;
	for(int i=0;i<6;i++){
		cb = step_4(cb);
	}
	
	int res = 0;
	for(int i=0;i<DM;i++){
		for(int j=0;j<DM;j++){
			for(int k=0;k<DM;k++){
				for(int w=0;w<DM;w++){
					if(cb[i][j][k][w]){
						res++;
					}
				}
			}
		}
	}
	
	return res;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
}
