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
	is_feasible = is_covered = false;
}

solution::solution( solution& _sol ) {
	this->spp = _sol.get_instance();
	this->elems_represented = vector< unsigned >(_sol.get_elems_represented());
	this->sets_selected = vector< unsigned >(_sol.get_sets_selected());
	this->cost = _sol.get_cost();
	this->is_covered = _sol.is_covered();
	this->is_feasible = _sol.is_feasible();
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

bool solution::is_covered() { return is_covered; }

bool solution::is_feasible() { return is_feasible; }

void solution::show_data() {
	printf("SOLUTION DATA -------------------------- \n");
	printf("COST: %.2lf\n", cost);
	printf("ELEMS REPRESENTED:\n");
	for(unsigned i = 0; i < spp.get_n(); i++)
		printf("%4d", elems_represented[i]);
	printf("\nSETS SELECTED:\n");
	for(unsigned i = 0; i < sets_selected.size(); i++)
		printf("%4d", sets_selected[i]);
	printf("\n");
	printf(" --------------------------------------- \n");
}

void solution::show_latex( char* filename, char* out_file ) {
	// TODO
}
