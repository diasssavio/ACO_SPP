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

#include "../include/typedef.hpp"
#include "../include/FWChrono.h"
#include "../include/logger.h"
#include "../include/mt19937ar.h"
#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/aco.h"

using namespace std;

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
  spp.read_from_file(args[1]);
	#if LOGS == true
		spp.show_data();
	#endif

  double alpha = 1;
	double beta = 1;
	double big_Q = 0.5;
	unsigned max_it = 50;

	unsigned n_neigh = 0;
	if(argc >= 4)
		n_neigh = string_to< unsigned >(args[3]) - 1;

	logger* logs = new logger(timer);
	aco ACO(spp, max_it, alpha, beta, big_Q, logs);

	// Executing Ant Colony Optimization algorithm
	// solution best = ACO.execute();
	timer.stop();
	// printf("%s;%d;%.2lf;%.2lf;%d;%.2lf;\n", args[1], n_neigh + 1, best.get_cost(), logs->best_time(), logs->get_individual_log(), logs->get_individual_average());

	return 0;
}
