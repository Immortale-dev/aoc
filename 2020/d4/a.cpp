#include <bits/stdc++.h>
using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<unordered_map<string,string>> input;

void prepare()
{
	string s;
	unordered_map<string,string> passport;
	while(getline(cin, s)){
		if(s == ""){
			input.push_back(passport);
			passport = unordered_map<string,string>();
			continue;
		}
		auto arr = split_line(s," ");
		for(auto it : arr){
			auto p = split_line(it, ":");
			passport[p[0]] = p[1];
		}
	}
	input.push_back(passport);
}

bool is_number(string s)
{
	for(int i=0;i<s.size();i++){
		if(s[i] < '0' || s[i] > '9') return false;
	}
	return true;
}

bool is_height(string s)
{
	if(s.size() < 3) return false;
	string dem = s.substr(s.size()-2);
	string val = s.substr(0, s.size()-2);
	if(dem != "cm" && dem != "in") return false;
	if(dem == "cm" && (stoi(val) < 150 || stoi(val) > 193)) return false;
	if(dem == "in" && (stoi(val) < 59 || stoi(val) > 76)) return false;
	return true;
}

bool is_hair_color(string s)
{
	if(s.size() != 7) return false;
	if(s[0] != '#') return false;
	for(int i=1;i<s.size();i++){
		if( (s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'f') ) return false;
	}
	return true;
}

bool is_eye_color(string s)
{
	if(s != "amb" && s != "blu" && s != "brn" && s != "gry" && s != "grn" && s != "hzl" && s != "oth") return false;
	return true;
}

bool is_pid(string s)
{
	if(s.size() != 9) return false;
	return is_number(s);
}

int first()
{
	vector<string> required = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
	int res = 0;
	for(auto &it : input){
		bool good = true;
		for(auto &req : required){
			if(!it.count(req)){
				good = false;
				break;
			}
		}
		if(good){
			res++;
		}
	}
	return res;
}

int second()
{
	vector<string> required = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
	int res = 0;
	for(auto &it : input){
		bool good = true;
		for(auto &req : required){
			if(!it.count(req)){
				good = false;
				break;
			}
		}
		if(good){
			good &= (is_number(it["byr"]) && stoi(it["byr"]) >= 1920 && stoi(it["byr"]) <= 2002);
			good &= (is_number(it["iyr"]) && stoi(it["iyr"]) >= 2010 && stoi(it["iyr"]) <= 2020);
			good &= (is_number(it["eyr"]) && stoi(it["eyr"]) >= 2020 && stoi(it["eyr"]) <= 2030);
			good &= is_height(it["hgt"]);
			good &= is_hair_color(it["hcl"]);
			good &= is_eye_color(it["ecl"]);
			good &= is_pid(it["pid"]);
		}
		if(good) res++;
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
