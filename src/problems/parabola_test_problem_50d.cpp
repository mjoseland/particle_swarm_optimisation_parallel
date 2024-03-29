//
// Created by Malcolm Joseland on 19/08/2016.
//

#include "parabola_test_problem_50d.h"

ParabolaTestProblem50d::ParabolaTestProblem50d() :
		Problem("Minimise 50-Dimemsion parabola", 50, -100.0, 100.0, true) { }

REAL ParabolaTestProblem50d::getOutput(const vector<REAL> &dimension_values) const {
	REAL output = 0.0;

	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		output += pow(dimension_values[i], 2);
	}

	return output;
}
