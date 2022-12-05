#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "../helpers/terminal.cpp"

typedef long long int ll;

//=======================================//

struct Command {
	int count;
	int from;
	int to;
};

vector<deque<char>> stacks;
vector<Command> commands;

void prepare() {
	string s;
	int stack_count;
	while(getline(cin, s)) {
		if (s[1] == '1') break;
		stack_count = (s.size()+1)/4;
		if (!stacks.size()) {
			stacks.resize(stack_count);
		}
		for(int i=0;i<stack_count;i++) {
			char c = s[i*4+1];
			if (c == ' ') continue;
			stacks[i].push_back(c);
		}
	}
	for(auto& stack : stacks) {
		//reverse(stack.begin(), stack.end());
	}
	getline(cin, s); // empty line
	while(getline(cin, s)) {
		auto command = split_line(s, " ");
		commands.push_back({stoi(command[1]), stoi(command[3])-1, stoi(command[5])-1});
	}
}

int print_stacks(vector<deque<char>> stacks) {
	cout << "\n";
	int max_stack = 0;
	for(int i=0;i<stacks.size();i++) {
		max_stack = max(max_stack, (int)stacks[i].size());
	}
	for(int i=max_stack-1;i>=0;i--) {
		for(auto stack : stacks) {
			char c = ' ';
			if (stack.size() > i) {
				c = stack[stack.size()-i-1];
				cout << "[" << c << "] ";
			} else {
				cout << "    ";
			}
		}
		cout << "\n";
	}
	for(int i=0;i<stacks.size();i++) {
		cout << " " << i << "  ";
	}
	cout << endl;
	return max_stack+1;
}

string first(vector<deque<char>> stacks) {
	for(auto& command : commands) {
		for(int i=0;i<command.count;i++) {
			stacks[command.to].push_front(stacks[command.from].front());
			stacks[command.from].pop_front();
		}
	}
	
	#ifdef PRINT
	print_stacks(stacks);
	#endif
	
	string result;
	for(auto& stack : stacks) {
		result.push_back(stack[0]);
	}
	return result;
}

string second(vector<deque<char>> stacks) {
	for(auto& command : commands) {
		for(int i=command.count-1;i>=0;i--) {
			stacks[command.to].push_front(stacks[command.from][i]);
		}
		for(int i=command.count-1;i>=0;i--) {
			stacks[command.from].pop_front();
		}
	}
	
	#ifdef PRINT
	print_stacks(stacks);
	#endif
	
	string result;
	for(auto& stack : stacks) {
		result.push_back(stack[0]);
	}
	return result;
}

int main() {
	prepare();
	cout << "First: " << first(stacks) << endl;
	cout << "Second: " << second(stacks) << endl;
	return 0;
}
