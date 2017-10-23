//============================================================================
// Name        : instance.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Instance data class implementation
//============================================================================

#include "../include/instance.h"

instance::instance() { }

instance::instance( unsigned _n, unsigned _m ) : n(_n), m(_m) {
	// TODO
}

instance::~instance() { }

void instance::set_n( unsigned _n ) { this->n = _n; }

void instance::set_m( unsigned _m ) { this->m = _m; }

void instance::set_weights( vector< unsigned >& _weights) { this->weights = _weights; }

void instance::set_subsets( vector< vector < unsigned > >& sets) { this->subsets = sets; }

unsigned instance::get_n() { return this->n; }

unsigned instance::get_m() { return this->m; }

const vector< unsigned >& instance::get_weights() const { return this->weights; }

const vector< vector < unsigned > >& instance::get_subsets() const { return this->subsets; }

void instance::read_data() {
	// TODO
}

void instance::read_from_file(const string& file_name) {
  // TODO
}

void instance::show_data() {
	// TODO
}
