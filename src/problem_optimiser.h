//
// Created by Malcolm Joseland on 20/09/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_PARALLEL_PROBLEMSOLVER_H
#define PARTICLE_SWARM_OPTIMISATION_PARALLEL_PROBLEMSOLVER_H

#include <iostream>

#include "swarm.h"
#include "problem.h"

#include "problems/parabola_test_problem_5d.h"
#include "problems/parabola_test_problem_25d.h"
#include "problems/parabola_test_problem_50d.h"
#include "problems/regression_problem.h"

#define NUM_ITERATIONS 2000

using namespace std;

class ProblemOptimiser {
public:
	ProblemOptimiser() {}
	~ProblemOptimiser() {}

	// initialises and optimises all required problems
	void optimiseProblems();

private:
	void optimiseProblem(Problem *problem);
	Problem *getInitialisedProblem(size_t problem_id);
};


#endif //PARTICLE_SWARM_OPTIMISATION_PARALLEL_PROBLEMSOLVER_H
