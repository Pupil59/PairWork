#include"pch.h"
#include<cmath>
#include<iostream>
#include<graphics.h>
#include"elements.h"
using namespace std;

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}
bool Point::operator<(const Point& p) const {//使用自定义类型的set需要重载<运算符
	if (x < p.x && p.x - x > 1e-8) {
		return true;
	}
	else {
		if (fabs(x - p.x) <= 1e-8 && y < p.y && p.y - y > 1e-8) { //采用1e-8的精度判断相等
			return true;
		}
	}
	return false;
}

Circle::Circle(long long x, long long y, long long r) {
	this->x = x;
	this->y = y;
	this->r = r;
}
long long gcd(long long m, long long n) {
	long long mid;
	while (n > 0) {
		mid = m % n;
		m = n;
		n = mid;
	}
	return m;
}
Line::Line(long long x1, long long y1, long long x2, long long y2) {
	this->a = y2 - y1;
	this->b = x1 - x2;
	this->c = x2 * y1 - x1 * y2;
	long long m;
	if (a < b) {
		m = gcd(abs(b), abs(a));
	}
	else {
		m = gcd(abs(a), abs(b));
	}
	if (m < c) {
		m = gcd(abs(c), m);
	}
	else {
		m = gcd(m, abs(c));
	}
	this->a = a / m;
	this->b = b / m;
	this->c = c / m;
	if (a < 0) {
		this->a = -a;
		this->b = -b;
		this->c = -c;
	}
}
Line::Line(long long a, long long b, long long c) {
	this->a = a;
	this->b = b;
	this->c = c;
}
bool Line::isInLine(double x, double y) {
	return true;
}
bool Line::isRepeat(string type, long long x1, long long y1, long long x2, long long y2) {
	Line l(x1, y1, x2, y2);
	if (a == l.a && b == l.b && c == l.c) {
		return true;
	}
	return false;
}
void Line::draw() {
	if (b == 0) {
		line(Xaxis + (-c / a) * PerUnit, 0, Xaxis + (-c / a) * PerUnit, Height);
	}
	else {
		long long x1 = -Length / (2 * PerUnit);
		long long x2 = Length / (2 * PerUnit);
		long long y1 = ((-c - a * x1) * PerUnit) / b;
		long long y2 = ((-c - a * x2) * PerUnit) / b;
		line(0, Yaxis - y1, Length, Yaxis - y2);
	}
}
void Line::show() {
	if (a != 0) {
		cout << a << "x";
	}
	if (b > 0) {
		cout << "+" << b << "y";
	}
	if (b < 0) {
		cout << b << "y";
	}
	if (c > 0) {
		cout << "+" << c << "=0";
	}
	if (c < 0) {
		cout << c << "=0";
	}
	cout << "(Line)" << endl;
}

