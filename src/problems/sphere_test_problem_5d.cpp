//
// Created by Malcolm Joseland on 4/08/2016.
//

#include "sphere_test_problem_5d.h"

ParabolaTestProblem5d::ParabolaTestProblem5d() :
		Problem("Minimize 5-Dimension Parabola", 5, -100.0, 100.0, true) { }

REAL ParabolaTestProblem5d::getOutput(const vector<REAL> &dimension_values) const {
	REAL output = 0.0;

	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		output += pow(dimension_values[i], 2);
	}

	return output;
}

//Problem *ParabolaTestProblem5d::getCopy() {
	//return new ParabolaTestProblem5d();
//}