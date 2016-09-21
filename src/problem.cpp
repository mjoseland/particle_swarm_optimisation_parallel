//
// Created by Malcolm Joseland on 1/08/2016.
//

#include "problem.h"

Problem::Problem(string name, DIMENSION n_dimensions, double lower_bound, double upper_bound, bool minimum_optimal) :
			name_(name), num_dimensions_(n_dimensions), lower_bound_(lower_bound), upper_bound_(upper_bound),
			minimum_optimal_(minimum_optimal) { }

Problem::~Problem() { }

bool Problem::outputMoreOptimal(REAL initial_output, REAL compare_output) const {
	// return true if initial output is smaller than compare output
	if (minimum_optimal_) {
		return compare_output < initial_output;
	}

	// return true if initial output is greater than compare output
	return compare_output > initial_output;
}

