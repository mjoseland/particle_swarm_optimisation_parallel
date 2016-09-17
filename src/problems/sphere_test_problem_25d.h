//
// Created by Malcolm Joseland on 19/08/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_25D_H
#define PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_25D_H

#include <cmath>

#include "problem.h"

using namespace std;

// Finds the minimal point in a 25-dimensional parabola
class ParabolaTestProblem25d : public Problem {
public:
	ParabolaTestProblem25d();

	// find the sum of the value at all dimensions squared (not sigma value)
	REAL getOutput(const vector<REAL> &dimension_values) const;
};


#endif //PARTICLE_SWARM_OPTIMISATION_SPHERE_TEST_PROBLEM_25D_H
