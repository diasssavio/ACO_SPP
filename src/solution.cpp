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
	feasible = covered = false;
}

solution::solution( solution& _sol ) {
	this->spp = _sol.get_instance();
	this->elems_represented = vector< unsigned >(_sol.get_elems_represented());
	this->sets_selected = vector< unsigned >(_sol.get_sets_selected());
	this->cost = _sol.get_cost();
	this->covered = _sol.is_covered();
	this->feasible = _sol.is_feasible();
}

solution::solution( instance& _spp, vector< unsigned > _elems, vector< unsigned > _sets, double _cost, bool _covered, bool _feasible ) : cost(_cost), covered(_covered), feasible(_feasible) {
	spp = _spp;
	elems_represented = _elems;
	sets_selected = _sets;
}

solution::~solution() { }

void solution::set_instance( instance& _spp ) { spp = _spp; }

void solution::set_elems_represented( const vector< unsigned >& _elems_represented ) { elems_represented = _elems_represented; }

void solution::set_sets_selected( const vector< unsigned >& _sets_selected ) { sets_selected = _sets_selected; }

void solution::set_cost( double _cost ) { cost = _cost; }

void solution::set_covered( bool _covered ) { covered = _covered; }

void solution::set_feasible( bool _feasible ) { feasible = _feasible; }

instance& solution::get_instance() { return spp; }

const vector< unsigned >& solution::get_elems_represented() const { return elems_represented; }

const vector< unsigned >& solution::get_sets_selected() const { return sets_selected; }

double solution::get_cost() { return cost; }

double solution::evaluate() {
	// TODO

	return cost;
}

bool solution::is_covered() { return covered; }

bool solution::is_feasible() { return feasible; }

void solution::show_data() {
	if(feasible)
		printf("SOLUTION DATA ----------------- FEASIBLE \n");
	else
		printf("SOLUTION DATA --------------- INFEASIBLE \n");
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
