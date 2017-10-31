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
	weights = vector< unsigned >(m);
	subsets = vector< vector< unsigned > >(m);
	big_M = *max_element(weights.begin(), weights.end());
}

instance::~instance() { }

void instance::set_n( unsigned _n ) { this->n = _n; }

void instance::set_m( unsigned _m ) { this->m = _m; }

void instance::set_weights( vector< unsigned >& _weights) { this->weights = _weights; }

void instance::set_subsets( vector< vector < unsigned > >& sets) { this->subsets = sets; }

unsigned instance::get_n() { return this->n; }

unsigned instance::get_m() { return this->m; }

unsigned instance::get_big_M() { return this->big_M; }

const vector< unsigned >& instance::get_weights() const { return this->weights; }

const vector< vector < unsigned > >& instance::get_subsets() const { return this->subsets; }

unsigned instance::get_weight( unsigned index ) { return this->weights[index]; }

const vector< unsigned >& instance::get_subset( unsigned index ) const { return this->subsets[index]; }

void instance::read_data() {
	scanf("%d %d", &n, &m);

	weights = vector< unsigned >(m);
	subsets = vector< vector< unsigned > >(m);

	for(int i = 0; i < m; i++) {
		unsigned aux;
		scanf("%d %d", &weights[i], &aux);
		vector< unsigned > line(aux);
		for(int j = 0; j < aux; j++)
			scanf("%d", &line[j]);
		subsets[i] = line;
	}

	big_M = *max_element(weights.begin(), weights.end());
}

void instance::read_from_file(const string& file_name) {
	ifstream _file;
  _file.open(file_name.c_str(), std::ifstream::in);

  if(_file.is_open()) {
    _file >> n >> m;

		weights = vector< unsigned >(m);
		subsets = vector< vector< unsigned > >(m);

    for(unsigned i = 0; i < m; i++) {
			unsigned aux;
			_file >> weights[i] >> aux;
			vector< unsigned > line(aux);
			for(int j = 0; j < aux; j++)
				_file >> line[j];
			subsets[i] = line;
		}

    _file.close();
  }

	big_M = *max_element(weights.begin(), weights.end());
}

void instance::show_data() {
	printf("INSTANCE DATA -------------------------- \n");
	printf("%d %d\n", n, m);
	for(int i = 0; i < m; i++) {
		printf("%d <-> ", weights[i]);
		for(int j = 0; j < subsets[i].size(); j++)
			printf("%d ", subsets[i][j]);
		printf("\n");
	}
	printf(" --------------------------------------- \n");
}
