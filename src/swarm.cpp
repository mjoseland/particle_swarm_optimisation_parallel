//
// Created by Malcolm Joseland on 1/08/2016.
//

#include <iostream>
#include "swarm.h"

Swarm::Swarm(Problem *problem) : problem_(problem) {
	// initialise the required number of particles in the particles_ vector
	particles_.reserve(SWARM_SIZE);


	//#pragma omp parallel

	// create a copy of the problem for each thread for use by particles
	// all references to problem_ from this class will still use the originial problem but all
	// use of the problem object within particle will use a thread-unique copy of the original
	// this w
	//Problem private_problem = *problem;

	for (size_t i = 0; i < SWARM_SIZE; i++) {
		particles_.push_back(Particle(problem_, i));
	}

	// find and store the neighbours of each particle using the ring topology
	// each particle's neibhbours: i − 1 mod(SWARM_SIZE), i, i + 1 mod(SWARM_SIZE)
	neighbours_ = vector<vector<size_t>>(SWARM_SIZE, vector<size_t>(3));
	for (size_t i = 0; i < SWARM_SIZE; i++) {
		neighbours_[i][0] = (i - 1) % SWARM_SIZE;
		neighbours_[i][1] = i;
		neighbours_[i][2] = (i + 1) % SWARM_SIZE;
	}

	setParticleNeighbourhoodBests();
}

const vector<REAL> *Swarm::getBestSolution() const {
	return particles_[optimal_particle_index_].getPreviousBestPosition();
}

REAL Swarm::getBestSolutionOutput() const {
	return particles_[optimal_particle_index_].getPreviousBestOutput();
}


void Swarm::iterateNTimes(int iterate_count) {
	// perform the required number of iterations
	for (int i = 0; i < iterate_count; i++) {
		// iterate all remaining particles while retaining the global best output

		//#pragma omp parallel for
		for (size_t j = 0; j < SWARM_SIZE; j++) {
			particles_[j].iterate();
		}
		// adjust particle neighbourhood bests
		setParticleNeighbourhoodBests();

		// find and set the optimal particle index
		optimal_particle_index_ = 0;
		REAL global_best_output = particles_[0].getPreviousBestOutput();
		for (size_t j = 1; j < SWARM_SIZE; j++) {
			if (problem_->outputMoreOptimal(global_best_output, particles_[j].getPreviousBestOutput())) {
				optimal_particle_index_ = j;
				global_best_output = particles_[j].getPreviousBestOutput();
			}
		}
	}
}


inline void Swarm::setParticleNeighbourhoodBests() {
	// set each particle's neighbourhood best to the position of the particle with the lowest previous best output
	//#pragma omp parallel for
	for (size_t i = 0; i < SWARM_SIZE; i++) {
		size_t best_neighbour_i = neighbours_[i][0];
		REAL best_neighbour_output = particles_[best_neighbour_i].getPreviousBestOutput();

		// if the second neighbour's output is more optimal, store it as the best neighbour
		if (problem_->outputMoreOptimal(best_neighbour_output, particles_[neighbours_[i][1]].getPreviousBestOutput())) {
			best_neighbour_output = particles_[i].getPreviousBestOutput();
			best_neighbour_i = 1;
		}

		// if the third neighbour's output is more optimal, store it as the best neighbour
		if (problem_->outputMoreOptimal(best_neighbour_output, particles_[neighbours_[i][2]].getPreviousBestOutput())) {
			best_neighbour_i = 2;
		}

		particles_[i].
				setNeighbourhoodBest(particles_[best_neighbour_i].getPreviousBestPosition());
	}

	return;
}

// neighbourhoods: 3.2.1 (i − 1 mod(S), i, i + 1 mod(S))
// find each particle's neighbours on init. and store in vector
