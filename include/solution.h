//============================================================================
// Name        : solution.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Solution represetation class interface
//============================================================================

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <limits>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <fstream>

#include "instance.h"

using namespace std;

class solution {
private:
	// Instance data class
	instance spp;

	// Solution itself
	vector< unsigned > elems_represented; // Size: n
	vector< unsigned > sets_selected;

	// Solution cost
	double cost;

	// Flags
	bool is_covered;
	bool is_feasible;

public:
	// Constructors & destructor
	solution();
	solution( instance& );
	solution( solution& );
	virtual ~solution();

	// Setters
	void set_instance( instance& );
	void set_elems_represented( const vector< unsigned >& );
	void set_sets_selected( const vector< unsigned >& );
	void set_cost( double );
	// void set_set( unsigned );

	// Getters
	instance& get_instance();
	const vector< unsigned >& get_elems_represented() const;
	const vector< unsigned >& get_sets_selected() const;
	double get_cost();

	// Useful Methods
	void show_data();
	void show_latex( char*, char* );
	double evaluate();
  bool is_covered();
	bool is_feasible();
  // vector< unsigned > not_used();

};

#endif /* SOLUTION_H_ */
