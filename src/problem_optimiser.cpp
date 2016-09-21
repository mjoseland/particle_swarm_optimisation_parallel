//
// Created by Malcolm Joseland on 20/09/2016.
//

#include "problem_optimiser.h"

void ProblemOptimiser::optimiseProblems() {
	for (size_t i = 0; i < 10; i++) {
		auto problem_ptr = getInitialisedProblem(i);
		optimiseProblem(problem_ptr);
	}
}

/* ---------------------- private functions -------------------------*/

void ProblemOptimiser::optimiseProblem(Problem *problem) {
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

Problem *ProblemOptimiser::getInitialisedProblem(size_t problem_id) {
	switch (problem_id) {
		case 0:
			// find minimal point in a 5 dimesion parabola
			return new ParabolaTestProblem5d();
		case 1:
			// find minimal point in a 25 dimesion parabola
			return new ParabolaTestProblem25d();
		case 2:
			// find minimal point in a 50 dimesion parabola
			return new ParabolaTestProblem50d();
		case 3:
			return new RegressionProblem("auto_mpg.txt", 5, -10.0, 10.0,
										vector<bool>({false, false, false, false, false, false, true, true}), 0, 8);
		case 4:
			return new RegressionProblem("breast_cancer_wisconsin.txt", 9, -0.5, 0.5,
										vector<bool>({true, false, false, false, false, false, false, false, false,
										false, false}), 10, 11);
		case 5:
			return new RegressionProblem("concrete.txt", 8, -1.0, 1.0,
										vector<bool>({false, false, false, false, false, false, false, false, false}),
										8, 9);
		case 6:
			return new RegressionProblem("forestfires.txt", 8, -1.5, 1.5,
										vector<bool>({true, true, true, true, false, false, false, false, false, false,
										false, false, false}), 12, 13);
		case 7:
			return new RegressionProblem("housing.txt", 12, -1.0, 1.0,
										vector<bool>({false, false, false, true, false, false, false, false, false, false,
										false, false, false, false}), 13, 14);
		case 8:
			return new RegressionProblem("wine_quality_red.txt", 11, -1.0, 1.0,
										 vector<bool>({false, false, false, false, false, false, false, false, false,
										false, false, false}), 11, 12);
		case 9:
			return new RegressionProblem("wine_quality_white.txt", 11, -1.0, 1.0,
										vector<bool>({false, false, false, false, false, false, false, false, false,
										false, false, false}), 11, 12);
		default:
			return nullptr;
	}

}


