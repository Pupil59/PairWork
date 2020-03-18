#include "pch.h"
#include "CppUnitTest.h"
#include "..\PairWork\elements.h"
#include "..\PairWork\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntersectTest
{
	TEST_CLASS(IntersectTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{//验证设定精度下的去重功能
			Point p1(1.0000000001, 0.999999999);
			Point p2(1.0000000000, 1.000000000);
			Point p3(0.9999999999, 0.999999998);
			points.insert(p1);
			points.insert(p2);
			points.insert(p3);
			Assert::AreEqual((int)points.size(), 1);
			points.clear();
		}

		TEST_METHOD(TestMethod2)
		{ //直线平行
			Line l1(1, 2, 2, 4);
			Line l2(1, 3, 2, 5);
			lineIntersectLine(l1, l2);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod3)
		{ //直线相交
			Line l1(1, 2, 2, 4);
			Line l2(3, 0, 0, 6);
			lineIntersectLine(l1, l2);
			Assert::AreEqual((int)points.size(), 1);
			Assert::AreEqual(points.begin()->x, 1.5);
			Assert::AreEqual(points.begin()->y, 3.0);
			points.clear();
		}

		TEST_METHOD(TestMethod4)
		{ //直线与圆相离
			Line l(1, 2, 2, 4);
			Circle c(1, -1, 1);
			lineIntersectCircle(l, c);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod5)
		{ //直线与圆相切
			Line l(1, -4, 5, -7);
			Circle c(-6, -5, 5);
			lineIntersectCircle(l, c);
			Assert::AreEqual((int)points.size(), 1);
			Assert::AreEqual(points.begin()->x, -3.0);
			Assert::AreEqual(points.begin()->y, -1.0);
			points.clear();
		}

		TEST_METHOD(TestMethod6)
		{ //直线与圆相交
			Line l(3, 4, 5, 2);
			Circle c(2, 3, 2);
			lineIntersectCircle(l, c);
			Assert::AreEqual((int)points.size(), 2);
			set<Point>::iterator it = points.begin();
			Assert::AreEqual(it->x, 2.0);
			Assert::AreEqual(it->y, 5.0);
			it++;
			Assert::AreEqual(it->x, 4.0);
			Assert::AreEqual(it->y, 3.0);
			points.clear();
		}

		TEST_METHOD(TestMethod7)
		{ //圆与圆内离
			Circle c1(2, 3, 3);
			Circle c2(3, 2, 1);
			circleIntersectCircle(c1, c2);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod8)
		{ //圆与圆外离
			Circle c1(0, 6, 3);
			Circle c2(3, 2, 1);
			circleIntersectCircle(c1, c2);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod9)
		{ //圆与圆内切
			Circle c1(2, 2, 2);
			Circle c2(3, 2, 1);
			circleIntersectCircle(c1, c2);
			Assert::AreEqual((int)points.size(), 1);
			Assert::AreEqual(points.begin()->x, 4.0);
			Assert::AreEqual(points.begin()->y, 2.0);
			points.clear();
		}

		TEST_METHOD(TestMethod10)
		{ //圆与圆外切
			Circle c1(-7, 2, 5);
			Circle c2(5, -7, 10);
			circleIntersectCircle(c1, c2);
			Assert::AreEqual((int)points.size(), 1);
			Assert::AreEqual(points.begin()->x, -3.0);
			Assert::AreEqual(points.begin()->y, -1.0);
			points.clear();
		}

		TEST_METHOD(TestMethod11)
		{ //圆与圆相交
			Circle c1(1, 0, 2);
			Circle c2(2, 2, 1);
			circleIntersectCircle(c1, c2);
			Assert::AreEqual((int)points.size(), 2);
			set<Point>::iterator it = points.begin();
			Assert::AreEqual(it->x, 1.0);
			Assert::AreEqual(it->y, 2.0);
			it++;
			Assert::AreEqual(it->x, 2.6);
			Assert::AreEqual(it->y, 1.2);
			points.clear();
		}
		TEST_METHOD(TestMethod12)
		{//射线与直线不相交
			Line l1(0, 1, 1, 0);
			RaysLine r1(1, 1, 2, 2);
			lineIntersectLine(l1, r1);
			Assert::AreEqual((int)points.size(), 0);
			RaysLine r2(1, 1, 1, 2);
			lineIntersectLine(l1, r2);
			Assert::AreEqual((int)points.size(), 0);
			RaysLine r3(0, 0, -1, -1);
			lineIntersectLine(l1, r3);
			Assert::AreEqual((int)points.size(), 0);
			RaysLine r4(-1, -1, -1, -2);
			lineIntersectLine(l1, r4);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}
		TEST_METHOD(TestMethod13) 
		{//线段与直线不相交
			Line l1(0, 1, 1, 0);
			SegmentLine s1(1, 1, 2, 2);
			lineIntersectLine(l1, s1);
			Assert::AreEqual((int)points.size(), 0);
			SegmentLine s2(1, 1, 1, 2);
			lineIntersectLine(l1, s2);
			Assert::AreEqual((int)points.size(), 0);
			SegmentLine s3(1, 2, 1, 1);
			lineIntersectLine(l1, s3);
			Assert::AreEqual((int)points.size(), 0);
			SegmentLine s4(-1, -1, -2, -2);
			lineIntersectLine(l1, s4);
			Assert::AreEqual((int)points.size(), 0);
			SegmentLine s5(-1, -1, -1, -2);
			lineIntersectLine(l1, s5);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}
		TEST_METHOD(TestMethod14)
		{//射线与圆相交
			Circle c1(0, 0, 1);
			RaysLine r1(0, 1, 1, 1);
			lineIntersectCircle(r1, c1);
			Assert::AreEqual((int)points.size(), 1);
			Assert::AreEqual(points.begin()->x, 0.0);
			Assert::AreEqual(points.begin()->y, 1.0);
			points.clear();
		}
		TEST_METHOD(TestMethod15)
		{//线段与圆相交
			Circle c1(0, 0, 1);
			SegmentLine s1(0, 1, 0, -1);
			lineIntersectCircle(s1, c1);
			Assert::AreEqual((int)points.size(), 2);
			set<Point>::iterator it = points.begin();
			Assert::AreEqual(it->x, 0.0);
			Assert::AreEqual(it->y, -1.0);
			it++;
			Assert::AreEqual(it->x, 0.0);
			Assert::AreEqual(it->y, 1.0);
			points.clear();
		}

		TEST_METHOD(TestMethod16)
		{//input函数测试
			char* argv[5] = {"PairWork.exe", "-i", "in.txt", "-o", "out.txt" };
			input(5, argv);
			Assert::AreEqual((int)lines.size(), 3);
			Assert::AreEqual((int)circles.size(), 1);
			lines.clear();
			circles.clear();
		}
		TEST_METHOD(TestMethod17)
		{//solve函数测试
			Line* l = new Line(-1, 4, 4, -1);
			SegmentLine* s = new SegmentLine(0, 0, 1, 2);
			Circle c1(1, 0, 2);
			Circle c2(2, 2, 1);
			Circle c3(3, -2, 6);
			lines.push_back(l);
			lines.push_back(s);
			circles.push_back(c1);
			circles.push_back(c2);
			circles.push_back(c3);
			solve();
			Assert::AreEqual((int)points.size(), 6);
			lines.clear();
			circles.clear();
			points.clear();
		}
	};
}
