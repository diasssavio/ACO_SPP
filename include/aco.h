//============================================================================
// Name        : aco.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Ant Colony Optimisation Interface
//============================================================================

#ifndef ACO_H_
#define ACO_H_

#include "typedef.hpp"
#include "instance.h"
#include "solution.h"
#include "neighborhoods.h"
#include "logger.h"
#include "mt19937ar.h"

#include <utility>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class aco {
private:
	// Parameters
	unsigned max_it;
	double alpha, beta;
	double big_Q;

	// Input instance
	instance spp;

	// Result best solution
	solution best;

	// ACO data
	vector< vector< double > > pheromones;
	vector< vector< double > > heuristics;
	vector< solution > ants;

	// Neighbors
	vector< vector< unsigned > > neighbors;

	// Utils
	double get_heuristic( unsigned, unsigned );
	void generate_ants();

	// Logs & seed
	logger* logs;
	unsigned long seed;

public:
	aco( instance&, unsigned, double, double, double, logger*, unsigned long );
	virtual ~aco();

	solution& execute();

};

#endif /* ACO_H_ */
