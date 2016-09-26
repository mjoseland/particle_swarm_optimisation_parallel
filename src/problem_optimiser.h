//
// Created by Malcolm Joseland on 20/09/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_PARALLEL_PROBLEMSOLVER_H
#define PARTICLE_SWARM_OPTIMISATION_PARALLEL_PROBLEMSOLVER_H

#include <iostream>
//#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <mpi.h>

#include "swarm.h"
#include "problem.h"

#include "problems/parabola_test_problem_5d.h"
#include "problems/parabola_test_problem_25d.h"
#include "problems/parabola_test_problem_50d.h"
#include "problems/regression_problem.h"

#define NUM_ITERATIONS 10000
#define CONTROL_PROCESS_ID
#define PROBLEM_COUNT 10

using namespace std;

class ProblemOptimiser {
public:
	//ProblemOptimiser() {}
	//~ProblemOptimiser() {}

	// initialises and optimises all required problems
	static void optimiseProblems(int rank);

private:
	static Problem *getInitialisedProblem(int problem_id);
};


#endif //PARTICLE_SWARM_OPTIMISATION_PARALLEL_PROBLEMSOLVER_H
