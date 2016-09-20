//
// Created by Malcolm Joseland on 1/08/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_SWARM_H
#define PARTICLE_SWARM_OPTIMISATION_SWARM_H

#include <algorithm>
#include <omp.h>

#include "pso_types.h"
#include "particle.h"
#include "problems/problem.h"

#define SWARM_SIZE 40

using namespace std;

/*
 * A swarm that uses multiple particles to find the best
 */
class Swarm {
public:
    Swarm(Problem *problem);

	const vector<REAL> *const getBestSolution();
	REAL getBestSolutionOutput();

	void iterateNTimes(int iterate_count);

private:
    const Problem *const problem_;
	size_t optimal_particle_index_;

    vector<Particle> particles_;
	vector<vector<size_t>> neighbours_;

	void setParticleNeighbourhoodBests();
};


#endif //PARTICLE_SWARM_OPTIMISATION_SWARM_H
