#ifndef UTILIDADES_CPP
#define UTILIDADES_CPP

#include "Utilidades.hpp"

vector<string> tokens(string line, char pattern) {
	stringstream ss(line);
	string s;
	vector<string> v;

	while (getline(ss, s, pattern)) {
		v.push_back(s);
	}

	return v;
}

default_random_engine & global_urng() {
	static default_random_engine u(359838953);
	return u;
}

void randomize() {
	static random_device rd{};
	global_urng().seed(rd());
}

void randomize(long seed) {
	global_urng().seed(seed);
}

int pick_a_number(int from, int upto) {
	static uniform_int_distribution<> d;
	using parm_t = decltype(d)::param_type;
	return d(global_urng(), parm_t{from, upto});
}

double pick_a_number(double from, double upto) {
	static uniform_real_distribution<> d{};
	using parm_t = decltype(d)::param_type;
	return d(global_urng(), parm_t{from, upto});
}

bool find(vector<int> v, int item) {
	for (int i=0; i<v.size(); i++)
		if (v[i] == item)
			return true;
		else if (v[i] == -1)
			return false;
	return false;
}

void swap(vector<int> &v, int p1, int p2) {
	int aux = v[p1];
	v[p1] = v[p2];
	v[p2] = aux;
}

string intToString(int n) {
	ostringstream ostr;
	ostr << n;

	return ostr.str();
}

bool endsWith(string base, string end) {
	int start = base.size()-end.size();
	for (int i=start, j=0; i<base.size(); i++, j++)
		if (base[i] != end[j])
			return false;
	return true;
}

#endif