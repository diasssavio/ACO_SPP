//============================================================================
// Name        : solution.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Solution represetation class implementation
//============================================================================

#include "../include/solution.h"

solution::solution() : cost(MAX_DOUBLE) {}

solution::solution( instance& _spp ) {
	spp = _spp;
	elems_represented = vector< unsigned >(spp.get_n());
	feasible = covered = false;
	bar_s = spp.get_n();
	cost = bar_s * spp.get_big_M();
}

solution::solution( solution& _sol ) {
	this->spp = _sol.get_instance();
	this->elems_represented = vector< unsigned >(_sol.get_elems_represented());
	this->sets_selected = vector< unsigned >(_sol.get_sets_selected());
	this->cost = _sol.get_cost();
	this->covered = _sol.is_covered();
	this->feasible = _sol.is_feasible();
	this->bar_s = _sol.get_bar_s();
}

solution::solution( instance& _spp, vector< unsigned > _elems, vector< unsigned > _sets, double _cost, unsigned _bar_s, bool _covered, bool _feasible ) : cost(_cost), bar_s(_bar_s), covered(_covered), feasible(_feasible) {
	spp = _spp;
	elems_represented = _elems;
	sets_selected = _sets;
}

solution::~solution() { }

void solution::set_instance( instance& _spp ) { spp = _spp; }

void solution::set_elems_represented( const vector< unsigned >& _elems_represented ) { elems_represented = _elems_represented; }

void solution::set_sets_selected( const vector< unsigned >& _sets_selected ) { sets_selected = _sets_selected; }

void solution::set_cost( double _cost ) { cost = _cost; }

void solution::set_bar_s( unsigned _bar_s ) { bar_s = _bar_s; }

void solution::set_covered( bool _covered ) { covered = _covered; }

void solution::set_feasible( bool _feasible ) { feasible = _feasible; }

instance& solution::get_instance() { return spp; }

const vector< unsigned >& solution::get_elems_represented() const { return elems_represented; }

const vector< unsigned >& solution::get_sets_selected() const { return sets_selected; }

double solution::get_cost() { return cost; }

unsigned solution::get_bar_s() { return bar_s; }

double solution::evaluate() {
	// TODO

	return cost;
}

bool solution::is_covered() { return covered; }

bool solution::is_feasible() { return feasible; }

void solution::remove_subset( unsigned subset ) {
	unsigned n = spp.get_n();
	unsigned big_M = spp.get_big_M();
	vector < unsigned > weights = spp.get_weights();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	// Reducing costs, represetation and checking cover flags
	for(unsigned i = 0; i < subsets[ subset - 1 ].size(); i++) {
		if(elems_represented[ subsets[ subset - 1 ][i] - 1 ] >= 2) {
			cost -= big_M;
			bar_s--;
		} else if(elems_represented[ subsets[ subset - 1 ][i] - 1 ] == 1) {
			cost += big_M;
			bar_s++;
			covered = false;
		}
		elems_represented[ subsets[ subset - 1 ][i] - 1 ]--;
	}
	feasible = !bar_s;
	cost -= weights[ subset - 1 ];
	sets_selected.erase(find(sets_selected.begin(), sets_selected.end(), subset));
}

void solution::insert_subset( unsigned subset ) {
	unsigned n = spp.get_n();
	unsigned big_M = spp.get_big_M();
	vector < unsigned > weights = spp.get_weights();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	for(unsigned i = 0; i < subsets[ subset - 1].size(); i++) {
		if(elems_represented[ subsets[ subset - 1][i] - 1 ] >= 1) {
			cost += big_M;
			bar_s++;
		} else if(elems_represented[ subsets[ subset - 1][i] - 1 ] == 0) {
			cost -= big_M;
			bar_s--;
		}
		elems_represented[ subsets[ subset - 1][i] - 1 ]++;
	}
	feasible = !bar_s;
	if(feasible) covered = true;
	else {
		for(unsigned i = 0; i < n; i++)
			if(!elems_represented[i]) {
				covered = false;
				break;
			}
	}
	cost += weights[ subset - 1 ];
	sets_selected.push_back( subset - 1 );
}

void solution::show_data() {
	if(feasible)
		printf("SOLUTION DATA ----------------- FEASIBLE \n");
	else
		printf("SOLUTION DATA --------------- INFEASIBLE \n");
	printf("COST: %.2lf ---- BAR_S: %2d\n", cost, bar_s);
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
