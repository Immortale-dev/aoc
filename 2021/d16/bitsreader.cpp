#ifndef BITS_READER_H
#define BITS_READER_H

typedef long long int ll;

class BITSReader {
	public:
		BITSReader(string s) : bits(s.size()*4, false) {
			for(int j=0;j<(int)s.size();j++) {
				char c = s[j];
				int a;
				if(c > '9') {
					a = c-'A'+10;
				} else {
					a = c-'0';
				}
				
				for(int i=3;i>=0;i--){
					bits[j*4+(3-i)] = (a & (1<<i));
				}
			}
		}
		
		bool next() {
			return bits[ind++];
		}
		
		ll next(int count) {
			ll num = 0;
			while(count--){
				num <<= 1;
				num |= next();
			}
			return num;
		}
		
		size_t size() {
			return bits.size();
		}
		
		bool eof() {
			return ind == bits.size();
		}
		
		void reset() {
			ind = 0;
		}
		
		int index() {
			return ind;
		}
	private:
		int ind = 0;
		vector<bool> bits;
};

#endif // BITS_READER_H
