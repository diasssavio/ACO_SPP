//============================================================================
// Name        : logger.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Logger class interface
//============================================================================

#ifndef LOGGER_H_
#define LOGGER_H_

#include "FWChrono.h"

#include <utility>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace std;

class logger {
private:
	// Parameters
	unsigned iteration = 0;

	// Logs
	vector< pair< double, unsigned > > it_log;
	vector< double > times;
	FWChrono timer;

	// Individual Neighborhood logs
	unsigned n_found_sol;
	double average_gain;

	// General Neighborhoods logs
	unsigned* g_n_found_sol;
	double* g_average_gain;

public:
	logger();
	logger( FWChrono& );
	virtual ~logger();

	void make_log( double );
	void make_individual_log( double, double );
	void make_general_log( unsigned, double, double );

	void print_log();
	unsigned get_individual_log() { return n_found_sol; }
	double get_individual_average();
	unsigned* get_n_found_sol() { return g_n_found_sol; }
	double* get_average();

  double best_time();

};

#endif /* LOGGER_H_ */
