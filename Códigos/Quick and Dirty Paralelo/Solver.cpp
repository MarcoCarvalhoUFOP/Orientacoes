#ifndef SOLVER_CPP
#define SOLVER_CPP

#include "Solver.hpp"

void initialization() {
}

void readProblem(string dirName) {
	
}

void termination() {
	//.clear in all data structures
	//=0 in all numeric variables
}

void printSolution(string inputFileName, unsigned long solutionValue, double t, int run) {
	ofstream fpSolution;

	stringstream ss;
	ss << "results/" << inputFileName << "_Run" << run << ".txt";

	string outputFileName;
	ss >> outputFileName;

	//file that contains the information about the solution of a problem instance
	fpSolution.open(outputFileName);

	//print input file name/characteristics
	fpSolution << inputFileName << "|" << run << "|";

	//print algorithm parameters and settings

	//print solution value
	fpSolution << solutionValue;

	//print solution time
	fpSolution << "|" << t << endl;

	//print preprocessing result

	//print solution structure
	

	fpSolution.close();
}

void multiRun(int &solutionValue, double &runningTime, string inputFileName, int run, int metodo) {
	unsigned long FinalSolutionValue = INT_MAX;
	duration<double> time_span2;

	readProblem(inputFileName);													//reads the problem data

	high_resolution_clock::time_point t1 = high_resolution_clock::now();		//time taking

	switch(metodo) {
		default:
			break;
	}

	FinalSolutionValue = pick_a_number(1, 100);

	high_resolution_clock::time_point t2 = high_resolution_clock::now(); 		//time taking
	duration<double> time_span = duration_cast<duration<double> >(t2 - t1);

	solutionValue = FinalSolutionValue;                             			//stores the solution value
	runningTime =  time_span.count();											//stores the execution time
	printSolution(inputFileName, solutionValue, runningTime, run);				//prints the solution to the file
	termination();																//terminates all data structures
}

#endif