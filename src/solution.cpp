//============================================================================
// Name        : solution.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Solution represetation class implementation
//============================================================================

#include "../include/solution.h"

solution::solution() { }

solution::solution( instance& _spp ) {
	spp = _spp;
	elems_represented = vector< unsigned >(spp.get_n());
	cost = numeric_limits< double >::max();
}

solution::solution( solution& _sol ) {
	// TODO
}

solution::~solution() { }

void solution::set_instance( instance& _spp ) { spp = _spp; }

void solution::set_elems_represented( const vector< unsigned >& _elems_represented ) { elems_represented = _elems_represented; }

void solution::set_sets_selected( const vector< unsigned >& _sets_selected ) { sets_selected = _sets_selected; }

void solution::set_cost( double _cost ) { cost = _cost; }

instance& solution::get_instance() { return spp; }

const vector< unsigned >& solution::get_elems_represented() const { return elems_represented; }

const vector< unsigned >& solution::get_sets_selected() const { return sets_selected; }

double solution::get_cost() { return cost; }

double solution::evaluate() {
	// TODO

	return cost;
}

void solution::show_data() {
	// TODO
}

void solution::show_latex( char* filename, char* out_file ) {
	// TODO
}
