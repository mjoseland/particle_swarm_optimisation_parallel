//
// Created by Malcolm Joseland on 20/09/2016.
//

#include "problem_optimiser.h"

void ProblemOptimiser::optimiseProblems(int job_count, int rank) {
	int next_problem_id;
	int rank;

	// find rank and the index of the first problem to solve
	// if there are more mpi processes than jobs and this is one of the excess processes, no problems will
	// be optimised by this process
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	next_problem_id = rank - 1;

	Problem *next_problem;
	MPI_Status status;

	while (next_problem_id < problem_count) {
		cout << "rank next_problem_id num_threads: " << rank << ' ' << next_problem_id << ' ' << omp_get_num_threads();

		// solve problem in parallel

		char problem_name[] = to_string(next_problem_id).c_str;
		DIMENSION dimension_count = 1;
		vector<REAL> dim_vals({0.0});
		REAL output = 1.0;

		// send name, dimension count, dimension values, and output to control process
		MPI_Send(&problem_name, 128, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD);
		MPI_Send(&dimension_count, 1, MPI_UNSIGNED_LONG, 0, MPI_ANY_TAG, MPI_COMM_WORLD);
		MPI_Send(&dim_vals, dimension_count, MPI_REAL, 0, MPI_ANY_TAG, MPI_COMM_WORLD);
		MPI_Send(&output, 1, MPI_REAL, 0, MPI_ANY_TAG, MPI_COMM_WORLD);


		// receive next_problem
		// if there are no more problems, the controller node will send problem_count as the next job ID
		MPI_Recv(&next_problem_id, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	}
}

/* ---------------------- private functions -------------------------*/

void ProblemOptimiser::optimiseProblem(Problem *problem) {
	Swarm test_swarm(problem);

	test_swarm.iterateNTimes(NUM_ITERATIONS);
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


