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

std::string replace_all(
    std::string s,
    std::string toReplace,
    std::string replaceWith
) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
    return s;
}
