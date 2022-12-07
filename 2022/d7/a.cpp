#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct CommandResult {
	string name;
	ll size;
	bool isDir = false;
};

struct DirFile : public CommandResult {
	map<string, DirFile*> sub;
};

struct Command {
	string command;
	string arg;
	vector<CommandResult> result;
};

vector<Command> commands;

DirFile* FS;
void fulfill() {
	FS = new DirFile{"", 0, true};
	FS->sub["/"] = new DirFile{"/", 0, true};
	auto cur = FS;
	for(auto &command : commands) {
		if (command.command == "cd") {
			if (!cur->sub.count(command.arg) || !cur->sub[command.arg]->isDir) throw logic_error("No dir found: " + command.arg);
			DirFile* par = cur;
			cur = cur->sub[command.arg];
			if (command.arg != "..") cur->sub[".."] = par;
		} else {
			for(auto& res : command.result) {
				cur->sub[res.name] = new DirFile{res.name, res.size, res.isDir};
			}
		}
	}
}

void calc_dir_size(DirFile* df) {
	if (!df->isDir) return;
	ll size = 0;
	for(auto sdf : df->sub) {
		if (sdf.first == "..") continue;
		calc_dir_size(sdf.second);
		size += sdf.second->size;
	}
	df->size = size;
}

void prepare() {
	string s;
	Command last_command;
	while(getline(cin, s)){
		if (s[0] == '$') {
			if (last_command.command != "") {
				commands.push_back(last_command);
			}
			auto comm = split_line(s, " ");
			last_command = {comm[1], comm.size() > 2 ? comm[2] : ""};
		} else {
			auto dfarr = split_line(s, " ");
			if (dfarr[0] == "dir") {
				last_command.result.push_back({dfarr[1], 0, true});
			} else {
				last_command.result.push_back({dfarr[1], stoll(dfarr[0]), false});
			}
		}
	}
	commands.push_back(last_command);
	fulfill();
}

ll first() {
	calc_dir_size(FS->sub["/"]);

	stack<DirFile*> process;
	process.push(FS->sub["/"]);
	ll result = 0;
	while(!process.empty()) {
		DirFile* df = process.top();
		process.pop();
		if (df->size <= 100000) {
			result += df->size;
		}
		for(auto sdf : df->sub) {
			if (sdf.first != ".." && sdf.second->isDir) {
				process.push(sdf.second);
			}
		}
	}
	return result;
}

ll second() {
	ll atLeast = 30000000 - (70000000 - FS->sub["/"]->size);
	ll minSize = 999999999;
	stack<DirFile*> process;
	process.push(FS->sub["/"]);
	while(!process.empty()) {
		DirFile* df = process.top();
		process.pop();
		if (df->size >= atLeast && df->size < minSize) {
			minSize = df->size;
		}
		for(auto sdf : df->sub) {
			if (sdf.first != ".." && sdf.second->isDir) {
				process.push(sdf.second);
			}
		}
	}
	return minSize;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
