//============================================================================
// Name        : aco.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Ant Colony Optimisation class implementation
//============================================================================

#include "../include/aco.h"

aco::aco( instance& _spp, unsigned _it, double _alpha, double _beta, double _rho, double _big_Q, logger* _logs, mt19937& _generator ) : max_it(_it), alpha(_alpha), beta(_beta), rho(_rho), big_Q(_big_Q) {
	this->spp = _spp;
	this->logs = _logs;
	this->generator = _generator;
	this->best = NULL;

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
		double partition_sum = spp.get_weight(i - 1) + spp.get_weight(j - 1);
		heuristics[i][j] = (partition_sum + spp.get_big_M() * intersec_size) / (double)union_set.size();
		// heuristics[i][j] = (partition_sum + partition_sum * intersec_size) / (double)union_set.size();
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
			// Calculating edges probabilities
			vector< double > probs(neighbors[k].size());
			for(unsigned j = 0; j < neighbors[k].size(); j++)
				probs[j] = pow(pheromones[origin][ neighbors[k][j] + 1 ], alpha) * pow(get_heuristic(origin, neighbors[k][j] + 1), beta);

			// Choosing which set to add (edge to take)
			discrete_distribution< int > distribution(probs.begin(), probs.end());
			origin = neighbors[k][ distribution(generator) ] + 1;
			cost += weights[origin - 1];
			sets.push_back(origin);

			// Updating covered elements list based on set taken
			for(unsigned j = 0; j < subsets[origin - 1]. size(); j++) elems[ subsets[origin - 1][j] - 1 ]++;
			for(k = 0; k < n; k++)
				if(!elems[k])	break;
		}

		// Saving constructed solution in ant pool
		unsigned bar_s = 0;
		for(unsigned j = 0; j < n; j++)
			bar_s += elems[j] - 1;
		cost += big_M * bar_s;
		ants[i] = solution(spp, elems, sets, cost, bar_s, true, !bar_s);

		is_best(&ants[i]);
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

void aco::feasibility_heuristic() {
	unsigned n = spp.get_n();
	unsigned m = spp.get_m();
	vector < unsigned > weights = spp.get_weights();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	// Trying to make every unfeasible solution feasible
	for(unsigned k = 0; k < n; k++) {
		if(ants[k].is_feasible()) continue;
		vector< unsigned > sets(ants[k].get_sets_selected());

		// Step 1: Remove subsets of over-covered elements
		while(sets.size() > 0) {
			vector< unsigned > elems = ants[k].get_elems_represented();
			unsigned j = genrand_int32() % sets.size();

			// Verifying whether the selected subset makes any infeasibility
			bool makes_infeasible = false;
			for(unsigned i = 0; i < subsets[ sets[j] - 1 ].size(); i++)
				if(elems[ subsets[ sets[j] - 1 ][i] - 1 ] >= 2) {
					makes_infeasible = true;
					break;
				}
			// Removing subset if positive
			if(makes_infeasible)
				ants[k].remove_subset(sets[j]);

			sets.erase(sets.begin() + j);
		}

		// Step 2: Add subsets as long as it doesn't over-cover any element
		// Building initial sets for heuristic
		vector< unsigned > elems = ants[k].get_elems_represented();
		set< unsigned > set_U;
		for(unsigned i = 0; i < n; i++)
			if(!elems[i])
				set_U.insert(i + 1);
		vector< unsigned > set_V(set_U.begin(), set_U.end());

		// Trying to add subsets based on under-covered elements
		while(set_V.size() > 0) {
			unsigned i = genrand_int32() % set_V.size();
			unsigned _i = set_V[i] - 1;
			set_V.erase(set_V.begin() + i);

			// Checking the minimum subset which covers uncovered elements only
			int j = -1;
			double s_value = MAX_DOUBLE;
			for(unsigned y = 0; y < neighbors[_i].size(); y++) {
				vector< unsigned > _subset = subsets[ neighbors[_i][y] ];
				bool is_subset = true;
				if(_subset.size() > set_U.size()) continue;
				for(unsigned x = 0; x < _subset.size(); x++)
					if(find(set_U.begin(), set_U.end(), _subset[x]) == set_U.end()) {
						is_subset = false;
						break;
					}

				if(is_subset) { // if neighbors[_i][y] \subseteq set_U
					double cost = (double) weights[ neighbors[_i][y] ] / (double) _subset.size();
					if(cost < s_value) {
						j = neighbors[_i][y];
						s_value = cost;
					}
				}
			}

			// Found a subset, adding it to the solution
			if(j >= 0) {
				ants[k].insert_subset(j + 1);
				for(unsigned x = 0; x < subsets[j].size(); x++) {
					set_U.erase(subsets[j][x]);
					vector< unsigned >::iterator it = find(set_V.begin(), set_V.end(), subsets[j][x]);
					if(it != set_V.end())
						set_V.erase(it);
				}
			}
		}

		is_best(&ants[k]);
	}
}

void aco::is_best( solution* candidate ) {
	if(!best) best = new solution(*candidate);
	else if(!best->is_feasible()) {
		if(candidate->is_feasible() || (best->get_cost() > candidate->get_cost()))
			best = new solution(*candidate);
	} else if(candidate->is_feasible() && (best->get_cost() > candidate->get_cost()))
			best = new solution(*candidate);
}

solution* aco::run() {
	unsigned n = spp.get_n();
	unsigned m = spp.get_m();

	unsigned it_count = 0;
	while( it_count < max_it ) {
		#if LOGS == true
			printf("ITERATION #%2d --------------------------\n", it_count + 1);
		#endif

		// Generating every ant solution
		generate_ants();

		// Running feasibility heuristic
		feasibility_heuristic();

		#if LOGS == true
			for(unsigned i = 0; i < n; i++) {
				printf("Ant #%d\n", i + 1);
				ants[i].show_data();
			}
		#endif

		// Updating pheromones
		update_pheromones();
		logs->make_log(best->get_cost());
		++it_count;
	}

	return best;
}
