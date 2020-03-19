#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include "elements.h"
using namespace std;
ifstream fin;
ofstream fout;
vector<Line *> lines;
vector<Circle> circles;
set<Point> points;

void lineIntersectLine(Line &l1, Line &l2) {
	if (l1.b * l2.a != l1.a * l2.b) { //不平行才会相交
		double x = (double)(l2.c * l1.b - l1.c * l2.b) / (double)(l1.a * l2.b - l1.b * l2.a);
		double y = (double)(l2.c * l1.a - l1.c * l2.a) / (double)(l1.b * l2.a - l1.a * l2.b);
		if (l1.isInLine(x, y) && l2.isInLine(x, y)) {
			Point p(x, y);
			points.insert(p);
		}
	}
}

void lineIntersectCircle(Line &l, Circle cir) { 
	if (l.a == 0) { //水平线
		double y = -(double)l.c / (double)l.b; //将y值代入圆方程
		long long a = l.b * l.b;
		long long b = -2 * l.b * l.b * cir.x;
		long long c = l.c * l.c + 2 * l.b * l.c * cir.y + (cir.x * cir.x + cir.y * cir.y - cir.r * cir.r) * l.b * l.b;
		long long delta = b * b - 4 * a * c;
		if (delta > 0) {
			double x1 = (-b + sqrt(delta)) / (2l * a);
			double x2 = (-b - sqrt(delta)) / (2l * a);
			if (l.isInLine(x1, y)) {
				Point p1(x1, y);
				points.insert(p1);
			}
			if (l.isInLine(x2, y)) {
				Point p2(x2, y);
				points.insert(p2);
			}
		}
		if (delta == 0) {
			double x = (-b + sqrt(delta)) / (2l * a);
			if (l.isInLine(x, y)) {
				Point p(x, y);
				points.insert(p);
			}	
		}
	}
	else {//直线Ax+By+C=0中A不为零，可以将x用y表示代入圆方程。
		long long a = l.a * l.a + l.b * l.b;
		long long b = 2 * (l.b * l.c + l.a * l.b * cir.x - l.a * l.a * cir.y);
		long long c = l.c * l.c + 2 * l.a * l.c * cir.x + (cir.x * cir.x + cir.y * cir.y - cir.r * cir.r) * l.a * l.a;
		long long delta = b * b - 4 * a * c;
		if (delta > 0) {
			double y1 = (-b + sqrt(delta)) / (2l * a);
			double y2 = (-b - sqrt(delta)) / (2l * a);
			double x1 = (-l.b * y1 - l.c) / l.a;
			double x2 = (-l.b * y2 - l.c) / l.a;
			if (l.isInLine(x1, y1)) {
				Point p1(x1, y1);
				points.insert(p1);
			}
			if (l.isInLine(x2, y2)) {
				Point p2(x2, y2);
				points.insert(p2);
			}
		}
		if (delta == 0) {
			double y = (-b + sqrt(delta)) / (2l * a);
			double x = (-l.b * y - l.c) / l.a;
			if (l.isInLine(x, y)) {
				Point p(x, y);
				points.insert(p);
			}	
		}
	}
}

void circleIntersectCircle(Circle c1, Circle c2) {
	if ((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y) <= (c1.r + c2.r) * (c1.r + c2.r)//外切外交
		|| (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y) >= (c1.r - c2.r) * (c1.r - c2.r)) {//内切内交
		long long a = 2 * (c1.x - c2.x);
		long long b = 2 * (c1.y - c2.y);
		long long c = c2.x * c2.x - c1.x * c1.x + c2.y * c2.y - c1.y * c1.y + c1.r * c1.r - c2.r * c2.r;
		Line l(a, b, c);//两圆方程相减得到过交点的直线方程，转为直线与圆交点问题
		lineIntersectCircle(l, c1);
	}
}

void addLine(char type, long long x1, long long y1, long long x2, long long y2) {
	if (type == 'L') {
		Line *l = new Line(x1, y1, x2, y2);
		lines.push_back(l);
	}
	if (type == 'R') {
		RaysLine* r = new RaysLine(x1, y1, x2, y2);
		lines.push_back(r);
	}
	if (type == 'S') {
		SegmentLine* s = new SegmentLine(x1, y1, x2, y2);
		lines.push_back(s);
	}
}

void addCircle(long long x, long long y, long long r) {
	Circle c(x, y, r);
	circles.push_back(c);
}

void delLine(int index) {
	vector<Line*>::iterator iter = lines.begin();
	delete(lines.at(index));
	lines.erase(iter + index);
}

void delCircle(int index) {
	vector<Circle>::iterator iter = circles.begin();
	circles.erase(iter + index);
}

void inputFile(char* path) {
	fin.open(path);
	int N;
	fin >> N;
	for (int i = 0; i < N; ++i) {
		char type;
		fin >> type;

		if (type == 'C') {
			long long x, y, r;
			fin >> x >> y >> r;
			addCircle(x, y, r);
		}
		else {
			long long x1, y1, x2, y2;
			fin >> x1 >> y1 >> x2 >> y2;
			addLine(type, x1, y1, x2, y2);
		}
	}
}

void inputArg(int argc, char** argv) {
	char* inputFilePath = NULL;
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "-i") == 0) {
			inputFilePath = argv[++i];
		}
		if (strcmp(argv[i], "-o") == 0) {
			fout.open(argv[++i]);
		}
	}
	inputFile(inputFilePath);
}

void solve() {
	for (int i = 0; i < (int)lines.size(); ++i) {//直线与直线相交
		for (int j = i + 1; j < (int)lines.size(); ++j) {
			lineIntersectLine(*lines[i], *lines[j]);
		}
	}
	for (int i = 0; i < (int)lines.size(); ++i) {//直线与圆相交
		for (int j = 0; j < (int)circles.size(); ++j) {
			lineIntersectCircle(*lines[i], circles[j]);
		}
	}
	for (int i = 0; i < (int)circles.size(); ++i) {//圆与圆相交
		for (int j = i + 1; j < (int)circles.size(); ++j) {
			circleIntersectCircle(circles[i], circles[j]);
		}
	}
}

int main(int argc, char** argv) {
	inputArg(argc, argv);
	solve();
	fout << points.size() << endl;
}

void draw() {
	for (unsigned int i = 0; i < lines.size(); i++) {

	}
	for (unsigned int i = 0; i < circles.size(); i++) {

	}
}

void drawPoint() {
	set<Point>::iterator iter = points.begin();
	while (iter != points.end()) {

		iter++;
	}
}