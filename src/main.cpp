//
// Created by Malcolm Joseland on 17/08/2016.
//

#include <iostream>
#include <ctime>

#include "swarm.h"
#include "problems/sphere_test_problem_5d.h"
#include "problems/sphere_test_problem_25d.h"
#include "problems/sphere_test_problem_50d.h"
//#include "problems/RegressionFileReader.h"
#include "problems/BrainVsBodyWeight.h"
#include "problems/PastureRentalPrice.h"

// 5, 20, and 50 dimensional versions of each test function
// 10000 iterations
// search space of -100, 100
#define NUM_ITERATIONS 100000


void optimiseProblem(Problem *problem);

int main() {
	clock_t begin = clock();

	// put all this code into a problem_solver class for MPI
	vector<Problem *> problems;
	problems.push_back(new BrainVsBodyWeight());
	problems.push_back(new PastureRentalPrice());
	problems.push_back(new ParabolaTestProblem5d());
	problems.push_back(new ParabolaTestProblem25d());
	problems.push_back(new ParabolaTestProblem50d());

	// optimise all problems
	for (auto problem: problems) {
		optimiseProblem(problem);
	}

	clock_t end = clock();

	double time_taken = double(end - begin) / CLOCKS_PER_SEC;

	cout << endl << "Execution time (seconds): " << time_taken << endl;

	return 0;
}

void optimiseProblem(Problem *problem) {
	cout << endl;
	cout << "Performing optimisation for: " << problem->name_ << endl;

	Swarm test_swarm(problem);

	test_swarm.iterateNTimes(NUM_ITERATIONS);

	cout << "Optimised solution after " << NUM_ITERATIONS << " iterations:" << endl;
	for (DIMENSION i = 0; i < problem->num_dimensions_ - 1; i++) {
		cout << (*test_swarm.getBestSolution())[i] << ", ";
	}
	cout << (*test_swarm.getBestSolution())[problem->num_dimensions_ - 1] << endl;

	cout << "Solution ouput: " << test_swarm.getBestSolutionOutput() << endl;
}