SegmentLine::SegmentLine(long long x1, long long y1, long long x2, long long y2) : Line(x1, y1, x2, y2) {
	if (x1 < x2) {
		this->startX = x1;
		this->startY = y1;
		this->endX = x2;
		this->endY = y2;
	}
	else {
		if (y1 < y2) {
			this->startX = x1;
			this->endX = x2;
			this->startY = y1;
			this->endY = y2;
		}
		else {
			this->startX = x2;
			this->endX = x1;
			this->startY = y2;
			this->endY = y1;
		}
	}
}
bool SegmentLine::isInLine(double x, double y) {
	if (startX == endX) {
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
bool SegmentLine::isRepeat(string type, long long x1, long long y1, long long x2, long long y2) {
	RaysLine l(x1, y1, x2, y2);
	if (a == l.a && b == l.b && c == l.c) {
		if (type == "L") {
			return true;
		}
		if (type == "S") {
			if (x1 == x2) {
				if ((y1 > startY && y1 < endY) || (y2 > startY && y2 < endY)) {
					return true;
				}
			}
			else {
				if ((x1 > startX && x1 < endX) || (x2 > startX && x2 < endX)) {
					return true;
				}
			}
		}
		if (type == "R") {
			switch (l.direct)
			{
			case 1:
				return (endX > l.startX);
			case 2:
				return (startX < l.startX);
			case 3:
				return (endY > l.startY);
			case 4:
				return (startY < l.startY);
			}
		}
	}
	return false;
}
void SegmentLine::draw() {
	line(Xaxis + startX * PerUnit, Yaxis - startY * PerUnit, Xaxis + endX * PerUnit, Yaxis - endY * PerUnit);
}
void SegmentLine::show() {
	if (a != 0) {
		cout << a << "x";
	}
	if (b > 0) {
		cout << "+" << b << "y";
	}
	if (b < 0) {
		cout << b << "y";
	}
	if (c > 0) {
		cout << "+" << c << "=0";
	}
	if (c < 0) {
		cout << c << "=0";
	}
	cout << "(SegmentLine) ";
	cout << "start:(" << startX << "," << startY << ") ";
	cout << "end:(" << endX << "," << endY << ") " << endl;
}

//1代表x轴正方向，2代表x轴负方向，3代表y轴正方向， 4代表y轴负方向
RaysLine::RaysLine(long long x1, long long y1, long long x2, long long y2) : Line(x1, y1, x2, y2) {
	this->startX = x1;
	this->startY = y1;
	if (x1 == x2) {
		this->direct = (y1 < y2) ? 3 : 4;
	}
	else {
		this->direct = (x1 < x2) ? 1 : 2;
	}
}
bool RaysLine::isInLine(double x, double y) {
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
bool RaysLine::isRepeat(string type, long long x1, long long y1, long long x2, long long y2) {
	SegmentLine l(x1, y1, x2, y2);
	if (a == l.a && b == l.b && c == l.c) {
		if (type == "L") {
			return true;
		}
		if (type == "S") {
			switch (direct)
			{
			case 1:
				return (l.endX > startX);
			case 2:
				return (l.startX < startX);
			case 3:
				return (l.endY > startY);
			case 4:
				return (l.startY < startY);
			}
		}
		if (type == "R") {
			RaysLine r(x1, y1, x2, y2);
			if (direct == r.direct) {
				return true;
			}
			else {
				if (x1 == x2) {
					if ((r.startY > startY && r.direct == 4) || (r.startY < startY && r.direct == 3)) {
						return true;
					}
				}
				else {
					if ((r.startX > startX && r.direct == 2) || (r.startX < startX && r.direct == 1)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
void RaysLine::draw() {
	long long x1, x2, y1, y2;
	switch (direct)
	{
	case 1:
		x1 = -Length / (2 * PerUnit);
		x2 = Length / (2 * PerUnit);
		y1 = ((-c - a * x1) * PerUnit) / b;
		y2 = ((-c - a * x2) * PerUnit) / b;
		line(Xaxis + startX * PerUnit, Yaxis - startY * PerUnit, Length, Yaxis - y2);
		break;
	case 2:
		x1 = -Length / (2 * PerUnit);
		x2 = Length / (2 * PerUnit);
		y1 = ((-c - a * x1) * PerUnit) / b;
		y2 = ((-c - a * x2) * PerUnit) / b;
		line(Xaxis + startX * PerUnit, Yaxis - startY * PerUnit, 0, Yaxis - y1);
		break;
	case 3:
		line(Xaxis + startX * PerUnit, Yaxis - startY * PerUnit, Xaxis + startX * PerUnit, 0);
		break;
	case 4:
		line(Xaxis + startX * PerUnit, Yaxis - startY * PerUnit, Xaxis + startX * PerUnit, Height);
		break;
	}
}
void RaysLine::show() {
	if (a != 0) {
		cout << a << "x";
	}
	if (b > 0) {
		cout << "+" << b << "y";
	}
	if (b < 0) {
		cout << b << "y";
	}
	if (c > 0) {
		cout << "+" << c << "=0";
	}
	if (c < 0) {
		cout << c << "=0";
	}
	cout << "(RaysLine) ";
	cout << "start:(" << startX << "," << startY << ") ";
	switch (direct) {
		case 1:
			cout << "direct: Xaxis positive" << endl;
			break;
		case 2:
			cout << "direct: Xaxis negative" << endl;
			break;
		case 3:
			cout << "direct: Yaxis positive" << endl;
			break;
		case 4:
			cout << "direct: Yaxis negative" << endl;
			break;
	}
}
