//============================================================================
// Name        : neighborhoods.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Neighborhoods class implementation
//============================================================================

#include "../include/neighborhoods.h"

int myrandom( unsigned i ) { return genrand_int32() % i; }

neighborhoods::neighborhoods( instance& _cars, logger* _log, bool _logs ) {
	this->cars = _cars;
	this->logs = _logs;
	this->log_system = _log;
}

neighborhoods::~neighborhoods() { }

solution& neighborhoods::execute( solution& p_sol ) {
	// TODO

	return best;
}
