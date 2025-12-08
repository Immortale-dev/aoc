#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Box) {
	PARSE_SETUP;
	PARSE(int) x = SINGLE();
	SKIP(char) = SINGLE(',');
	PARSE(int) y = SINGLE();
	SKIP(char) = SINGLE(',');
	PARSE(int) z = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Box) boxes = UNTIL_END();
};

Input input(std::cin);

struct Connection {
	double distance;
	int from;
	int to;
};

int union_get(vector<int>& un, int a) {
	if (un[a] == a) return a;
	return un[a] = union_get(un, un[a]);
}

void union_add(vector<int>& un, int a, int b) {
	un[union_get(un, b)] = union_get(un, a);
}

ll first() {
	vector<Connection> connections;
	for (int i=0;i<input.boxes.size();i++) {
		for (int j=i+1;j<input.boxes.size();j++) {
			auto& b1 = input.boxes[i];
			auto& b2 = input.boxes[j];
			double distance = pow(pow(b2.x() - b1.x(), 2.0) + pow(b2.y() - b1.y(), 2.0) + pow(b2.z() - b1.z(), 2.0), 0.5);
			connections.push_back({distance, i, j});
		}
	}
	sort(connections.begin(), connections.end(), [](auto &left, auto &right){ return left.distance < right.distance; });

	vector<int> un(input.boxes.size());
	for (int i=0;i<un.size();i++) {
		un[i] = i;
	}
	for (int i=0;i<1000;i++) {
		auto &conn = connections[i];
		union_add(un, conn.from, conn.to);
	}

	vector<int> clusters(input.boxes.size(), 0);
	for (int i=0;i<input.boxes.size();i++) {
		clusters[union_get(un, i)]++;
	}
	vector<int> cluster_sizes;
	for (int i=0;i<input.boxes.size();i++) {
		cluster_sizes.push_back(clusters[i]);
	}
	sort(cluster_sizes.begin(), cluster_sizes.end(), greater<int>());

	return 1LL * cluster_sizes[0] * cluster_sizes[1] * cluster_sizes[2];
}

ll second() {
	vector<Connection> connections;
	for (int i=0;i<input.boxes.size();i++) {
		for (int j=i+1;j<input.boxes.size();j++) {
			auto& b1 = input.boxes[i];
			auto& b2 = input.boxes[j];
			double distance = pow(pow(b2.x() - b1.x(), 2.0) + pow(b2.y() - b1.y(), 2.0) + pow(b2.z() - b1.z(), 2.0), 0.5);
			connections.push_back({distance, i, j});
		}
	}
	sort(connections.begin(), connections.end(), [](auto &left, auto &right){ return left.distance < right.distance; });

	int connected = 0;
	vector<int> un(input.boxes.size());
	for (int i=0;i<un.size();i++) {
		un[i] = i;
	}
	for (int i=0;i<connections.size();i++) {
		auto &conn = connections[i];
		if (union_get(un, conn.from) != union_get(un, conn.to)) {
			union_add(un, conn.from, conn.to);
			connected++;
			if (connected == input.boxes.size()-1) return 1LL * input.boxes[conn.from].x() * input.boxes[conn.to].x();
		}
	}
	assert(false);
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
