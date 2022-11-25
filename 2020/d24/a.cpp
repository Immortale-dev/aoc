#include <bits/stdc++.h>

using namespace std;

vector<string> input;

void prepare()
{
	string s;
	while(getline(cin, s)){
		input.push_back(s);
	}
}

unordered_set<int> tiles;

int get_id(int x, int y)
{
	return y*1000 + x;
}

int first()
{
	for(auto& it : input){
		int x=0,y=0;
		for(int i=0;i<it.size();i++){
			if(it[i] == 'e'){
				x+=2;
				continue;
			}
			if(it[i] == 'w'){
				x-=2;
				continue;
			}
			if(it[i] == 'n' && it[i+1] == 'e'){
				x++;
				y++;
				i++;
				continue;
			}
			if(it[i] == 'n' && it[i+1] == 'w'){
				y++;
				x--;
				i++;
				continue;
			}
			if(it[i] == 's' && it[i+1] == 'e'){
				y--;
				x++;
				i++;
				continue;
			}
			if(it[i] == 's' && it[i+1] == 'w'){
				y--;
				x--;
				i++;
				continue;
			}
			throw runtime_error("No Way!");
		}
		
		int coor = get_id(x, y);
		if(tiles.count(coor)){
			tiles.erase(coor);
		} else {
			tiles.insert(coor);
		}
	}
	
	return tiles.size();
}

int second()
{
	for(int t=0;t<100;t++){
		unordered_set<int> newtiles;
		for(int i=-150;i<=150;i++){
			for(int j=-150;j<=150;j++){
				int id = get_id(j,i);
				bool tile = tiles.count(id);
				
				int cnt = 0;
				if(tiles.count(get_id(j-2, i))) cnt++;
				if(tiles.count(get_id(j+2, i))) cnt++;
				if(tiles.count(get_id(j+1, i+1))) cnt++;
				if(tiles.count(get_id(j+1, i-1))) cnt++;
				if(tiles.count(get_id(j-1, i+1))) cnt++;
				if(tiles.count(get_id(j-1, i-1))) cnt++;
				
				if(tile){
					if(!cnt || cnt > 2){
						//newtiles.erase(id);
					} else {
						newtiles.insert(id);
					}
				} else {
					if(cnt == 2){
						newtiles.insert(id);
					}
				}
			}
		}
		tiles = newtiles;
	}
	
	return tiles.size();
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
