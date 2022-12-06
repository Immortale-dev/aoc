#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

string buffer;

void prepare() {
	getline(cin, buffer);
}

ll find_first_n_distinct_chars(string buffer, int n) {
	unordered_map<char, int> chars;
	for(size_t i=0;i<buffer.size();i++) {
		if (i >= n) {
			chars[buffer[i-n]]--;
			if (!chars[buffer[i-n]]) {
				chars.erase(buffer[i-n]);
			}
		}
		chars[buffer[i]]++;
		if (chars.size() == n) {
			return i+1;
		}
	}
	throw logic_error("No marker found");
}

ll first() {
	return find_first_n_distinct_chars(buffer, 4);
}

ll second() {
	return find_first_n_distinct_chars(buffer, 14);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
