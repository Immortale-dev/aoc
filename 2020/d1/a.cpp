#include <bits/stdc++.h>

using namespace std;

const int COUNT = 200;

int arr[2500];

void prepare()
{
	for(int i=0;i<2500;i++) arr[i] = 0;
	for(int i=0;i<COUNT;i++){
		int a;
		cin >> a;
		++arr[a];
	}
}

int first()
{
	for(int i=0;i<2500;i++){
		if(arr[i] && arr[2020-i]){
			return i*(2020-i);
		}
	}
	return -1;
}

int second()
{
	for(int i=0;i<2500;i++){
		for(int j=i+1;j<2500;j++){
			if(arr[i] && arr[j] && (2020-i-j) > 0 && arr[2020-i-j]){
				return i*j*(2020-i-j);
			}
		}
	}
	return -1;
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
