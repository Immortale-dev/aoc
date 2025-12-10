#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Point) {
	PARSE_SETUP;
	PARSE(double) x = SINGLE();
	SKIP(char) = SINGLE(',');
	PARSE(double) y = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Point) points = UNTIL_END();
};

Input input(std::cin);

auto calc_area(Point& pt1, Point& pt2) {
	return (abs(pt2.x() - pt1.x()) + 1) * (abs(pt2.y() - pt1.y()) + 1);
}

ll first() {
	ll best_area = 0;
	for (int i=0;i<input.points.size();i++) {
		for (int j=i+1;j<input.points.size();j++) {
			auto pt1 = input.points[i];
			auto pt2 = input.points[j];
			ll area = calc_area(pt1, pt2);
			best_area = max(best_area, area);
		}
	}
	return best_area;
}

struct Pt {
	double x;
	double y;
};

bool lines_intersect(Pt sl1, Pt el1, Pt sl2, Pt el2) {
	// check if paralel
	if (sl1.x == el1.x && sl2.x == el2.x) return false;
	if (sl1.y == el1.y && sl2.y == el2.y) return false;

	if (sl1.x != el1.x) { swap(sl1, sl2); swap(el1, el2); }
	if (sl1.y > el1.y) swap(sl1, el1);
	if (sl2.x > el2.x) swap(sl2, el2);

	assert(sl1.x == el1.x);
	assert(sl2.y == el2.y);

	if (sl2.y < sl1.y || sl2.y > el1.y) return false;
	if (sl1.x < sl2.x || sl1.x > el2.x) return false;
	return true;
}

int count_lines_intersect(Pt p1, Pt p2) {
	int res = 0;
	for (int i=0;i<input.points.size();i++) {
		auto &q1 = input.points[i];
		auto &q2 = input.points[(i+1)%input.points.size()];
		res += lines_intersect(p1, p2, {q1.x(), q1.y()}, {q2.x(), q2.y()});
	}
	return res;
}

ll second() {
	ll best_area = 0;
	for (int i=0;i<input.points.size();i++) {
		for (int j=i+1;j<input.points.size();j++) {
			auto pt1 = input.points[i];
			auto pt2 = input.points[j];
			if (j-i == 1) {
				ll area = calc_area(pt1, pt2);
				best_area = max(best_area, area);
				continue;
			}
			double minx = min(pt1.x(), pt2.x());
			double maxx = max(pt1.x(), pt2.x());
			double miny = min(pt1.y(), pt2.y());
			double maxy = max(pt1.y(), pt2.y());

			if (minx != maxx && miny != maxy) {
				// Check if no lines intersect the innner rectangle
				if (count_lines_intersect({minx+0.5, miny+0.5}, {minx+0.5, maxy-0.5})) continue;
				if (count_lines_intersect({maxx-0.5, miny+0.5}, {maxx-0.5, maxy-0.5})) continue;
				if (count_lines_intersect({minx+0.5, miny+0.5}, {maxx-0.5, miny+0.5})) continue;
				if (count_lines_intersect({minx+0.5, maxy-0.5}, {maxx-0.5, maxy-0.5})) continue;
			}

			double midx = floor((maxx+minx)/2.0);
			double midy = floor((maxy+miny)/2.0);
			if ((count_lines_intersect({0.0, midy}, {midx, midy}) % 2) == 0) continue;
			if ((count_lines_intersect({midx, midy}, {1000000.0, midy}) % 2) == 0) continue;
			if ((count_lines_intersect({midx, 0.0}, {midx, midy}) % 2) == 0) continue;
			if ((count_lines_intersect({midx, midy}, {midx, 1000000.0}) % 2) == 0) continue;

			ll area = calc_area(pt1, pt2);
			best_area = max(best_area, area);
		}
	}
	return best_area;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
