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
	// default_random_engine generator(seed);
	mt19937 generator(seed);

	instance spp;
  spp.read_from_file(args[1]);
	// #if LOGS == true
	// 	spp.show_data();
	// #endif

  double alpha = 2;
	double beta = 2;
	double rho = 0.2;
	double big_Q = 1;
	unsigned max_it = 50;
	if(argc >= 4) {
		alpha = string_to< double >(args[3]);
		beta = string_to< double >(args[4]);
		rho = string_to< double >(args[5]);
		big_Q = string_to< double >(args[6]);
	}

	logger* logs = new logger(timer);
	aco ACO(spp, max_it, alpha, beta, rho, big_Q, logs, generator);

	// Executing Ant Colony Optimization algorithm
	solution* best = ACO.run();
	timer.stop();

	// Logging output data
	printf("BEST SOLUTION FOUND -------------------- \n");
	printf("BEST TIME (TOTAL): %.2lf (%.2lf)\n", logs->best_time(), timer.getStopTime());
	printf("SEED: %ld\n", seed);
	best->show_data();
	logs->print_log();

	FILE* _file = fopen("results.csv", "a+");
	if(_file)
		fprintf(_file, "%s;%ld;%.2lf;%d;%.2lf;%.2lf\n", args[1], seed, best->get_cost(), best->is_feasible(), logs->best_time(), timer.getStopTime());

	return 0;
}
