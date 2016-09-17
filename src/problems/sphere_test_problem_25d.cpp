//
// Created by Malcolm Joseland on 19/08/2016.
//

#include "sphere_test_problem_25d.h"

ParabolaTestProblem25d::ParabolaTestProblem25d() :
		Problem("Minimise 25-Dimension parabola", 25, -100.0, 100.0, true) { }

REAL ParabolaTestProblem25d::getOutput(const vector<REAL> &dimension_values) const {
	REAL output = 0.0;

	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		output += pow(dimension_values[i], 2);
	}

	return output;
}
