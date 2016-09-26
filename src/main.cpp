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
		ProblemOptimiser::optimiseProblems(rank);
	}

	MPI_Finalize();


	return 0;
}

void manageMpiJobs(int rank) {
	// get the size of the group of MPI processes
	int num_processes;
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

	// print the run description
	cout << "Optimising " << PROBLEM_COUNT << " problems for " << NUM_ITERATIONS << " iterations per problem using "
				<< (num_processes - 1) << " MPI processes" << endl;

	// each process will self-allocate the job with ID = rank - 1, unless that ID is >= num_initial_allocations
	int next_job = num_processes - 1;

	DIMENSION num_problem_dimensions;
	vector<REAL> optimal_values;
	REAL output;

	MPI::Status status;
	// receive problem optimisation output and send the `
	for (int i = 0; i < PROBLEM_COUNT; i++) {
		// receive the name of the optimised problem
		//MPI_Recv(&problem_name_len, 1, MPI_UNSIGNED_LONG, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
		MPI::COMM_WORLD.Probe(MPI::ANY_SOURCE, 1, status);
		int cstr_len = status.Get_count(MPI::CHAR);
		char *problem_name_cstr = new char[cstr_len + 1];
		MPI::COMM_WORLD.Recv(problem_name_cstr, cstr_len, MPI::CHAR, status.Get_source(), 1, status);

		problem_name_cstr[cstr_len] = '\0';

		// get the optimal values for each dimension and the output of those values
		MPI::COMM_WORLD.Recv(&num_problem_dimensions, 1, MPI::UNSIGNED_LONG, status.Get_source(), 1);
		optimal_values.resize(num_problem_dimensions);
		MPI::COMM_WORLD.Recv(&optimal_values.front(), num_problem_dimensions, MPI::DOUBLE, status.Get_source(), 1);
		MPI::COMM_WORLD.Recv(&output, 1, MPI::DOUBLE, status.Get_source(), 1);


		// send the id of the next job back to the process, the id may be == PROBLEM_COUNT, which
		// causes the receiving process to terminate
		MPI::COMM_WORLD.Send(&next_job, 1, MPI_INT, status.Get_source(), 1);

		// print the name and optimal solution to the problem
		//string problem_name (problem_name_cstr);

		cout << endl;
		cout << "Optimal solution for: " << problem_name_cstr << " (" << num_problem_dimensions << " dimensions)" << endl;

		cout << "Optimal values for each dimension: " << endl;
		for (DIMENSION i = 0; i < num_problem_dimensions - 1; i++) {
			cout << optimal_values[i] << ", ";
		}
		cout << optimal_values[num_problem_dimensions - 1] << endl;

		cout << "Output: " << output << endl;

		next_job = min(next_job + 1, PROBLEM_COUNT);
	}
}


