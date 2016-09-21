//
// Created by Malcolm Joseland on 21/09/2016.
//

#ifndef PARTICLE_SWARM_OPTIMISATION_PARALLEL_REGRESSIONPROBLEM_H
#define PARTICLE_SWARM_OPTIMISATION_PARALLEL_REGRESSIONPROBLEM_H

#include <cmath>

#include "../problem.h"
#include "regression_file_reader.h"

class RegressionProblem : public Problem {
public:
	RegressionProblem(string file_name, DIMENSION num_dimensions, REAL range_min, REAL range_max,
					  vector<bool> ignore_columns, size_t y_value_index, size_t num_columns);

	REAL getOutput(const vector<REAL> &dimension_valuse) const;

private:
	vector<vector<REAL>> data_;
};


#endif //PARTICLE_SWARM_OPTIMISATION_PARALLEL_REGRESSIONPROBLEM_H
