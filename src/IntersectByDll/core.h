#pragma once
#pragma comment(lib, "Core.lib")
#include <string>
using namespace std;
extern "C" _declspec(dllimport) void addLine(string type, long long x1, long long y1, long long x2, long long y2);
extern "C" _declspec(dllimport) void addCircle(long long x, long long y, long long r);
extern "C" _declspec(dllimport) void delLine(int index);
extern "C" _declspec(dllimport) void delCircle(int index);
extern "C" _declspec(dllimport) void inputFile(char* path);
extern "C" _declspec(dllimport) int solve();
extern "C" _declspec(dllimport) void draw();
extern "C" _declspec(dllimport) void drawPoint();
extern "C" _declspec(dllimport) void showLine();
extern "C" _declspec(dllimport) void showCircle();
extern "C" _declspec(dllimport) void inputArg(int argc, char** argv);
extern "C" _declspec(dllimport) void outputArg();