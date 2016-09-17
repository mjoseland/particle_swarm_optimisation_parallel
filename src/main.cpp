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
void test5dSphereProblem();
void test25dSphereProblem();
void test50dSphereProblem();

int main() {
	vector<Problem *> problems;
	problems.push_back(new BrainVsBodyWeight());
	problems.push_back(new PastureRentalPrice());
	problems.push_back(new ParabolaTestProblem5d());
	problems.push_back(new ParabolaTestProblem25d());
	problems.push_back(new ParabolaTestProblem50d());

	clock_t begin = clock();

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

void test5dSphereProblem() {
	const ParabolaTestProblem5d sphere_test_problem_5d;

	cout << endl;
	cout << "Performing 5 dimensional sphere test problem..." << endl;

	Swarm test_swarm(&sphere_test_problem_5d);

	test_swarm.iterateNTimes(NUM_ITERATIONS);

	cout << "Optimised solution after " << NUM_ITERATIONS << " iterations:" << endl;

	cout << "values for each dimension: ";
	for (DIMENSION i = 0; i < sphere_test_problem_5d.num_dimensions_ - 1; i++) {
		cout << (*test_swarm.getBestSolution())[i] << ", ";
	}
	cout << (*test_swarm.getBestSolution())[sphere_test_problem_5d.num_dimensions_ - 1] << endl;

	cout << "Y value of lowest point found: " << test_swarm.getBestSolutionOutput() << endl;
}

void test25dSphereProblem() {
	cout << endl;
	cout << "Performing 25 dimensional sphere test problem..." << endl;
	const ParabolaTestProblem25d sphere_test_problem_25d;

	Swarm test_swarm(&sphere_test_problem_25d);

	test_swarm.iterateNTimes(NUM_ITERATIONS);

	cout << "Optimised solution after " << NUM_ITERATIONS << " iterations:" << endl;

	cout << "values for each dimension: ";
	for (DIMENSION i = 0; i < sphere_test_problem_25d.num_dimensions_ - 1; i++) {
		cout << (*test_swarm.getBestSolution())[i] << ", ";
		if (i == 7 || (i % 10 == 7 && i > 10)) {
			cout << endl;
		}
	}
	cout << (*test_swarm.getBestSolution())[sphere_test_problem_25d.num_dimensions_ - 1] << endl;

	cout << "Y value of lowest point found: " << test_swarm.getBestSolutionOutput() << endl;
}

void test50dSphereProblem() {
	cout << endl;
	cout << "Performing 50 dimensional sphere test problem..." << endl;

	const ParabolaTestProblem50d sphere_test_problem_50d;

	Swarm test_swarm(&sphere_test_problem_50d);

	test_swarm.iterateNTimes(NUM_ITERATIONS);

	cout << "Optimised solution after " << NUM_ITERATIONS << " iterations:" << endl;

	cout << "values for each dimension: ";
	for (DIMENSION i = 0; i < sphere_test_problem_50d.num_dimensions_ - 1; i++) {
		cout << (*test_swarm.getBestSolution())[i] << ", ";
		if (i == 7 || (i % 10 == 7 && i > 10)) {
			cout << endl;
		}
	}
	cout << (*test_swarm.getBestSolution())[sphere_test_problem_50d.num_dimensions_ - 1] << endl;

	cout << "Y value of lowest point found: " << test_swarm.getBestSolutionOutput() << endl;
}

