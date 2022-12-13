#include <vector>
#include <string>
#include <stack>
#include <stdexcept>

class Signal {
	public:
		Signal();
		Signal(int val);
		static Signal* parse(std::string s);
		bool is_final();
		int get_value();
		std::vector<Signal*>& get_list();
		bool operator < (Signal& signal);
		
	private:
		std::vector<Signal*> list;
		int value;
		bool final_value = false;
};

Signal::Signal() {}

Signal::Signal(int val) {
	value = val;
	final_value = true;
}

Signal* Signal::parse(std::string s) {
	std::stack<Signal*> cst;
	cst.push(new Signal());
	for(size_t i=0;i<s.size();i++) {
		if (s[i] == '[') {
			auto* sig = new Signal();
			cst.top()->get_list().push_back(sig);
			cst.push(sig);
		}
		if (s[i] == ']') {
			cst.pop();
		}
		if (s[i] >= '0' && s[i] <= '9') {
			std::string sv;
			while(s[i] >= '0' && s[i] <= '9') {
				sv.push_back(s[i++]);
			}
			cst.top()->get_list().push_back(new Signal(stoi(sv)));
			--i;
		}
		if (s[i] == ',') continue;
	}
	return cst.top()->get_list()[0];
}

bool Signal::is_final() {
	return final_value;
}

int Signal::get_value() {
	return value;
}

std::vector<Signal*>& Signal::get_list() {
	return list;
}

bool Signal::operator < (Signal& signal) {
	if (this->is_final() && signal.is_final()) {
		return this->get_value() < signal.get_value();
	}
	if (!this->is_final() && !signal.is_final()) {
		for (size_t i=0;i<std::min(this->get_list().size(), signal.get_list().size());++i) {
			if (*(this->get_list()[i]) < *(signal.get_list()[i])) return true;
			if (*(signal.get_list()[i]) < *(this->get_list()[i])) return false;
		}
		return this->get_list().size() < signal.get_list().size();
	}
	if (this->is_final()) {
		if (signal.get_list().size() == 0) return false;
		if ( *(signal.get_list()[0]) < (*this) ) return false;
		if ( (*this) < *(signal.get_list()[0]) || signal.get_list().size() > 1 ) return true;
		return false;
	}
	if (signal.is_final()) {
		if (this->get_list().size() == 0) return true;
		if (*(this->get_list()[0]) < signal) return true;
		if ( signal < *(this->get_list()[0]) || this->get_list().size() > 1) return false;
		return false;
	}
	throw std::logic_error("Something went wrong");
}
