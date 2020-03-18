#pragma once
#include<cmath>
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