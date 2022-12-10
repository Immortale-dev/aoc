#include <deque>
#include <queue>

class Device {
	public:
		struct Command {
			string command;
			vector<int> args = {};
		};
		
		void input(Command com);
		void tick();
		int get_x();
		bool empty();
		
	private:
		void addX(int x);
		void noop();
		void addToQueue(Command com);
		
		std::queue<Command> commands;
		int x = 1;
};

void Device::input(Command com) {
	if (com.command == "addx") {
		addToQueue({"noop"});
	}
	addToQueue(com);
}

void Device::tick() {
	Command com = commands.front();
	commands.pop();
	if (com.command == "addx") {
		addX(com.args[0]);
	} else if (com.command == "noop") {
		noop();
	}
}

int Device::get_x() {
	return x;
}

bool Device::empty() {
	return commands.empty();
}

///// PRIVATE MEMBERS

void Device::addX(int x) {
	this->x += x;
}

void Device::noop() {
	//nothing to do here :)
}

void Device::addToQueue(Command com) {
	commands.push(com);
}
