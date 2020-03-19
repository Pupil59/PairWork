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
	try {
		if (!(x1 > -100000 && x1 < 100000 && y1 > -100000 && y1 < 100000
			&& x2 > -100000 && x2 < 100000 && y2 > -100000 && y2 < 100000)) {
			throw "parameter out of range, correct rang is (-100000, 100000)";
		}
		if (x1 == x2 && y1 == y2) {
			throw "Two points coincide in a line definition,please input two different points";
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
	catch(const char* msg) {
		cerr << msg << endl;
	}
	
}

void addCircle(long long x, long long y, long long r) {
	try {
		if (!(x > -100000 && x < 100000 && y > -100000 && y < 100000 && r > -100000 && r < 100000)) {
			throw "parameter out of range, correct rang is (-100000, 100000)";
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
	catch (const char* msg) {
		cerr << msg << endl;
	}
	
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
	int N = -1;
	try {
		fin >> N;
		if (N <= 0) {
			throw "Incorrect Num at line 1, the Num must be a positive integer";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
		return;
	}
	
	for (int i = 0; i < N; ++i) {
		string type;
		try {
			fin >> type;
			if (type != "L" && type != "S" && type != "R" && type != "C") {
				throw "Incorrect type at line ";
			}
		}catch (const char* msg) {
			cerr << msg << i + 2 << ", the type must be L, S, R, C"<< endl;
			return;
		}
		if (type == "C") {
			long long x, y, r;
			try {
				fin >> x >> y >> r;
				if (fin.fail()) {
					throw "Incorrect parameter at line ";
				}
				addCircle(x, y, r);
			}
			catch (const char* msg) {
				cerr << msg << i + 2 << ", please input integer or check the number of the parameters" << endl;
				return;
			}
			
		}
		else {
			long long x1, y1, x2, y2;
			try {
				fin >> x1 >> y1 >> x2 >> y2;
				if (fin.fail()) {
					throw "Incorrect parameter at line ";
				}
				addLine(type, x1, y1, x2, y2);
			}
			catch (const char* msg) {
				cerr << msg << i + 2 << ", please input integer or check the number of the parameters" << endl;
				return;
			}		
		}
	}
}

void inputArg(int argc, char** argv) {
	char* inputFilePath = NULL;
	try {
		for (int i = 0; i < argc; ++i) {
			if (argv[i][0] == '-' && strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-o") != 0) {
				throw "Incorrect command line parameters, please use '-i' for input, '-o' for output" ;
			}
			if (strcmp(argv[i], "-i") == 0) {
				inputFilePath = argv[++i];
			}
			if (strcmp(argv[i], "-o") == 0) {
				fout.open(argv[++i]);
			}
		}
		inputFile(inputFilePath);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
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