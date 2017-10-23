//============================================================================
// Name        : logger.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal Fluminense
// Description : Logger class implementation
//============================================================================

#include "../include/logger.h"

logger::logger() {
	n_found_sol = 0;
	average_gain = 0.0;
	g_n_found_sol = new unsigned[17];
	g_average_gain = new double[17];

	for(unsigned i = 0; i < 17; i++) {
		g_n_found_sol[i] = 0;
		g_average_gain[i] = 0.0;
	}
}

logger::logger( FWChrono& _timer ) {
	this->timer = _timer;

	n_found_sol = 0;
	average_gain = 0.0;
	g_n_found_sol = new unsigned[17];
	g_average_gain = new double[17];

	for(unsigned i = 0; i < 17; i++) {
		g_n_found_sol[i] = 0;
		g_average_gain[i] = 0.0;
	}
}

logger::~logger() { }

void logger::make_log( double cost ) {
	it_log.push_back(make_pair(cost, ++iteration));
	times.push_back(((double) timer.getMilliSpan() / 1000));
}

void logger::make_individual_log( double initial, double improved ) {
	n_found_sol++;
	average_gain += (initial - improved) / initial;
}

void logger::make_general_log( unsigned i, double initial, double improved ) {
	g_n_found_sol[i]++;
	g_average_gain[i] += (initial - improved) / initial;
}

void logger::print_log() {
	printf("MULTI-START ITERATION LOGS:\n");
	for(unsigned i = 0; i < it_log.size(); i++)
		printf("%d: Cost: %.2lf\tTime:%.2lf\n", it_log[i].second, it_log[i].first, times[i]);
}

double logger::get_individual_average() {
	if(n_found_sol)
		average_gain = 100 * (average_gain / n_found_sol);
	else average_gain = (double) n_found_sol;

	return average_gain;
}

double* logger::get_average() {
	for(unsigned i = 0; i < 17; i++)
		if(g_n_found_sol[i])
			g_average_gain[i] = 100 * (g_average_gain[i] / g_n_found_sol[i]);
		else
			g_average_gain[i] = (double) g_n_found_sol[i];

	return g_average_gain;
}

double logger::best_time() {
  double min_time = 0.0;
	for(unsigned i = 0; i < it_log.size() - 1; i++) {
		if(it_log[i].first == it_log[ it_log.size() - 1 ].first && min_time == 0.0)
			min_time = times[i];
	}

  return min_time;
}
