//
// Created by Malcolm Joseland on 17/08/2016.
//

#include <iostream>
#include <omp.h>

#include "problem_optimiser.h"

void manageMpiJobs(int rank);

int main(int argc, char **argv) {
	int rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// find out if this process is meant to perform I/O for the other processes
	bool is_control_process = (rank == 0);

	// if this process is the control process, begin timing and controlling job allocation
	if (is_control_process) {
		clock_t begin = clock();

		manageMpiJobs(rank);

		clock_t end = clock();
		double time_taken = double(end - begin) / CLOCKS_PER_SEC;
		cout << endl << "Execution time (seconds): " << time_taken << endl;
	}

	// if we aren't the controller process begin asking for problems and optimising them
	if (!is_control_process) {
		ProblemOptimiser::optimiseProblems(JOB_COUNT, rank);
	}

	MPI_Finalize();


	return 0;
}

void manageMpiJobs(int rank) {
	// disable dynamic teams and set num_threads to 1 because the control node doesn't need to parallelise
	//omp_set_dynamic(0);
	//omp_set_num_threads(1);

	int num_processes;

	// get the size of the group of MPI processes
	MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);

	// each process will self-allocate the job with ID = rank - 1, unless that ID is >= num_initial_allocations
	int next_job = num_processes - 1;

	char problem_name[128];
	int num_problem_dimensions;
	vector<REAL> optimal_values;
	REAL output;

	MPI_Status status;
	// receive problem optimisation output and send the `
	for (int i = 0; i < PROBLEM_COUNT; i++) {
		// receive the name of the optimised problem
		MPI_Recv(&problem_name, 128, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

		// get the optimal values for each dimension and the output of those values
		MPI_Recv(&num_problem_dimensions, 1, MPI_LONG_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		optimal_values.resize(num_problem_dimensions);
		MPI_Recv(&optimal_values, num_problem_dimensions, MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&output, 1, MPI_FLOAT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);


		// send the id of the next job back to the process, the id may be == PROBLEM_COUNT, which
		// causes the receiving process to terminate
		MPI_Send(&next_job, 1, MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD);

		// print the name and optimal solution to the problem

		cout << endl;
		cout << "Optimal solution for " << problem_name << endl;
		cout << "Number of iterations: " << NUM_ITERATIONS << endl;

		cout << "Optimal values for each dimension: " << endl;
		for (DIMENSION i = 0; i < num_problem_dimensions - 1; i++) {
			cout << optimal_values[i] << ", ";
		}
		cout << optimal_values[num_problem_dimensions - 1] << endl;

		cout << "Output: " << output << endl;

		next_job = min(next_job + 1, PROBLEM_COUNT);
	}
}


