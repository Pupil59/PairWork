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
	if (l1.b * l2.a != l1.a * l2.b) { //��ƽ�вŻ��ཻ
		double x = (double)(l2.c * l1.b - l1.c * l2.b) / (double)(l1.a * l2.b - l1.b * l2.a);
		double y = (double)(l2.c * l1.a - l1.c * l2.a) / (double)(l1.b * l2.a - l1.a * l2.b);
		if (l1.isInLine(x, y) && l2.isInLine(x, y)) {
			Point p(x, y);
			points.insert(p);
		}
	}
}

void lineIntersectCircle(Line &l, Circle cir) { 
	if (l.a == 0) { //ˮƽ��
		double y = -(double)l.c / (double)l.b; //��yֵ����Բ����
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
	else {//ֱ��Ax+By+C=0��A��Ϊ�㣬���Խ�x��y��ʾ����Բ���̡�
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
	if ((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y) <= (c1.r + c2.r) * (c1.r + c2.r)//�����⽻
		|| (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y) >= (c1.r - c2.r) * (c1.r - c2.r)) {//�����ڽ�
		long long a = 2 * (c1.x - c2.x);
		long long b = 2 * (c1.y - c2.y);
		long long c = c2.x * c2.x - c1.x * c1.x + c2.y * c2.y - c1.y * c1.y + c1.r * c1.r - c2.r * c2.r;
		Line l(a, b, c);//��Բ��������õ��������ֱ�߷��̣�תΪֱ����Բ��������
		lineIntersectCircle(l, c1);
	}
}

void addLine(string type, long long x1, long long y1, long long x2, long long y2) {
	if (!(x1 > -100000 && x1 < 100000 && y1 > -100000 && y1 < 100000
		&& x2 > -100000 && x2 < 100000 && y2 > -100000 && y2 < 100000)) {
		throw "parameter out of range, correct range is (-100000, 100000)";
	}
	if (x1 == x2 && y1 == y2) {
		throw "two points coincide in a line definition,please input two different points";
	}
	for (unsigned int i = 0; i < lines.size(); i++) {
		if ((lines.at(i))->isRepeat(type, x1, y1, x2, y2)) {
			throw "two lines coincide";
		}
	}
	if (type == "L") {
		Line *l = new Line(x1, y1, x2, y2);
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
	if (fin.fail()) {
		throw "can not locate input file, please check the path of the file";
	}
	int N = -1;

	fin >> N;
	if (N <= 0) {
		throw "Incorrect Num at line 1, the Num must be a positive integer";
	}
	for (int i = 0; i < N; ++i) {
		string type;
		fin >> type;
		if (type != "L" && type != "S" && type != "R" && type != "C") {
			throw "Incorrect type, correct types are L, S, R, C";
		}
		if (type == "C") {
			long long x, y, r;
			fin >> x >> y >> r;
			if (fin.fail()) {
				throw "Incorrect parameter, please input integer and check the number of the circle parameters";
			}
			addCircle(x, y, r);		
		}
		else {
			long long x1, y1, x2, y2;
			fin >> x1 >> y1 >> x2 >> y2;
			if (fin.fail()) {
				throw "Incorrect parameter, please input integer and check the number of the line parameters";
			}
			addLine(type, x1, y1, x2, y2);		
		}
	}
}

void inputArg(int argc, char** argv) {
	char* inputFilePath = NULL;
		bool flagI = false;
		bool flagO = false;
		for (int i = 0; i < argc; ++i) {
			if (argv[i][0] == '-' && strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-o") != 0) {
				throw "Incorrect command line parameters, please use '-i' for input, '-o' for output";
			}
			if (strcmp(argv[i], "-i") == 0) {
				inputFilePath = argv[++i];
				flagI = true;
			}
			if (strcmp(argv[i], "-o") == 0) {
				fout.open(argv[++i]);
				flagO = true;
			}
		}
		if (flagI == false) {
			throw "'-i' is not found, please use '-i'";
		}
		if (flagO == false) {
			throw "'-o' is not found, please use '-o'";
		}
		inputFile(inputFilePath);
}

void solve() {
	for (int i = 0; i < (int)lines.size(); ++i) {//ֱ����ֱ���ཻ
		for (int j = i + 1; j < (int)lines.size(); ++j) {
			lineIntersectLine(*lines[i], *lines[j]);
		}
	}
	for (int i = 0; i < (int)lines.size(); ++i) {//ֱ����Բ�ཻ
		for (int j = 0; j < (int)circles.size(); ++j) {
			lineIntersectCircle(*lines[i], circles[j]);
		}
	}
	for (int i = 0; i < (int)circles.size(); ++i) {//Բ��Բ�ཻ
		for (int j = i + 1; j < (int)circles.size(); ++j) {
			circleIntersectCircle(circles[i], circles[j]);
		}
	}
}

int main(int argc, char** argv) {
	try {
		inputArg(argc, argv);
		solve();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	fout << points.size() << endl;
	fin.close();
	fout.close();
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