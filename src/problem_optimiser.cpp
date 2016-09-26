//
// Created by Malcolm Joseland on 20/09/2016.
//

#include "problem_optimiser.h"

void ProblemOptimiser::optimiseProblems(int rank) {
	int next_problem_id;

	// find rank and the index of the first problem to solve
	// if there are more mpi processes than jobs and this is one of the excess processes, no problems will
	// be optimised by this process
	next_problem_id = rank - 1;

	Problem *current_problem;
	MPI_Status status;

	while (next_problem_id < PROBLEM_COUNT) {
		// solve problem in parallel
		current_problem = getInitialisedProblem(next_problem_id);

		Swarm swarm(current_problem);
		swarm.iterateNTimes(NUM_ITERATIONS);

		const string problem_name = current_problem->name_;
		//unsigned long problem_name_len = current_problem->name_.size();
		DIMENSION num_dimensions = current_problem->num_dimensions_;
		const vector<REAL> &optimised_solution = *(swarm.getBestSolution());
		REAL output = swarm.getBestSolutionOutput();

		// send name, dimension count, dimension values, and output to control process
		//MPI_Send(&problem_name_len, 1, MPI_UNSIGNED_LONG, 0, 1, MPI_COMM_WORLD);
		MPI::COMM_WORLD.Send(problem_name.c_str(), problem_name.length(), MPI::CHAR, 0, 1);
		MPI::COMM_WORLD.Send(&num_dimensions, 1, MPI::UNSIGNED_LONG, 0, 1);
		MPI::COMM_WORLD.Send(&optimised_solution.front(), num_dimensions, MPI::DOUBLE, 0, 1);
		MPI::COMM_WORLD.Send(&output, 1, MPI::DOUBLE, 0, 1);


		// receive ID of next problem
		// if there are no more problems, the controller node will send problem_count as the next job ID
		MPI_Recv(&next_problem_id, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	}
}

/* ---------------------- private functions -------------------------*/

Problem *ProblemOptimiser::getInitialisedProblem(int problem_id) {
	switch (problem_id) {
		case 0:
			// find minimal point in a 5 dimesion parabola, search space -100.0 to 100.0
			return new ParabolaTestProblem5d();
		case 1:
			// find minimal point in a 25 dimesion parabol, search space -100.0 to 100.0
			return new ParabolaTestProblem25d();
		case 2:
			// find minimal point in a 50 dimesion parabol, search space -100.0 to 100.0
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


