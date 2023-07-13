#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <random>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#include <climits>

#include <string.h>
#include <stdlib.h>

#include "Utilidades.hpp"

using namespace std;
using namespace std::chrono;

/*
Initializes the structures, vectors and matrices used
*/
void initialization();

/*
Reads the problem from a file specified by inputFileName
*/
void readProblem(string inputFileName);

/*
Terminates all data structures. 
*/
void termination();

/*
Prints the solution information to the output file
*/
void printSolution(string inputFileName, unsigned long solutionValue, double t, int run);

/*
Main procedure - Multi-Run version
Parameters:
solutionValue			stores the solution value obtained by the method
runningTime				stores the exeution time of the method
inputFileName			stores the name of the file containing the instance
*/
void multiRun(int &solutionValue, double &runningTime, string inputFileName, int run, int metodo);

#endif