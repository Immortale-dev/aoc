#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;


class Program{
	public:
		Program(vector<string> input){
			for(auto& it : input){
				insts.push_back(parseString(it));
			}
		}
		bool is_corrupted(){
			int ind = 0;
			accumulate = 0;
			unordered_set<int> executed;
			while(true){
				if(ind == insts.size()) return false;
				if(ind < 0 || ind > insts.size()) return true;
				if(executed.count(ind)){
					return true;
				}
				executed.insert(ind);
				Inst ins = insts[ind];
				switch(ins.type){
					case Type::ACC:
						ind++;
						accumulate += ins.offset;
						break;
					case Type::JMP:
						ind+=ins.offset;
						break;
					default:
						ind++;
				}
			}
		}
		void fix_corrupt(){
			for(int i=0;i<insts.size();i++){
				if(insts[i].type == Type::JMP){
					insts[i].type = Type::NOP;
					if(!is_corrupted()) return;
					insts[i].type = Type::JMP;
				} else if(insts[i].type == Type::NOP) {
					insts[i].type = Type::JMP;
					if(!is_corrupted()) return;
					insts[i].type = Type::NOP;
				}
			}
		}
		
		int get_acc(){ return accumulate; }
		
	private:
		enum class Type{ ACC, JMP, NOP };
		struct Inst{
			Inst(Type type, int offset) : type(type), offset(offset) {}; 
			Type type;
			int offset;
		};
		
		Inst parseString(string s){
			stringstream ss;
			ss << s;
			string command;
			int offset;
			ss >> command >> offset;
			Type type;
			if(command == "acc"){
				type = Type::ACC;
			} else if(command == "jmp"){
				type = Type::JMP;
			} else {
				type = Type::NOP;
			}
			return Inst(type, offset);
		}
		
		vector<Inst> insts;
		int accumulate = 0;
};

vector<string> input;
Program* p;

void prepare()
{
	string s;
	while(getline(cin, s)){
		input.push_back(s);
	}
	p = new Program(input);
}

int first()
{
	p->is_corrupted();
	return p->get_acc();
}

int second()
{
	p->fix_corrupt();
	return p->get_acc();
}

int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
