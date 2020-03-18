#pragma once
#include<cmath>
#include<iostream>
using namespace std;
class Point {
public:
	double x;
	double y;

	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	bool operator<(const Point& p) const {//ʹ���Զ������͵�set��Ҫ����<�����
		if (x < p.x && p.x - x > 1e-8) {
			return true;
		}
		else {
			if (fabs(x - p.x) <= 1e-8 && y < p.y && p.y - y > 1e-8) { //����1e-8�ľ����ж����
				return true;
			}
		}
		return false;
	}
};
class Line {
public://ʹ��һ��ʽ��ʾֱ�ߣ�����ʹ��double���־�����ʧ��
	long long a;
	long long b;
	long long c;

	Line(long long x1, long long y1, long long x2, long long y2) {
		this->a = y2 - y1;
		this->b = x1 - x2;
		this->c = x2 * y1 - x1 * y2;
	}
	Line(long long a, long long b, long long c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
	virtual bool isInLine(double x, double y) {
		return true;
	}
};
class Circle {
public:
	long long x;
	long long y;
	long long r;

	Circle(long long x, long long y, long long r) {
		this->x = x;
		this->y = y;
		this->r = r;
	}
};

class SegmentLine : public Line {
public:
	long long startX;
	long long startY;
	long long endX;
	long long endY;
	SegmentLine(long long x1, long long y1, long long x2, long long y2) : Line(x1, y1, x2, y2) {
		if (x1 < x2) {
			this->startX = x1;
			this->startY = y1;
			this->endX = x2;
			this->endY = y2;
		}
		else {
			this->startX = x2;
			this->endX = x1;
			if (y1 < y2) {
				this->startY = y1;
				this->endY = y2;
			}
			else {
				this->startY = y2;
				this->endY = y1;
			}
		}
	}
	bool isInLine(double x, double y) {
		if (startX ==  endX) {
			if ((y < startY && (startY - y) > 1e-8) || (y > endY && (y - endY) > 1e-8)) {
				return false;
			}
		}
		else {
			if ((x < startX && (startX - x) > 1e-8) || (x > endX && (x - endX) > 1e-8)) {
				return false;
			}
		}
		return true;
	}
};

class RaysLine : public Line {
public:
	long long startX;
	long long startY;
	int direct;
	//1����x��������2����x�Ḻ����3����y�������� 4����y�Ḻ����
	RaysLine(long long x1, long long y1, long long x2, long long y2) : Line(x1, y1, x2, y2) {
		this->startX = x1;
		this->startY = y1;
		if (x1 == x2) {
			this->direct = (y1 < y2) ? 3 : 4;
		}
		else {
			this->direct = (x1 < x2) ? 1 : 2;
		}
	}
	bool isInLine(double x, double y) {
		switch (this->direct)
		{
		case 1:
			if (x < startX && (startX - x) > 1e-8) {
				return false;
			}
			break;
		case 2:
			if (x > startX && (x - startX) > 1e-8) {
				return false;
			}
			break;
		case 3:
			if (y < startY && (startY - y) > 1e-8) {
				return false;
			}
			break;
		case 4:
			if (y > startY && (y - startY) > 1e-8) {
				return false;
			}
			break;
		}
		return true;
	}
};