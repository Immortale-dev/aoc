#include <iostream>
#include <string>

void put_command(std::string command) {
	#ifdef linux
	std::cout << command;
	#endif
}

void save_cursor() {
	put_command("\033[s");
}

void restore_cursor() {
	put_command("\033[u");
}

void erase_to_end() {
	put_command("\033[K");
}

void clear_screen() {
	put_command("\033[2J");
}

void move_cursor_backward(int n=1) {
	if (!n) return;
	put_command("\033["+std::to_string(n)+"D");
}

void move_cursor_forward(int n=1) {
	if (!n) return;
	put_command("\033["+std::to_string(n)+"C");
}

void move_cursor_down(int n=1) {
	if (!n) return;
	put_command("\033["+std::to_string(n)+"B");
}

void move_cursor_up(int n=1) {
	if (!n) return;
	put_command("\033["+std::to_string(n)+"A");
}

void move_cursor_to(int n, int m) {
	put_command("\033["+std::to_string(n)+";"+std::to_string(m)+"H");
}

void remove_lines(int n) {
	if (!n) return;
	move_cursor_backward(999);
	while(n--){
		erase_to_end();
		move_cursor_up();
	}
}
