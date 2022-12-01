vector<string> split_line(string line, string delim)
{
	vector<string> res;
	int pos = 0;
	while(true){
		int newpos = line.find(delim, pos);
		if(newpos < 0){
			res.push_back(line.substr(pos));
			break;
		}
		res.push_back(line.substr(pos,newpos-pos));
		pos = newpos+delim.size();
	}
	return res;
}

string join_line(vector<string> arr, string delim)
{
	string res = "";
	for(int i=0;i<arr.size();i++){
		if(i) res += delim;
		res += arr[i];
	}
	return res;
}
