//============================================================================
// Name        : neighborhoods.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Federal University of Rio de Janeiro
// Description : Neighborhoods class implementation
//============================================================================

#include "../include/neighborhoods.h"

int myrandom( unsigned i ) { return genrand_int32() % i; }

neighborhoods::neighborhoods( instance& _spp, logger* _logs) {
	this->spp = _spp;
	this->log_system = _logs;
}

neighborhoods::~neighborhoods() { }

solution neighborhoods::swap11( solution& p_sol ) {
	unsigned n = spp.get_n();
	unsigned big_M = spp.get_big_M();
	vector < unsigned > weights = spp.get_weights();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	vector< unsigned > sets = p_sol.get_sets_selected();

	// Evaluating all posible swaps
	unsigned i_swap = 0, j_swap = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned i = 0; i < sets.size(); i++)
		for(unsigned j = 0; j < subsets.size(); j++) {
			// If j is already in the solution, skip it.
			if(find(sets.begin(), sets.end(), j + 1) != sets.end()) continue;

			// Calculating the current cost for the swap change:
			vector< unsigned > elems(p_sol.get_elems_represented());
			double cost = p_sol.get_cost();
			// -- Cost for removing sets[i]
			cost -= weights[ sets[i] - 1 ];
			for(unsigned k = 0; k < subsets[ sets[i] - 1 ].size(); k++) {
				if(elems[ subsets[ sets[i] - 1 ][k] - 1 ] >= 2)
					cost -= big_M;
				else if(elems[ subsets[ sets[i] - 1 ][k] - 1 ] == 1)
					cost += big_M;
				elems[ subsets[ sets[i] - 1 ][k] - 1 ]--;
			}

			// -- Cost for adding set j
			cost += weights[j];
			for(unsigned k = 0; k < subsets[j].size(); k++) {
				if(elems[ subsets[j][k] - 1 ] >= 1)
					cost += big_M;
				else if(elems[ subsets[j][k] - 1 ] == 0)
					cost -= big_M;
				elems[ subsets[j][k] - 1 ]++;
			}

			// Checking whether the cost is satisfactory.
			if(cost < current_cost) {
				i_swap = i;
				j_swap = j;
				current_cost = cost;
			}
		}

	// If a better solution cost was found, make the swap.
	if(i_swap != j_swap) {
		solution neighbor(p_sol);
		neighbor.remove_subset(sets[i_swap]);
		neighbor.insert_subset(j_swap + 1);
		#if LOGS == true
			printf("Swapped %d <-> %d\n", sets[i_swap], j_swap + 1);
			printf("Previous cost / New cost: %.2lf <-> %.2lf\n", p_sol.get_cost(), current_cost);
			neighbor.show_data();
		#endif
		// getchar();
		return neighbor;
	}

	return p_sol;
}

solution neighborhoods::swap22( solution& p_sol ) {
	unsigned n = spp.get_n();
	unsigned big_M = spp.get_big_M();
	vector < unsigned > weights = spp.get_weights();
	vector< vector < unsigned > > subsets = spp.get_subsets();

	vector< unsigned > elems(p_sol.get_elems_represented());
	vector< unsigned > sets(p_sol.get_sets_selected());

	// Evaluating all posible swaps
	unsigned i_swap = 0, j_swap = 0;
	double current_cost = p_sol.get_cost();
	for(unsigned i = 0; i < sets.size(); i++)
		for(unsigned j = 0; j < subsets.size(); j++) {
			// If j is already in the solution, skip it.
			if(find(sets.begin(), sets.end(), j + 1) != sets.end()) continue;

			// Calculating the current cost for the swap change:
			double cost = p_sol.get_cost();
			// -- Cost for removing sets[i]
			cost -= weights[ sets[i] - 1 ];
			for(unsigned k = 0; k < subsets[ sets[i] - 1 ].size(); k++)
				if(elems[ subsets[ sets[i] - 1 ][k] - 1 ] >= 2)
					cost -= big_M;
				else if(elems[ subsets[ sets[i] - 1 ][k] - 1 ] == 1)
					cost += big_M;

			// -- Cost for adding set j
			cost += weights[j];
			for(unsigned k = 0; k < subsets[j].size(); k++)
				if(elems[ subsets[j][k] - 1 ] >= 1)
					cost += big_M;
				else if(elems[ subsets[j][k] - 1 ] == 0)
					cost -= big_M;

			// Checking whether the cost is satisfactory.
			if(cost < current_cost) {
				i_swap = i;
				j_swap = j;
				current_cost = cost;
			}
		}

	// If a better solution cost was found, make the swap.
	if(i_swap != j_swap) {
		#if LOGS == true
			printf("Swapped %d <-> %d\n", sets[i_swap], j_swap + 1);
		#endif
		solution neighbor(p_sol);
		neighbor.remove_subset(sets[i_swap]);
		neighbor.insert_subset(j_swap + 1);
		return neighbor;
	}

	return p_sol;
}

solution& neighborhoods::execute( solution& p_sol ) {
	// Setting neighborhood random order
	unsigned n_neighborhoods = 1;
	NL = vector< unsigned >(n_neighborhoods);
	for(unsigned i = 0; i < n_neighborhoods; i++)
		NL[i] = i;
	random_shuffle(NL.begin(), NL.end(), myrandom);

	// cout << "Executing inner_RVND: ";
	// for(unsigned i = 0; i < 8; i++)
	// 	printf("%d ", i_NL[i]);
	// printf("\n");

	// Executing inner_RVND based on neighborhood order
	best = p_sol;
	solution aux;
	unsigned i = 0;
	while(i < n_neighborhoods) {
		#if LOGS == true
			printf("    ");
		#endif
		switch(NL[i]) {
			case 0:
				#if LOGS == true
					cout << "Trying swap_11...\n";
				#endif
				aux = swap11(best);
				break;
			case 1:
				#if LOGS == true
					cout << "Trying swap_22...\n";
				#endif
				aux = swap22(best);
				break;
			}
		// If neighborhood find a better solution, the NL is updated
		if(aux.get_cost() < best.get_cost()) {
			// log_system->make_general_log(NL[i] + 9, best.get_cost(), aux.get_cost());
			best = aux;
			i = 0;
		} else i++;
	}

	return best;
}
