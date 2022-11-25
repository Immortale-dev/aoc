#include <bits/stdc++.h>

typedef long long int ll;

using namespace std;

ll card, door;
ll divider = 20201227;
ll subject = 7;

void prepare()
{
	cin >> card >> door;
}

ll first()
{
	ll val = 1;
	int i=0;
	while(++i){
		val = val*subject%divider;
		if(val == card) break;
	}
	
	val = 1;
	for(int j=0;j<i;j++){
		val = val*door%divider;
	}
	
	return val;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	return 0;
}
