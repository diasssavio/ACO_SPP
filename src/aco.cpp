//============================================================================
// Name        : aco.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Ant Colony Optimisation class implementation
//============================================================================

#include "../include/aco.h"

aco::aco( instance& _spp, unsigned _it, double _alpha, logger* _logs ) : max_it(_it), alpha(_alpha) {
	this->spp = _spp;
	this->logs = _logs;
}

aco::~aco() { }

solution& aco::execute() {
	// TODO

	return best;
}
