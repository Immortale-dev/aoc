#ifndef BITS_H
#define BITS_H

#include <bits/stdc++.h>

using namespace std;

#include "./bitsreader.cpp"

typedef long long int ll;

namespace BITS {
	
	struct BIT{
		int version;
		int type;
		vector<shared_ptr<BIT>> childs;
		ll val;
	};
	
	namespace details {
		shared_ptr<BIT>parse_bit(BITSReader& reader) {
			shared_ptr<BIT> bit(new BIT());
			bit->version = reader.next(3);
			bit->type = reader.next(3);
			if(bit->type == 4) { // literal
				ll num = 0;
				while(true) {
					int a = reader.next(5);
					int d = a & 15;
					num <<= 4;
					num |= d;
					if( !(a & (1 << 4)) ) break;
				}
				bit->val = num;
			} else { // operator
				if(reader.next()) { // packets count
					int packets_count = reader.next(11);
					while(packets_count--){
						bit->childs.push_back(parse_bit(reader));
					}
				} else { // bits count
					int bits_count = reader.next(15);
					int start_index = reader.index();
					do {
						bit->childs.push_back(parse_bit(reader));
					} while(reader.index()-start_index < bits_count);
				}
			}
			return bit;
		}
	}
	
	shared_ptr<BIT> fromString(string s){
		BITSReader reader(s);
		
		return details::parse_bit(reader);
	}
}

#endif // BITS_H
