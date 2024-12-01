#include <bits/stdc++.h>

using namespace std;

#include "../helpers/parser.h"

typedef long long int ll;

//=======================================//

DECLARE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	
}

ll first() {
	return 0;
}

ll second() {
	return 0;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
