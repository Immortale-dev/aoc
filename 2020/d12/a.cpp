#include <bits/stdc++.h>

using namespace std;

struct command{
	char c;
	int v;
};

vector<command> input;

void prepare()
{
	string s;
	while(getline(cin,s)){
		char c = s[0];
		int v = stoi(s.substr(1));
		input.push_back({c,v});
	}
}

int first()
{
	int x=0,y=0;
	unordered_map<char, std::function<void(int)>> dirs;
	vector<char> comp = {'E','S','W','N'};
	int course_n = 0;
	char course = 'E';
	
	dirs['N'] = [&x,&y](int a){y-=a;};
	dirs['S'] = [&x,&y](int a){y+=a;};
	dirs['W'] = [&x,&y](int a){x-=a;};
	dirs['E'] = [&x,&y](int a){x+=a;};
	dirs['L'] = [&comp, &course_n, &course](int a){course_n=(course_n-a/90+4)%4; course=comp[course_n];};
	dirs['R'] = [&comp, &course_n, &course](int a){course_n=(course_n+a/90+4)%4; course=comp[course_n];};
	dirs['F'] = [&course,&dirs](int a){dirs[course](a);};
	
	for(auto& it : input){
		dirs[it.c](it.v);
	}
	
	return abs(x)+abs(y);
}

int second()
{
	int x=0,y=0;
	int px=10, py=-1;
	unordered_map<char, std::function<void(int)>> dirs;
	
	dirs['N'] = [&px,&py](int a){py-=a;};
	dirs['S'] = [&px,&py](int a){py+=a;};
	dirs['W'] = [&px,&py](int a){px-=a;};
	dirs['E'] = [&px,&py](int a){px+=a;};
	dirs['R'] = [&px,&py](int a){a/=90;while(a--){int pt=-py;py=px;px=pt;}};
	dirs['L'] = [&px,&py](int a){a/=90;while(a--){int pt=-px;px=py;py=pt;}};
	dirs['F'] = [&px,&py,&x,&y](int a){x+=a*px;y+=a*py;};
	
	for(auto& it : input){
		dirs[it.c](it.v);
	}
	
	return abs(x)+abs(y);
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
