#include <iostream>
#include "core.h"
using namespace std;

int main(int argc, char** argv) {
	try {
		inputArg(argc, argv);
		outputArg();
	}
	catch(const char* msg) {
		cerr << msg << endl;
	}
}