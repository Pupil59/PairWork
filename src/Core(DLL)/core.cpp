#include "pch.h"
#include "core.h"
#include "elements.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <graphics.h>

using namespace std;
ifstream fin;
vector<Line*> lines;
vector<Circle> circles;
set<Point> points;

void lineIntersectLine(Line& l1, Line& l2) {
	if (l1.b * l2.a != l1.a * l2.b) { //不平行才会相交
		double x = (double)(l2.c * l1.b - l1.c * l2.b) / (double)(l1.a * l2.b - l1.b * l2.a);
		double y = (double)(l2.c * l1.a - l1.c * l2.a) / (double)(l1.b * l2.a - l1.a * l2.b);
		if (l1.isInLine(x, y) && l2.isInLine(x, y)) {
			Point p(x, y);
			points.insert(p);
		}
	}
}

void lineIntersectCircle(Line& l, Circle cir) {
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

void inputFile(char* path) {
	fin.open(path);
	if (fin.fail()) {
		throw "can not locate input file, please check the path of the file";
	}
	int N = -1;

	fin >> N;
	if (N <= 0) {
		fin.close();
		throw "Incorrect Num at line 1, the Num must be a positive integer";
	}
	for (int i = 0; i < N; ++i) {
		string type;
		fin >> type;
		if (type != "L" && type != "S" && type != "R" && type != "C") {
			fin.close();
			throw "Incorrect type, correct types are L, S, R, C";
		}
		if (type == "C") {
			long long x, y, r;
			fin >> x >> y >> r;
			if (fin.fail()) {
				fin.close();
				throw "Incorrect circle parameter, please input integer and check the number of parameters";
			}
			addCircle(x, y, r);
		}
		else {
			long long x1, y1, x2, y2;
			fin >> x1 >> y1 >> x2 >> y2;
			if (fin.fail()) {
				fin.close();
				throw "Incorrect line parameter, please input integer and check the number of parameters";
			}
			addLine(type, x1, y1, x2, y2);
		}
	}
	fin.close();
}

void addLine(string type, long long x1, long long y1, long long x2, long long y2) {
	if (!(x1 > -100000 && x1 < 100000 && y1 > -100000 && y1 < 100000
		&& x2 > -100000 && x2 < 100000 && y2 > -100000 && y2 < 100000)) {
		throw "parameter out of range, correct range is (-100000, 100000)";
	}
	if (x1 == x2 && y1 == y2) {
		throw "two points coincide in a line definition, please input two different points";
	}

	for (unsigned int i = 0; i < lines.size(); i++) {
		if ((lines.at(i))->isRepeat(type, x1, y1, x2, y2)) {
			throw "two lines coincide";
		}
	}
	if (type == "L") {
		Line* l = new Line(x1, y1, x2, y2);
		lines.push_back(l);
	}
	if (type == "R") {
		RaysLine* r = new RaysLine(x1, y1, x2, y2);
		lines.push_back(r);
	}
	if (type == "S") {
		SegmentLine* s = new SegmentLine(x1, y1, x2, y2);
		lines.push_back(s);
	}
}

void addCircle(long long x, long long y, long long r) {
	if (!(x > -100000 && x < 100000 && y > -100000 && y < 100000 && r > -100000 && r < 100000)) {
		throw "parameter out of range, correct range is (-100000, 100000)";
	}
	if (r <= 0) {
		throw "radius of circle must be a positive integer";
	}
	for (unsigned int i = 0; i < circles.size(); i++) {
		Circle cir = circles.at(i);
		if (cir.x == x && cir.y == y && cir.r == cir.r) {
			throw "this circle exists";
		}
	}
	Circle c(x, y, r);
	circles.push_back(c);
}

void delLine(int index) {
	if (index < 0 || index >= lines.size()) {
		throw "Index out of range";
	}
	vector<Line*>::iterator iter = lines.begin();
	delete(lines.at(index));
	lines.erase(iter + index);
}

void delCircle(int index) {
	if (index < 0 || index >= circles.size()) {
		throw "Index out of range";
	}
	vector<Circle>::iterator iter = circles.begin();
	circles.erase(iter + index);
}

void showLine() {
	FILE* fp = NULL;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
	for (unsigned int i = 0; i < lines.size(); ++i) {
		cout << "Line " << i << ":";
		lines[i]->show();
	}
	FreeConsole();
}

void showCircle() {
	FILE* fp = NULL;
	AllocConsole();
	freopen_s(&fp,"CONOUT$", "w", stdout);
	for (unsigned int i = 0; i < circles.size(); ++i) {
		cout << "Circle " << i << ": (" << circles[i].x << "," << circles[i].y << ") r=" << circles[i].r << endl;
	}
	FreeConsole();
}

int solve() {
	points.clear();
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
	return (int)points.size();
}

void draw() {
	COLORREF color = RGB(245, 245, 245);
	initgraph(Length, Height);
	setbkcolor(color);
	cleardevice();
	//fillrectangle(0, 0, Length, Height);
	//画坐标轴
	setlinestyle(PS_SOLID, 3);
	color = RGB(28, 28, 28);
	setlinecolor(color);
	//x轴
	line(0, Yaxis, Length, Yaxis);
	//y轴
	line(Xaxis, 0, Xaxis, Height);
	setlinestyle(PS_DASH, 1);
	color = RGB(156, 156, 156);
	setlinecolor(color);
	for (unsigned int i = 0; i < Length / PerUnit; i++) {
		line(i * PerUnit, 0, i * PerUnit, Height);
		line(0, i * PerUnit, Length, i * PerUnit);
	}
	setlinestyle(PS_SOLID, 3);
	color = RGB(99, 184, 255);
	setlinecolor(color);
	for (unsigned int i = 0; i < circles.size(); i++) {
		Circle c = circles.at(i);
		circle((int)c.x * PerUnit + Xaxis, Yaxis - (int)c.y * PerUnit, (int)c.r * PerUnit);
	}
	color = RGB(255, 64, 64);
	setlinecolor(color);
	for (unsigned int i = 0; i < lines.size(); i++) {
		lines.at(i)->draw();
	}

}

void drawPoint() {
	setlinestyle(PS_SOLID, 3);
	COLORREF color = RGB(46, 139, 87);
	setfillcolor(color);
	setlinecolor(color);
	set<Point>::iterator iter = points.begin();
	FILE* fp = NULL;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
	int i = 0;
	while (iter != points.end()) {
		i++;
		int x = (int)(Xaxis + iter->x * PerUnit);
		int y = (int)(Yaxis - iter->y * PerUnit);
		cout << "Intersect Point " << i << ": (" << iter->x << ", " << iter->y << ")" << endl;
		fillcircle(x, y, 3);
		iter++;
	}
	FreeConsole();
}
