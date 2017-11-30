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
	instance spp;

	vector< unsigned > NL;

	logger* log_system;

	// Result best solution
	solution best;

public:
	neighborhoods( instance&, logger* = NULL );
	virtual ~neighborhoods();

	solution swap11( solution& );
	solution swap12( solution& );
	solution swap21( solution& );
	solution swap22( solution& );

	solution& execute( solution& );

};

#endif /* NEIGHBORHOODS_H_ */
