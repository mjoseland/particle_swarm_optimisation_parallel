//
// Created by Malcolm Joseland on 17/08/2016.
//

#include <iostream>
#include <ctime>

#include "problem_optimiser.h"

//void optimiseProblem(Problem *problem);

int main() {
	clock_t begin = clock();

	auto optimiser = new ProblemOptimiser();
	optimiser->optimiseProblems();

	clock_t end = clock();

	double time_taken = double(end - begin) / CLOCKS_PER_SEC;

	cout << endl << "Execution time (seconds): " << time_taken << endl;

	return 0;
}


