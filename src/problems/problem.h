//
// Created by Malcolm Joseland on 1/08/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_PROBLEM_H
#define PARTICLE_SWARM_OPTIMISATION_PROBLEM_H

#include <vector>
#include <utility>
#include <ctime>
#include <string>

#include "../pso_types.h"

using namespace std;

//  (Abstract class) a problem whose optimal solution is to be found using PSO
class Problem {
public:
	const string name_;
    const DIMENSION num_dimensions_;       // count of dimensions
	const REAL lower_bound_;
	const REAL upper_bound_;
	const bool minimum_optimal_;         // true : minimum output is optimal for this problem

    Problem(string name, DIMENSION n_dimensions, double lower_bound, double upper_bound, bool minimum_optimal);
	~Problem();

	virtual REAL getOutput(const vector<double> &input_position) const { return 0.0; }
	//virtual Problem *getCopy() const;

	// returns true if compare_output is more optimal than inital_output
	bool outputMoreOptimal(REAL initial_output, REAL compare_output) const;

private:
	// false : we are trying to maximise the output
};


#endif //PARTICLE_SWARM_OPTIMISATION_PROBLEM_H
