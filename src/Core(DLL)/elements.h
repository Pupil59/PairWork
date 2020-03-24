#pragma once
using namespace std;
const long long PerUnit = 40;
const long long Length = 1200;
const long long Height = 800;
const long long Yaxis = Height / 2;
const long long Xaxis = Length / 2;

class Point {
public:
	double x;
	double y;

	Point(double x, double y);
	bool operator<(const Point& p) const;
};
class Circle {
public:
	long long x;
	long long y;
	long long r;

	Circle(long long x, long long y, long long r);
};

class Line {
public://ʹ��һ��ʽ��ʾֱ�ߣ�����ʹ��double���־�����ʧ��
	long long a;
	long long b;
	long long c;

	Line(long long x1, long long y1, long long x2, long long y2);
	Line(long long a, long long b, long long c);
	virtual bool isInLine(double x, double y);
	virtual bool isRepeat(string type, long long x1, long long y1, long long x2, long long y2);
	virtual void draw();
	virtual void show();
};
class SegmentLine : public Line {
public:
	long long startX;
	long long startY;
	long long endX;
	long long endY;
	SegmentLine(long long x1, long long y1, long long x2, long long y2);
	bool isInLine(double x, double y);
	bool isRepeat(string type, long long x1, long long y1, long long x2, long long y2);
	void draw();
	void show();
};

class RaysLine : public Line {
public:
	long long startX;
	long long startY;
	int direct;
	//1����x��������2����x�Ḻ����3����y�������� 4����y�Ḻ����
	RaysLine(long long x1, long long y1, long long x2, long long y2);
	bool isInLine(double x, double y);
	bool isRepeat(string type, long long x1, long long y1, long long x2, long long y2);
	void draw();
	void show();
};