#include "pch.h"
#include "CppUnitTest.h"
#include "..\Intersect\elements.h"
#include "..\Intersect\main.cpp"
#include "..\Intersect\elements.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntersectTest
{
	TEST_CLASS(IntersectTest)
	{
	public:

		TEST_METHOD(TestMethod01)
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

		TEST_METHOD(TestMethod02)
		{ //直线平行
			Line l1(1, 2, 2, 4);
			Line l2(1, 3, 2, 5);
			lineIntersectLine(l1, l2);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod03)
		{ //直线相交
			Line l1(1, 2, 2, 4);
			Line l2(3, 0, 0, 6);
			lineIntersectLine(l1, l2);
			Assert::AreEqual((int)points.size(), 1);
			Assert::AreEqual(points.begin()->x, 1.5);
			Assert::AreEqual(points.begin()->y, 3.0);
			points.clear();
		}

		TEST_METHOD(TestMethod04)
		{ //直线与圆相离
			Line l(1, 2, 2, 4);
			Circle c(1, -1, 1);
			lineIntersectCircle(l, c);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod05)
		{ //直线与圆相切
			Line l(1, -4, 5, -7);
			Circle c(-6, -5, 5);
			lineIntersectCircle(l, c);
			Assert::AreEqual((int)points.size(), 1);
			Assert::AreEqual(points.begin()->x, -3.0);
			Assert::AreEqual(points.begin()->y, -1.0);
			points.clear();
		}

		TEST_METHOD(TestMethod06)
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

		TEST_METHOD(TestMethod07)
		{ //圆与圆内离
			Circle c1(2, 3, 3);
			Circle c2(3, 2, 1);
			circleIntersectCircle(c1, c2);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod08)
		{ //圆与圆外离
			Circle c1(0, 6, 3);
			Circle c2(3, 2, 1);
			circleIntersectCircle(c1, c2);
			Assert::AreEqual((int)points.size(), 0);
			points.clear();
		}

		TEST_METHOD(TestMethod09)
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
		{//inputArg函数测试
			char* argv[5] = { "Intersect.exe", "-i", "in.txt", "-o", "out.txt" };
			inputArg(5, argv);
			Assert::AreEqual((int)lines.size(), 3);
			Assert::AreEqual((int)circles.size(), 1);
			lines.clear();
			circles.clear();
			fin.close();
			fout.close();
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
		TEST_METHOD(TestMethod18)
		{//addLine
			addLine("L", 1, 2, 3, 4);
			addLine("S", 2, 2, -1, -4);
			addLine("R", 3, 4, 2, 7);
			Assert::AreEqual((int)lines.size(), 3);
			delLine(0);
			Assert::AreEqual((int)lines.size(), 2);
			delLine(0);
			Assert::AreEqual((int)lines.size(), 1);
			delLine(0);
			Assert::AreEqual((int)lines.size(), 0);
			lines.clear();
		}
		TEST_METHOD(TestMethod19)
		{//addCircle
			addCircle(0, 0, 1);
			addCircle(5, 6, 7);
			addCircle(4, 5, 6);
			Assert::AreEqual((int)circles.size(), 3);
			delCircle(0);
			Assert::AreEqual((int)circles.size(), 2);
			delCircle(0);
			Assert::AreEqual((int)circles.size(), 1);
			delCircle(0);
			Assert::AreEqual((int)circles.size(), 0);
			circles.clear();
		}
		TEST_METHOD(TestMethod20)
		{//inputFile
			char* path = "C:\\Users\\LY59\\Desktop\\Intersect\\IntersectTest\\in.txt";
			inputFile(path);
			Assert::AreEqual((int)lines.size(), 3);
			Assert::AreEqual((int)circles.size(), 1);
			lines.clear();
			circles.clear();
		}
		TEST_METHOD(TestMethod21)
		{
			try {
				char* argv[5] = { "Intersect.exe", "-v", "in.txt", "-o", "out.txt" };
				inputArg(5, argv);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "Incorrect command line parameters, please use '-i' for input, '-o' for output");
			}
			try {
				char* argv[5] = { "Intersect.exe", "iii", "in.txt", "-o", "out.txt" };
				inputArg(5, argv);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "'-i' is not found, please use '-i'");
			}
			try {
				char* argv[5] = { "Intersect.exe", "-i", "in.txt", "oooo", "out.txt" };
				inputArg(5, argv);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "'-o' is not found, please use '-o'");
			}
			fin.close();
		}
		//"Incorrect command line parameters, please use '-i' for input, '-o' for output"
		//"'-i' is not found, please use '-i'"
		//"'-o' is not found, please use '-o'"
		
		TEST_METHOD(TestMethod22)
		{
			try {
				char* path = "int.txt";
				inputFile(path);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "can not locate input file, please check the path of the file");
				fin.close();
			}
			try {
				char* path = "C:\\Users\\LY59\\Desktop\\Intersect\\IntersectTest\\test case\\case1.txt";
				inputFile(path);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "Incorrect Num at line 1, the Num must be a positive integer");
				fin.close();
			}
			try {
				char* path = "C:\\Users\\LY59\\Desktop\\Intersect\\IntersectTest\\test case\\case2.txt";
				inputFile(path);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "Incorrect type, correct types are L, S, R, C");
				fin.close();
			}
			try {
				char* path = "C:\\Users\\LY59\\Desktop\\Intersect\\IntersectTest\\test case\\case3.txt";
				inputFile(path);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "Incorrect parameter, please input integer and check the number of the circle parameters");
				fin.close();
			}
			try {
				char* path = "C:\\Users\\LY59\\Desktop\\Intersect\\IntersectTest\\test case\\case4.txt";
				inputFile(path);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "Incorrect parameter, please input integer and check the number of the line parameters");
				fin.close();
			}
		}
		//"can not locate input file, please check the path of the file"
		//"Incorrect Num at line 1, the Num must be a positive integer"
		//"Incorrect type, correct types are L, S, R, C"
		//"Incorrect parameter, please input integer and check the number of the circle parameters"
		//"Incorrect parameter, please input integer and check the number of the line parameters"

		TEST_METHOD(TestMethod23)
		{
			try {
				addLine("R", 1, 2, 3, 100000);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "parameter out of range, correct range is (-100000, 100000)");
			}
			
			try {
				addLine("R", 1, 1, 1, 1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two points coincide in a line definition,please input two different points");
			}
		}
		//parameter out of range, correct range is (-100000, 100000)
		//"two points coincide in a line definition,please input two different points"

		TEST_METHOD(TestMethod24) 
		{
			//直线和直线重合
			try {
				addLine("L", 1, 1, 2, 2);
				addLine("L", 3, 3, 4, 4);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			//射线与直线重合
			try {
				addLine("R", 1, 1, 2, 2);
				addLine("L", 3, 3, 4, 4);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			//射线与射线重合
			try {
				addLine("R", 1, 1, 2, 2);
				addLine("R", 3, 3, 4, 4);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("R", 0, 0, 1, 1);
				addLine("R", 1, 1, -1, -1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("R", 0, 0, -1, -1);
				addLine("R", -1, -1, 1, 1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("R", 0, 1, 0, 2);
				addLine("R", 0, 3, 0, 0);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("R", 0, 1, 0, -1);
				addLine("R", 0, 0, 0, 2);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			//射线与线段重合
			try {
				addLine("R", 0, 0, 1, 1);
				addLine("S", 1, 1, -1, -1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("R", 0, 0, -1, -1);
				addLine("S", -1, -1, 1, 1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("R", 0, 1, 0, 2);
				addLine("S", 0, 3, 0, 0);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("R", 0, 1, 0, -1);
				addLine("S", 0, 0, 0, 2);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			//线段与直线重合
			try {
				addLine("S", 0, 1, 0, -1);
				addLine("L", 0, 0, 0, 2);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			//线段与射线重合
			try {
				addLine("S", 1, 1, -1, -1);
				addLine("R", 0, 0, 1, 1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("S", -1, -1, 1, 1);
				addLine("R", 0, 0, -1, -1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("S", 0, 3, 0, 0);
				addLine("R", 0, 1, 0, 2);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("S", 0, 0, 0, 2);
				addLine("R", 0, 1, 0, -1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			//线段与线段重合
			try {
				addLine("S", 1, 1, 2, 2);
				addLine("S", 3, 3, 4, 4);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("S", 0, 0, 1, 1);
				addLine("S", 1, 1, -1, -1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("S", 0, 0, -1, -1);
				addLine("S", -1, -1, 1, 1);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("S", 0, 1, 0, 2);
				addLine("S", 0, 3, 0, 0);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
			try {
				addLine("S", 0, 1, 0, -1);
				addLine("S", 0, 0, 0, 2);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "two lines coincide");
				lines.clear();
			}
		}
		//"two lines coincide"

		TEST_METHOD(TestMethod25)
		{
			try {
				addCircle(100000, 100000, -100000);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "parameter out of range, correct range is (-100000, 100000)");
			}
			try {
				addCircle(1, 2, -3);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "radius of circle must be a positive integer");
			}
			try {
				addCircle(1, 2, 3);
				addCircle(1, 2, 3);
			}
			catch (char* msg) {
				Assert::AreEqual(msg, "this circle exists");
			}
		}
		//"radius of circle must be a positive integer"
		//"this circle exists"
	};
}
