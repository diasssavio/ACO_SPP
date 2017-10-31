//============================================================================
// Name        : aco.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Ant Colony Optimisation class implementation
//============================================================================

#include "../include/aco.h"

aco::aco( instance& _spp, unsigned _it, double _alpha, double _beta, double _rho, double _big_Q, logger* _logs, default_random_engine& _generator ) : max_it(_it), alpha(_alpha), beta(_beta), rho(_rho), big_Q(_big_Q) {
	this->spp = _spp;
	this->logs = _logs;
	this->generator = _generator;

	unsigned n = spp.get_n();
	unsigned m = spp.get_m();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	// Ant Colony
	this->ants = vector< solution >(n);

	// Initializing pheromones and heuristics informations
	pheromones = vector< vector < double > >(m + 1);
	heuristics = vector< vector < double > >(m + 1);
	for(unsigned i = 0; i <= m; i++) {
		pheromones[i] = vector< double >(m + 1);
		heuristics[i] = vector< double >(m + 1);
		for(unsigned j = 0; j <= m; j++) {
			pheromones[i][j] = 1.0;
			heuristics[i][j] = -1.0;
		}
	}

	// Generating neighborhood list based on every element from the set
	neighbors = vector< vector< unsigned> >(n);
	for(unsigned i = 0; i < n; i++) {
		vector< unsigned > adj;
		for(unsigned j = 0; j < m; j++)
			if(find(subsets[j].begin(), subsets[j].end(), i + 1) != subsets[j].end())
				adj.push_back(j);
		neighbors[i] = adj;
	}

	// #if LOGS == true
	// 	printf("NEIGHBORS LIST --------------------------\n");
	// 	for(unsigned i = 0; i < n; i++) {
	// 		for(unsigned j = 0; j < neighbors[i].size(); j++)
	// 			printf("%4d", neighbors[i][j]);
	// 		printf("\n");
	// 	}
	// 	printf("----------------------------------------\n");
	// #endif
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
		double intersec_size = spp.get_subset(i - 1).size() + spp.get_subset(j - 1).size() - union_set.size();
		heuristics[i][j] = (spp.get_weight(i - 1) + spp.get_weight(j - 1) + spp.get_big_M() * intersec_size) / (double)union_set.size();
		heuristics[i][j] = 1.0 / heuristics[i][j];
	}
	return heuristics[i][j];
}

void aco::generate_ants() {
	unsigned n = spp.get_n();
	unsigned m = spp.get_m();
	unsigned big_M = spp.get_big_M();
	vector < unsigned > weights = spp.get_weights();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	for(unsigned i = 0; i < n; i++) {
		vector< unsigned > elems(n);
		vector< unsigned > sets;
		double cost = 0.0;
		unsigned k = i, origin = 0;
		while(k < n) { // i.e. all elements are covered
			// Calculating denominator of probability equation
			// double denominator = 0.0;
			// for(unsigned j = 0; j < neighbors[k].size(); j++)
			// 	denominator += pow(pheromones[origin][ neighbors[k][j] + 1 ], alpha) * pow(get_heuristic(origin, neighbors[k][j] + 1), beta);

			// Calculating edges probabilities
			vector< double > probs(neighbors[k].size());
			for(unsigned j = 0; j < neighbors[k].size(); j++)
				probs[j] = pow(pheromones[origin][ neighbors[k][j] + 1 ], alpha) * pow(get_heuristic(origin, neighbors[k][j] + 1), beta); // denominator;

			// Choosing which set to add (edge to take)
			discrete_distribution< int > distribution(probs.begin(), probs.end());
			origin = neighbors[k][ distribution(generator) ] + 1;
			cost += weights[origin - 1];
			sets.push_back(origin);

			// Updating covered elements list based on set taken
			for(unsigned j = 0; j < subsets[origin - 1]. size(); j++) elems[ subsets[origin - 1][j] - 1 ]++;
			for(k = 0; k < n; k++)
				if(!elems[k])	break;

			// #if LOGS == true
			// 	printf("Set choosen: %d\nCurrent elems covered: ", origin);
			// 	for(unsigned j = 0; j < n; j++) printf("%4d", elems[j]);
			// 	printf("\nSets selected: ");
			// 	for(unsigned j = 0; j < sets.size(); j++) printf("%4d", sets[j]);
			// 	printf("\n");
			// #endif
		}

		// Saving constructed solution in ant pool
		unsigned bar_s = 0;
		for(unsigned j = 0; j < n; j++)
			bar_s += elems[j] - 1;
		cost += big_M * bar_s;
		ants[i] = solution(spp, elems, sets, cost, true, !bar_s);

		#if LOGS == true
			printf("Ant #%d\n", i + 1);
			ants[i].show_data();
		#endif
	}
}

void aco::update_pheromones() {
	unsigned n = spp.get_n();
	unsigned m = spp.get_m();

	// Evaporating pheromones
	for(unsigned i = 0; i <= m; i++)
		for(unsigned j = 0; j <= m; j++) {
			if(i == j) continue;
			pheromones[i][j] -= rho * pheromones[i][j];
		}

	// Incrementing the pheromones for every edge used by the ants
	for(unsigned k = 0; k < n; k++) {
		vector< unsigned > sets = ants[k].get_sets_selected();
		unsigned origin = 0;
		for(unsigned i = 0; i < sets.size(); i++) {
			pheromones[origin][ sets[i] ] += big_Q / ants[k].get_cost();
			origin = sets[i];
		}
	}
}

solution& aco::run() {
	unsigned n = spp.get_n();
	unsigned m = spp.get_m();
	unsigned big_M = spp.get_big_M();

	unsigned it_count = 0;
	while( it_count < max_it ) {
		#if LOGS == true
			printf("HEURISTICS INFO ------------------------\n");
			for(unsigned i = 0; i <= m; i++) {
				for(unsigned j = 0; j <= m; j++)
				printf("%.2lf ", heuristics[i][j]);
				printf("\n");
			}
			printf("----------------------------------------\n");
			printf("PHEROMONES INFO ------------------------\n");
			for(unsigned i = 0; i <= m; i++) {
				for(unsigned j = 0; j <= m; j++)
				printf("%.2lf ", pheromones[i][j]);
				printf("\n");
			}
			printf("----------------------------------------\n");
		#endif

		// Generating every ant solution
		generate_ants();

		// Updating pheromones
		update_pheromones();

		// getchar();
		++it_count;
	}

	return best;
}
