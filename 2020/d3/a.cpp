#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

vector<string> input;

void prepare()
{
	string resp;
	while(getline(cin, resp)){
		input.push_back(resp);
	}
}

int encounter(int mx, int my)
{
	int res = 0;
	int x = 0;
	int y = 0;
	while(y < input.size()){
		if(input[y][x] == '#'){
			res++;
		}
		x = (x + mx) % input[0].size();
		y += my;
	}
	return res;
}

int first()
{
	return encounter(3,1);
}

ll second()
{
	return (ll)encounter(1,1) * encounter(3,1) * encounter(5,1) * encounter(7,1) * encounter(1,2);
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
