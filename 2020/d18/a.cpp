#include <bits/stdc++.h>

using namespace std;

vector<string> exprs;

typedef unsigned long long int ll;

void prepare()
{
	string s;
	while(getline(cin,s)){
		exprs.push_back(s);
	}
}

bool is_num(char c)
{
	return c >= '0' && c <= '9';
}

bool is_op(char c)
{
	return c=='+' || c=='*';
}

ll make_op(ll left, char op, ll right)
{
	return op == '+' ? left + right : left * right;
}

ll req_expr(string& expr, int& ind)
{
	bool left = 0;
	bool sign = 0;
	char op;
	ll left_num;
	while(ind < expr.size()){
		char c = expr[ind];
		if(c == ' '){ ind++; continue; }
		if(c == ')'){ break; }
		if(c == '('){
			ind++;
			ll num = req_expr(expr, ind);
			if(!left){
				left_num = num;
				left = true;
			} else {
				left_num = make_op(left_num, op, num);
			}
		} else if(is_num(c)){
			ll num = c-'0';
			if(!left){
				left_num = num;
				left = true;
			} else{
				left_num = make_op(left_num, op, num);
			}
		} else if(is_op(c)){
			op = c;
			sign = 1;
		}
		ind++;
	}
	return left_num;
}

ll calc_expr(string expr)
{
	int ind=0;
	return req_expr(expr, ind);
}

///////////////////////////////////////////////

ll get_num_2(string& str, int& ind)
{
	ll n = 0;
	while(ind < str[ind] && str[ind] == ' ')
		ind++;
	while(ind < str.size()){
		if(!is_num(str[ind])){
			break;
		}
		n = n * 10 + (str[ind]-'0');
		ind++;
	}
	return n;
}

char get_op_2(string& str, int& ind)
{
	char op = '.';
	while(ind < str[ind] && str[ind] == ' ')
		ind++;
	if(ind < str[ind]){
		op = str[ind];
		ind++;
	}
	return op;
}

ll calc_line_2(string& str, int& ind)
{
	bool left = false;
	ll num;
	while(ind < str.size()){
		if(!left){
			num = get_num_2(str, ind);
			left = 1;
		}
		char op = get_op_2(str, ind);
		if(op == '.'){
			break;
		} else if(op == '+') {
			num = num + get_num_2(str, ind);
		} else {
			num = num * calc_line_2(str, ind);
		}
	}
	return num;
}

ll req_expr_2(string& expr, int& ind)
{
	string nstr = "";
	int i;
	for(i=ind;i<=expr.size();i++){
		char c = expr[i];
		if(c == '('){
			i++;
			ll num = req_expr_2(expr, i);
			i--;
			nstr += to_string(num);
		} else if(c == ')') {
			i++;
			break;
		} else {
			nstr.push_back(c);
		}
	}
	
	ind = i;
	int ii = 0;
	return calc_line_2(nstr, ii);
}

ll calc_expr_2(string expr)
{
	int ind = 0;
	return req_expr_2(expr, ind);
}

ll first()
{
	ll res = 0;
	int i = 0;
	for(auto& it : exprs){
		res += calc_expr(it);
		i++;
	}
	return res;
}

ll second()
{
	ll res = 0;
	int i = 0;
	for(auto& it : exprs){
		res += calc_expr_2(it);
		i++;
	}
	return res;
}


int main()
{
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
