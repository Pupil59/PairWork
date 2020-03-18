#include "pch.h"
#include "CppUnitTest.h"
#include "..\IntersectProject\elements.h"
#include "..\IntersectProject\main.cpp"
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
			Circle c(1,-1,1);
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
	};
}
