//
// Created by Malcolm Joseland on 31/07/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_PARTICLE_H
#define PARTICLE_SWARM_OPTIMISATION_PARTICLE_H

#include <vector>
#include <array>
#include <random>
#include <omp.h>

#include "pso_types.h"
#include "problem.h"

// 1 / (2 * ln(2))
#define W_CONST 0.7213475204
// 0.5 + ln(2)
#define C_CONST 1.1931471806

using namespace std;

//  A particle. Used as part of a swarm of particles to optimise a problem
class Particle {
public:
    Particle(const Problem *const problem, size_t particle_id);

	REAL getPreviousBestOutput() const;
	const vector<REAL> *getPreviousBestPosition() const;

	void setNeighbourhoodBest(const vector<REAL> *neighbourhood_best_position);

    // iterate the dimension values by one step
    void iterate();

private:
	const Problem *const problem_;
	const DIMENSION num_dimensions_;
	const REAL lower_bound_;
	const REAL upper_bound_;

	REAL previous_best_output_;
	vector<REAL> position_;
	vector<REAL> velocity_;
	vector<REAL> previous_best_position_;
	vector<REAL> neighbourhood_best_position_;
	const vector<REAL> *neighbourhood_best_ptr_;

	// a unique random_engine for RNG in this particle
	default_random_engine random_engine_;
	uniform_real_distribution<REAL> zero_to_one_distribution_;
	uniform_real_distribution<REAL> plus_minus_one_distribution_;

	// finds a random point centered on G (centre of gravity)
	inline void getHypersphereRandomPoint(vector<REAL> &hypersphere_random_point);
};


#endif //PARTICLE_SWARM_OPTIMISATION_PARTICLE_H
