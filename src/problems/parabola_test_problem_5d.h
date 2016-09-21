//
// Created by Malcolm Joseland on 4/08/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_H
#define PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_H

#include <cmath>

#include "../problem.h"

using namespace std;

// Finds the minimal point in a 5-dimensional parabola
class ParabolaTestProblem5d : public Problem {
public:
	ParabolaTestProblem5d();

	// find the sum of the value at all dimensions squared (not sigma value)
	REAL getOutput(const vector<REAL> &dimension_values) const;
	//Problem *getCopy();
};


#endif //PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_H
