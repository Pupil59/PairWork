#pragma once
#include <string>
using namespace std;
extern "C" _declspec(dllexport) void addLine(string type, long long x1, long long y1, long long x2, long long y2);
extern "C" _declspec(dllexport) void addCircle(long long x, long long y, long long r);
extern "C" _declspec(dllexport) void delLine(int index);
extern "C" _declspec(dllexport) void delCircle(int index);
extern "C" _declspec(dllexport) void inputFile(char* path);
extern "C" _declspec(dllexport) int solve();
extern "C" _declspec(dllexport) void draw();
extern "C" _declspec(dllexport) void drawPoint();
extern "C" _declspec(dllexport) void showLine();
extern "C" _declspec(dllexport) void showCircle();