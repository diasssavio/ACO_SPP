//============================================================================
// Name        : neighborhoods.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Neighborhoods class interface
//============================================================================

#ifndef NEIGHBORHOODS_H_
#define NEIGHBORHOODS_H_

#include "instance.h"
#include "solution.h"
#include "mt19937ar.h"
#include "logger.h"

#include <utility>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;

int myrandom( unsigned );

class neighborhoods {
private:
	// Input instance
	instance cars;

	vector< unsigned > i_NL;
	vector< unsigned > o_NL;

	bool logs;
	logger* log_system;

	// Result best solution
	solution best;

public:
	neighborhoods( instance&, logger* = NULL, bool = false );
	virtual ~neighborhoods();

	solution& execute( solution& );

};

#endif /* NEIGHBORHOODS_H_ */
