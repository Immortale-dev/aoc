#ifndef SCANNER_H
#define SCANNER_H

struct Beacon {
	int x,y,z;
};

class Scanner {
	public:
		void add_beacon(Beacon b) {
			beacons.push_back(b);
		}
		vector<Beacon>& get_beacons() {
			return beacons;
		}
		void rotateX(int num) {
			for(auto& it : beacons) {
				while(num--){
					rotatePt(it.y, it.z);
				}
			}
		}
		void rotateY(int num) {
			for(auto& it : beacons) {
				while(num--){
					rotatePt(it.x, it.z);
				}
			}
		}
		void rotateZ(int num) {
			for(auto& it : beacons) {
				while(num--){
					rotatePt(it.x, it.y);
				}
			}
		}
	
	private:
		void rotatePt(int& a, int& b){
			swap(a,b);
			a = -a;
		}
		vector<Beacon> beacons;
};

#endif
