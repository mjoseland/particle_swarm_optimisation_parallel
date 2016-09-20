//
// Created by Malcolm Joseland on 31/07/2016.
//

#include <iostream>
#include <unordered_set>
#include "particle.h"

Particle::Particle(const Problem *const problem, size_t particle_id) : problem_(problem),
                   num_dimensions_(problem_->num_dimensions_), lower_bound_(problem_->lower_bound_),
                   upper_bound_(problem_->upper_bound_) {
	// build the random_engine for generating random numbers in this particle, random engines
	// used in each particle are unique and constructed based on particle_id so consistent results
	// will be given when testing
	seed_seq seed_sequence({particle_id});
	random_engine_ = default_random_engine(seed_sequence);

	// declare the two distributions used to initialise the particle's position and velocity
	uniform_real_distribution<REAL> bounded_distribution(lower_bound_, upper_bound_);
	uniform_real_distribution<REAL> velocity_distribution;

	// initialise the distributions used in getHypersphereRandomPoint
	zero_to_one_distribution_ = uniform_real_distribution<REAL>(0.0, 1.0);
	plus_minus_one_distribution_ = uniform_real_distribution<REAL>(-1.0, 1.0);

	// initialise vectors to store position, velocity etc. to the required size (number of
	// dimesnions)
	position_ = vector<REAL>(num_dimensions_);
	velocity_ = vector<REAL>(num_dimensions_);
	previous_best_position_ = vector<REAL>(num_dimensions_);
	neighbourhood_best_position_ = vector<REAL>(num_dimensions_);

	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		// initialise the position for this dimension to a random position in the search space (3.3)
		position_[i] = bounded_distribution(random_engine_);

		// initialise the velocity for this dimension (3.4)
		velocity_distribution = uniform_real_distribution<REAL>(lower_bound_ - position_[i],
		                                                        upper_bound_ - position_[i]);
		velocity_[i] = velocity_distribution(random_engine_);

		// initialise the previous best position for this dimension to the same as the current
		// position (3.3)
		previous_best_position_[i] = position_[i];

		// neighbourhood best values are initialised after all particles are constructed via a call
		// from swarm's constructor
	}

	// initialise previous_best_output_
	previous_best_output_ = problem_->getOutput(position_);

}

REAL Particle::getPreviousBestOutput() const {
	return previous_best_output_;
}

const vector<REAL> *Particle::getPreviousBestPosition() const {
	return &previous_best_position_;
}

void Particle::setNeighbourhoodBest(const vector<REAL> *new_neighbourhood_best_position) {
	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		neighbourhood_best_position_[i] = (*new_neighbourhood_best_position)[i];
	}

	neighbourhood_best_ptr_ = new_neighbourhood_best_position;
}

void Particle::iterate() {
	// retrive a random point in the hypersphere H(G, ||G - x) (3.10)
	vector<double> hypersphere_random_point(num_dimensions_);
	getHypersphereRandomPoint(hypersphere_random_point);

	// set the new velocity using the random point (3.11)
	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		velocity_[i] = W_CONST * velocity_[i] + hypersphere_random_point[i] - position_[i];
	}

	// change current dimension values (position) based on new velocities (3.11)
	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		position_[i] = W_CONST * velocity_[i] + hypersphere_random_point[i];
	}

	// confinement: ensure new dimension values are inside the required range (3.5)
	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		if (position_[i] < lower_bound_) {
			position_[i] = lower_bound_;
			velocity_[i] *= -0.5;
			continue;
		}

		if (position_[i] > upper_bound_) {
			position_[i] = upper_bound_;
			velocity_[i] *= -0.5;
		}
	}

	// use the defined problem to test the fitness of the new values
	REAL new_output = problem_->getOutput(position_);

	// if the new solution is better than the old one, update the old one
	if (problem_->outputMoreOptimal(previous_best_output_, new_output)) {
		previous_best_output_ = new_output;

		for (DIMENSION i = 0; i < num_dimensions_; i++) {
			previous_best_position_[i] = position_[i];
		}
	}
}

inline void Particle::getHypersphereRandomPoint(vector<REAL> &hypersphere_random_point) {
	// stores the centre of gravity (3.10)
	vector<REAL> centre_of_gravity(num_dimensions_);
	// stores random values in the range -1...1
	vector<REAL> random_values(num_dimensions_);
	// stores sum of all random values squared, used to confine the random point to a hypersphere
	// around the centre of gravity
	REAL cumulative_random_values_squared = 0.0;

	// if neighbourhood_best and previous_best values point to the same vector, then the
	// neighbourhood best for this particle is from the particle itself (3.4.3)
	bool neighbourhood_best_from_this_particle = neighbourhood_best_ptr_ ==
	                                             &previous_best_position_;

	// for each dimension:
	//      find and store the centre of gravity
	//      find and store a random real number in the range -1...1
	//      accumulate the random number ^ 2
	// if the neighbourhood best is from this particle, a modified centre of gravity formula is used
	if (!neighbourhood_best_from_this_particle) {
		// find the centre of gravity for each dimension (3.10)
		for (DIMENSION i = 0; i < num_dimensions_; i++) {
			centre_of_gravity[i] = position_[i] + C_CONST * ((previous_best_position_[i] +
								   neighbourhood_best_position_[i] - 2.0 * position_[i]) / 3.0);

			random_values[i] = plus_minus_one_distribution_(random_engine_);
			cumulative_random_values_squared += pow(random_values[i], 2);
		}
	} else {
		// find the centre of gravity for each dimension using the alternate formula (3.13)
		for (DIMENSION i = 0; i < num_dimensions_; i++) {
			centre_of_gravity[i] = position_[i] + C_CONST * ((previous_best_position_[i] -
								   position_[i]) / 2.0);
			//cout << centre_of_gravity[i] << endl;     // debug

			random_values[i] = plus_minus_one_distribution_(random_engine_);
			cumulative_random_values_squared += pow(random_values[i], 2);
		}
	}

	// calculate the random_value_multiplier (to constrain the random values in a sphere shape)
	// the first line restricts a dimension the random point on the surface of the hypersphere
	// the second line multiplies the above value by a real number in the range 0...1, to reduce
	// hypersphere random point to a point inside the hypersphere, instead of on it's surface
	REAL random_value_multiplier = (1 / sqrt(cumulative_random_values_squared)) *
			zero_to_one_distribution_(random_engine_);

	// find the hypersphere random point (x', 3.10)
	for (DIMENSION i = 0; i < num_dimensions_; i++) {
		hypersphere_random_point[i] = centre_of_gravity[i] + random_value_multiplier *
				                      random_values[i] * (centre_of_gravity[i] - position_[i]);
	}

	//TODO: del
	//cout << (0.5 + random_value_multiplier * random_values[0] * 0.4) << ',';
	//cout << (0.5 + random_value_multiplier * random_values[1] * 0.25) << endl;
}