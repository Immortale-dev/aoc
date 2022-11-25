#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

int rp1,rp2;

void prepare() {
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	auto arr1 = split_line(s1, " ");
	auto arr2 = split_line(s2, " ");
	rp1 = stoi(arr1[arr1.size()-1])-1;
	rp2 = stoi(arr2[arr2.size()-1])-1;
}

ll first() {
	int p1=rp1,p2=rp2;
	int score1=0, score2=0;
	int rolls=0;
	int round = 0;
	
	while(score1 < 1000 && score2 < 1000){
		int moves = 0;
		for(int i=0;i<3;i++) moves += ++rolls;
		
		if((round%2) == 0) {
			p1 = (p1+moves)%10;
			score1 += p1+1;
		} else {
			p2 = (p2+moves)%10;
			score2 += p2+1;
		}
		
		++round;
	}
	
	return min(score1, score2)*rolls;
}

struct qstep {
	vector<vector<ll>> scores = vector<vector<ll>>(31, vector<ll>(10, 0));
};

void calc_dp(vector<qstep>& dp){
	// rounds
	for(int i=0;i<dp.size()-1;i++){
		int round = i;
		// scores
		for(int j=0;j<dp[round].scores.size();j++){
			int score = j;
			if(score >= 21) continue; // the game is finished
			// positions
			for(int k=0;k<dp[round].scores[score].size();k++){
				int pos = k;
				// rolls
				for(int r1=1;r1<=3;r1++){
					for(int r2=1;r2<=3;r2++){
						for(int r3=1;r3<=3;r3++){
							int sum = r1+r2+r3;
							int newpos = (pos+sum)%10;
							int newscore = score+newpos+1;
							
							// magic
							dp[round+1].scores[newscore][newpos] += dp[round].scores[score][pos];
						}
					}
				}
			}
		}
	}
}

ll second() {
	const int rounds_count = 20;
	const int scores_count = 31;
	const int positions_count = 10;
	
	vector<qstep> dp1(rounds_count);
	vector<qstep> dp2(rounds_count);
	
	dp1[0].scores[0][rp1] = 1;
	dp2[0].scores[0][rp2] = 1;
	
	calc_dp(dp1);
	calc_dp(dp2);
	
	ll wins1 = 0;
	ll wins2 = 0;
	
	for(int i=1;i<rounds_count;i++){
		ll w1 = 0;
		ll l1 = 0;
		ll w2 = 0;
		ll l2 = 0;
		for(int j=21;j<scores_count;j++){
			for(int k=0;k<positions_count;k++){
				w1 += dp1[i].scores[j][k];
				w2 += dp2[i].scores[j][k];
			}
		}
		for(int j=0;j<21;j++){
			for(int k=0;k<positions_count;k++){
				l1 += dp1[i].scores[j][k];
				l2 += dp2[i-1].scores[j][k];
			}
		}
		wins1 += w1*l2;
		wins2 += w2*l1;
	}
	
	return max(wins1, wins2);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
