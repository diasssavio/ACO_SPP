//============================================================================
// Name        : instance.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Instance data class interface
//============================================================================

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <vector>
#include <algorithm>
#include <cstdio>
#include <fstream>

using namespace std;

typedef vector < vector< double > > matrix_2d;

class instance {
private:
	// Primary parameter
	unsigned n; // Number of itens in the main set
	unsigned m; // Number of subsets

	// General data
	vector< unsigned > weights; // Weights of every subset
	vector< vector < unsigned > > subsets; // Itens in every subset

	unsigned big_M; // Biggest value of weights vector

public:
	// Constructors & Destructors
	instance();
	instance( unsigned, unsigned );
	virtual ~instance();

	// Setters
	void set_n( unsigned );
	void set_m( unsigned );
	void set_weights( vector< unsigned >& );
	void set_subsets( vector< vector < unsigned > >& );

	// Getters
	unsigned get_n();
	unsigned get_m();
	unsigned get_big_M();
	const vector< unsigned >& get_weights() const;
	const vector< vector < unsigned > >& get_subsets() const;
	unsigned get_weight( unsigned );
	const vector< unsigned >& get_subset( unsigned ) const;

	// Useful Methods
	void read_data();
  void read_from_file(const string&);
	void show_data();
};

#endif /* INSTANCE_H_ */
