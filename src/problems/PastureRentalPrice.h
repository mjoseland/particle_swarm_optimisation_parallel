//
// Created by Malcolm Joseland on 17/09/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_PASTURERENTALPRICE_H
#define PARTICLE_SWARM_OPTIMISATION_PASTURERENTALPRICE_H

#include <cmath>

#include "problem.h"
#include "RegressionFileReader.h"

// data sourced from: http://people.sc.fsu.edu/~jburkardt/datasets/regression/x11.txt
class PastureRentalPrice : public Problem {

public:
	PastureRentalPrice();

	// returns the sigma value for a given linear regression attempt
	REAL getOutput(const vector<REAL> &dimension_values) const;
	//Problem *getCopy();

private:
	string file_name = "pasture_rental_price.txt";

	// 0: rent per arable acre, 1: milk cows per square mile, 2: difference between pasture and arable land
	// 4: rental price per grassy acre (Y value)
	vector<vector<REAL>> data;
};


#endif //PARTICLE_SWARM_OPTIMISATION_PASTURERENTALPRICE_H
