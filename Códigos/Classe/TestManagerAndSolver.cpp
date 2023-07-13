#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
using namespace std;

#include <chrono>
using namespace std::chrono;

#define RUNS 20					//how many runs for each instance?

//Node class for use in graph search
class Node{
public:	
	Node()
	{
		degree = 0;
		visited = false;
		id = 0;
	}
	
	void setDegree(int i)
	{
		degree = i;
	}
	
	void setVisited(bool b)
	{
		visited = b;
	}
		
	void setId(int i)
	{
		id = i;
	}

	int getDegree()
	{
		return degree;
	}
	
	bool wasVisited()
	{
		return visited;
	}
		
	int getId()
	{
		return id;
	}

private:
	int degree;	 //stores the degree of the node
	int id;		 //stores the index of the node
	bool visited; //indicates whether the node has been reached by the BFS
};

class Solver
{		
	public:

	Solver(string fileName)
	{
		inputFileName = fileName;
		readProblem(fileName);
	}
	
	~Solver()
	{
		termination();
	}
		
	/*
	Initializes the structures, vectors and matrices used
	*/
	void initialization()
	{
	}

	/*
	Reads the problem from a file specified by fileName
	*/
	void readProblem(string fileName)
	{
		ifstream fpIn(fileName);								//input file

		initialization();										//initializes all structures, vectors and matrices
	}

	/*
	Builds the graph 
	*/
	void buildGraph()
	{
	}


	/*
	Evaluates the current solution
	*/
	int evaluation()
	{
		int value;
		return value;						//returns the maximum number of open stacks
	}

	/*
	 Pre-processing procedure
	 */
	void preProcessing()
	{
	}

	/*
	Terminates all data structures. 
	*/
	void termination()
	{
		//.clear in all data structures
		//=0 in all numeric variables
	}

	/*
	Prints the solution information to the output file, for use in multiruns
	*/
	void printSolution(int solutionValue, double time, int run)
	{
	    string outputFileName;

	    outputFileName = "Solution_"+inputFileName;

		ofstream fpSolution(outputFileName);	//file that contains the information about the solution of a problem instance
		
		//print input file name/characteristics	
		//print algorithm parameters and settings
		//print solution value
		//print solution time
		//print preprocessing result
		//print solution structure
	}

	/*
	Prints the solution information to the output file, for use in single runs
	*/
	void printSolution(string inputFileName, int solutionValue, double time)
	{
	    string outputFileName;

	    outputFileName = "Solution_"+inputFileName;

	    ofstream fpSolution(outputFileName); 	//file that contains the information about the solution of a problem instance
		
		//print input file name/characteristics	
		//print algorithm parameters and settings
		//print solution value
		//print solution time
		//print preprocessing result
		//print solution structure
	}

	/*
	Sets the lowerbound 
	*/
	void setLowerBound()
	{
	}

	/*
	Main procedure - Multi-Run version
	Parameters:
	solutionValue			stores the solution value obtained by the method
	runningTime				stores the exeution time of the method
	run 					stores the run #
	*/

	void multiRun(int *solutionValue, double *runningTime, int run)
	{
		int FinalSolutionValue = INT_MAX;
		duration<double> time_span2;

		//readProblem(inputFileName);													//reads the problem data

		high_resolution_clock::time_point t1 = high_resolution_clock::now();		//time taking
		
		setLowerBound();															//determines the largest pattern size
	   	preProcessing();															//preprocessing procedure, removes dominated patterns
	   	buildGraph();																//builds the mosp graph

		high_resolution_clock::time_point t2 = high_resolution_clock::now(); 		//time taking
	  	duration<double> time_span = duration_cast<duration<double> >(t2 - t1);

		*solutionValue = FinalSolutionValue;                             			//stores the solution value
		*runningTime =  time_span.count();											//stores the execution time

		//printSolution(inputFileName, *solutionValue, *runningTime, run);			//prints the solution to the file
		printSolution(*solutionValue, *runningTime, run);			//prints the solution to the file

		//termination();																//terminates all data structures
	}

	/*
	Main procedure - single run version
	Parameters:
	solutionValue			stores the solution value obtained by the method
	runningTime				stores the exeution time of the method
	inputFileName			stores the name of the file containing the instance
	*/
	void singleRun(int *solutionValue, double *runningTime, string inputFileName)
	{
		int i, j;
		int FinalSolutionValue = INT_MAX;											//considering minimization problems		

		readProblem(inputFileName);													//reads the problem data
		
		high_resolution_clock::time_point t1 = high_resolution_clock::now();		//time taking
		
		setLowerBound();															//determines the lower bound
	   	preProcessing();															//preprocessing procedure
	   	buildGraph();																//builds the graph
	    
	    //solve the problem

		high_resolution_clock::time_point t2 = high_resolution_clock::now(); 		//time taking
	  	duration<double> time_span = duration_cast<duration<double> >(t2 - t1);

		*solutionValue = FinalSolutionValue;                             			//stores the solution value
		*runningTime =  time_span.count();											//stores the execution time

		//printSolution(inputFileName, *solutionValue, *runningTime);				//prints the solution to the file 

		termination();																//terminates all data structures
	}

	private:

	string inputFileName; //stores the name of the input file
};
	
class TestManager{

	public:
	
	void run()
	{
		int i=0, j;
		ifstream fpIndex("index.txt");
		ofstream fpOut("RESULTS_SUMMARY.txt");

		while(fpIndex>>inputFileName)
		//while(fscanf(fpIndex, "%s", inputFileName) != -1)
		{
			Solver solve(inputFileName);

			i++;
			//single run
			//solve.singleRun(&LookaheadSolutionValue, &LookaheadRunningTime, inputFileName);
			
			//multiruns
			for(j=0; j<RUNS; j++)
			{
				printf("Run %d\n", j+1);						
				solve.multiRun(&solutionValue, &runningTime, j+1);
				printf("PROBLEM %d: %s %d\n", i, inputFileName.c_str(), solutionValue);
				fpOut<<inputFileName<<" "<<j+1<<" "<<solutionValue<<" "<<runningTime<<endl;
			}
		}
	}	
	
	private:
		int solutionValue;		//stores the result 
		double runningTime;		//stores the running time
		string inputFileName; 	//stores the name of the input file
		ofstream fpOut;			//output file 
		ifstream fpIndex; 		//input index file
};

int main() {
	TestManager tm;
	
	tm.run();
}