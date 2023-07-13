#include <iostream>
#include <fstream>
#include <iomanip>

#include "Solver.hpp"
#include "Utilidades.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	int solutionValue, run, metodo;
	double runningTime;
	string inputFileName;

	inputFileName = argv[1];
	run = stoi(argv[2])+1;
	metodo = stoi(argv[3]);
	randomize(stol(argv[4]));

	multiRun(solutionValue, runningTime, inputFileName, run, metodo);

	return 0;
}