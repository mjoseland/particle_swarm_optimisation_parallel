//
// Created by Malcolm Joseland on 1/08/2016.
//

#include <iostream>
#include "swarm.h"

Swarm::Swarm(const Problem *const problem) : problem_(problem) {
	// initialise the required number of particles in the particles_ vector
	particles_.reserve(SWARM_SIZE);
	for (size_t i = 0; i < SWARM_SIZE; i++) {
		particles_.push_back(Particle(problem_, i));
	}

	// find and store the neighbours of each particle using the ring topology
	// each particle's neibhbours: i − 1 mod(SWARM_SIZE), i, i + 1 mod(SWARM_SIZE)
	neighbours_ = vector<vector<int>>(SWARM_SIZE, vector<int>(3));
	for (size_t i = 0; i < SWARM_SIZE; i++) {
		neighbours_[i][0] = (i - 1) % SWARM_SIZE;
		neighbours_[i][1] = i;
		neighbours_[i][2] = (i + 1) % SWARM_SIZE;
	}

	setParticleNeighbourhoodBests();
}

const vector<REAL> *const Swarm::getBestSolution() {
	return particles_[optimal_particle_index_].getPreviousBestPosition();
}

REAL Swarm::getBestSolutionOutput() {
	return particles_[optimal_particle_index_].getPreviousBestOutput();
}


void Swarm::iterateNTimes(int iterate_count) {
	REAL global_best_output = particles_[0].getPreviousBestOutput();

	// branch for problem requiring minimisation
	if (problem_->minimum_optimal_) {
		// perform the required number of iterations
		for (int i = 0; i < iterate_count; i++) {
			// iterate and get the previous best of the first particle
			//particles_[0].iterate();
			//global_best_output = particles_[0].getPreviousBestOutput();

			//iterate all remaining particles while retaining the global best output
			for (size_t i = 0; i < SWARM_SIZE; i++) {
				particles_[i].iterate();

				if (particles_[i].getPreviousBestOutput() < global_best_output) {
					global_best_output = particles_[i].getPreviousBestOutput();
					optimal_particle_index_ = i;
				}
			}

			// adjust particle neighbourhood bests
			setParticleNeighbourhoodBests();
			/*
			cout << "Iteration complete: values, gbo: " << endl;
			for (DIMENSION i = 0; i < problem_->num_dimensions_ - 1; i++) {
				cout << (*getBestSolution())[i] << ", ";
			}
			cout << (*getBestSolution())[problem_->num_dimensions_ - 1] << endl;
			cout << global_best_output << endl;*/
		}

		return;
	}

	// branch for problem requiring maximal output
	for (int i = 0; i < iterate_count; i++) {
		// iterate and get the previous best of the first particle
		particles_[0].iterate();
		global_best_output = particles_[0].getPreviousBestOutput();

		//iterate all remaining particles while retaininng the global best output
		for (size_t i = 1; i < SWARM_SIZE; i++) {
			particles_[i].iterate();

			if (particles_[i].getPreviousBestOutput() > global_best_output) {
				global_best_output = particles_[i].getPreviousBestOutput();
				optimal_particle_index_ = i;
			}
		}
	}
}


void Swarm::setParticleNeighbourhoodBests() {
	if (problem_->minimum_optimal_) {
		// if the problem is trying to minimise output, set each particle's neighbourhood best
		// to the position of the particle with the lowest previous best output
		for (size_t i = 0; i < SWARM_SIZE; i++) {
			size_t best_neighbour_i = neighbours_[i][0];
			REAL best_neighbour_output = particles_[best_neighbour_i].getPreviousBestOutput();

			// if the second neighbour's output is smaller, store it as the best neighbour
			if (particles_[neighbours_[i][1]].getPreviousBestOutput() < best_neighbour_output) {
				best_neighbour_output = particles_[i].getPreviousBestOutput();
				best_neighbour_i = 1;
			}

			// if the third neighbour's output is smaller, store it as the best neighbour
			if (particles_[neighbours_[i][2]].getPreviousBestOutput() < best_neighbour_output) {
				best_neighbour_i = 2;
			}

			particles_[i].
					setNeighbourhoodBest(particles_[best_neighbour_i].getPreviousBestPosition());
		}

		return;
	}

	for (size_t i = 0; i < SWARM_SIZE; i++) {
		size_t best_neighbour_i = neighbours_[i][0];
		REAL best_neighbour_output = particles_[best_neighbour_i].getPreviousBestOutput();

		// if the second neighbour's output is smaller, store it as the best neighbour
		if (particles_[neighbours_[i][1]].getPreviousBestOutput() > best_neighbour_output) {
			best_neighbour_output = particles_[i].getPreviousBestOutput();
			best_neighbour_i = 1;
		}

		// if the third neighbour's output is smaller, store it as the best neighbour
		if (particles_[neighbours_[i][2]].getPreviousBestOutput() > best_neighbour_output) {
			best_neighbour_i = 2;
		}

		particles_[i].
				setNeighbourhoodBest(particles_[best_neighbour_i].getPreviousBestPosition());
	}
}

// neighbourhoods: 3.2.1 (i − 1 mod(S), i, i + 1 mod(S))
// find each particle's neighbours on init. and store in vector
