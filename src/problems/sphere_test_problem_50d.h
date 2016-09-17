//
// Created by Malcolm Joseland on 19/08/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_50D_H
#define PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_50D_H

#include <cmath>

#include "problem.h"

using namespace std;

// Finds the minimal point in a 50-dimensional parabola
class ParabolaTestProblem50d : public Problem {
public:
	ParabolaTestProblem50d();

	// find the sum of the value at all dimensions squared (not sigma value)
	REAL getOutput(const vector<REAL> &dimension_values) const;
};


#endif //PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_50D_H
