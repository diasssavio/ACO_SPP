//============================================================================
// Name        : aco.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Ant Colony Optimisation Interface
//============================================================================

#ifndef ACO_H_
#define ACO_H_

#include "instance.h"
#include "solution.h"
#include "neighborhoods.h"
#include "logger.h"
#include "mt19937ar.h"

#include <utility>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>

using namespace std;

class aco {
private:
	// Parameters
	unsigned max_it;
	double alpha;

	// Input instance
	instance spp;

	// Result best solution
	solution best;

	// Logs
	logger* logs;

public:
	aco( instance&, unsigned, double, logger* );
	virtual ~aco();

	solution& execute();

};

#endif /* ACO_H_ */
