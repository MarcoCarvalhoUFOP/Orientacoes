#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP

#include <vector>
#include <string>
#include <sstream>
#include <string>
#include <random>

using namespace std;

vector<string> tokens(string line, char pattern);

default_random_engine & global_urng(int seed);

void randomize();
void randomize(long seed);

int pick_a_number(int from, int upto);

double pick_a_number(double from, double upto);

bool find(vector<int> v, int item);

void swap(vector<int> &v, int p1, int p2);

string intToString(int n);

bool endsWith(string base, string end);

#endif