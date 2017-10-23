//============================================================================
// Name        : main.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Main program file
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "../include/FWChrono.h"
#include "../include/logger.h"
#include "../include/mt19937ar.h"
#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/aco.h"

using namespace std;

template<typename T>
T string_to(const string& s){
	istringstream i(s);
	T x;
	if (!(i >> x)) return 0;
	return x;
}

int main(int argc, char* args[]) {
	FWChrono timer;
	timer.start();

	unsigned long seed = time(NULL);
	if(argc >= 3)
		seed = string_to< unsigned long >(args[2]);
	// time_t seed = time(NULL);
	// srand(seed);
	init_genrand(seed);

	instance spp;
	// spp.read_data();
  spp.read_from_file(args[1]);
	spp.show_data();

  double alpha = 0.47;
	unsigned max_it = 61;

	unsigned n_neigh = 0;
	if(argc >= 4)
		n_neigh = string_to< unsigned >(args[3]) - 1;

	logger* logs = new logger(timer);
	// aco ACO(spp, max_it, alpha, logs);

	// Executing individual neighborhoods
	// solution best = ACO.execute();
	timer.stop();
	// printf("%s;%d;%.2lf;%.2lf;%d;%.2lf;\n", args[1], n_neigh + 1, best.get_cost(), logs->best_time(), logs->get_individual_log(), logs->get_individual_average());

	return 0;
}
