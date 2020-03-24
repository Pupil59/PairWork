#include <iostream>
#include <fstream>
#include "core.h"
using namespace std;

ofstream fout;

void inputArg(int argc, char** argv) {
	char* inputFilePath = NULL;
	bool flagI = false;
	bool flagO = false;
	for (int i = 0; i < argc; ++i) {
		if (argv[i][0] == '-' && strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-o") != 0) {
			throw "Incorrect command line parameters, please use '-i' for input, '-o' for output";
		}
		if (strcmp(argv[i], "-i") == 0) {
			inputFilePath = argv[++i];
			flagI = true;
		}
		if (strcmp(argv[i], "-o") == 0) {
			fout.open(argv[++i]);
			flagO = true;
		}
	}
	if (flagI == false) {
		throw "'-i' is not found, please use '-i'";
	}
	if (flagO == false) {
		throw "'-o' is not found, please use '-o'";
	}
	inputFile(inputFilePath);
}

int main(int argc, char** argv) {
	try {
		inputArg(argc, argv);
		fout << solve() << endl;
	}
	catch(const char* msg) {
		cerr << msg << endl;
	}
}