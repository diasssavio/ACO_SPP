//============================================================================
// Name        : aco.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Ant Colony Optimisation class implementation
//============================================================================

#include "../include/aco.h"

aco::aco( instance& _spp, unsigned _it, double _alpha, double _beta, double _big_Q, logger* _logs ) : max_it(_it), alpha(_alpha), beta(_beta), big_Q(_big_Q) {
	this->spp = _spp;
	this->logs = _logs;

	unsigned n = spp.get_n();
	unsigned m = spp.get_m();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	// Ant Colony
	this->ants = vector< solution >(n);

	// Initializing pheromones and heuristics informations
	pheromones = vector< vector < double > >(m + 1);
	heuristics = vector< vector < double > >(m + 1);

	#if LOGS == true
		printf("HEURISTICS INFO ------------------------\n");
		for(unsigned i = 0; i <= m; i++) {
			pheromones[i] = vector < double >(m + 1);
			heuristics[i] = vector < double >(m + 1);
			for(unsigned j = 0; j <= m; j++) {
				pheromones[i][j] = 1.0;
				heuristics[i][j] = -1.0;
				printf("%.2lf ", heuristics[i][j]);
			}
			printf("\n");
		}
		printf("----------------------------------------\n");
	#endif

	// Generating neighborhood list based on every element from the set
	neighbors = vector< vector< unsigned> >(n);
	for(unsigned i = 0; i < n; i++) {
		vector< unsigned > adj;
		for(unsigned j = 0; j < m; j++)
			if(find(subsets[j].begin(), subsets[j].end(), i + 1) != subsets[j].end())
				adj.push_back(j);
		neighbors[i] = adj;
	}

	#if LOGS == true
		printf("NEIGHBORS LIST --------------------------\n");
		for(unsigned i = 0; i < n; i++) {
			for(unsigned j = 0; j < neighbors[i].size(); j++)
				printf("%4d", neighbors[i][j]);
			printf("\n");
		}
		printf("----------------------------------------\n");
	#endif
}

aco::~aco() { }

double aco::get_heuristic( unsigned i, unsigned j ) {
	if(heuristics[i][j] >= 1e-05) return heuristics[i][j];
	if(i == j) heuristics[i][j] = 0.0;
	else if(!i) {
		heuristics[i][j] = spp.get_weight(j - 1) / (double)spp.get_subset(j - 1).size();
		heuristics[i][j] = 1.0 / heuristics[i][j];
	} else if(!j) {
		heuristics[i][j] = spp.get_weight(i - 1) / (double)spp.get_subset(i - 1).size();
		heuristics[i][j] = 1.0 / heuristics[i][j];
	} else {
		set< unsigned > union_set(spp.get_subset(i - 1).begin(), spp.get_subset(i - 1).end());
		union_set.insert(spp.get_subset(j - 1).begin(), spp.get_subset(j - 1).end());
		heuristics[i][j] = (spp.get_weight(i - 1) + spp.get_weight(j - 1)) / (double)union_set.size();
		heuristics[i][j] = 1.0 / heuristics[i][j];
	}
	return heuristics[i][j];
}

solution& aco::execute() {
	unsigned n = spp.get_n();
	unsigned m = spp.get_m();
	unsigned big_M = spp.get_big_M();
	vector < unsigned > weights = spp.get_weights();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	unsigned it_count = 0;
	while( it_count < max_it ) {
		// TODO Generating every ant solution
		for(unsigned i = 0; i < n; i++) {
			vector< unsigned > adj = neighbors[i];
		}

		// TODO Updating pheromones

		++it_count;
	}

	return best;
}
