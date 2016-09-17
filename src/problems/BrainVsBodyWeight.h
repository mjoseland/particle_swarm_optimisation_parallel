//
// Created by Malcolm Joseland on 17/09/2016.
//

#ifndef PSO_TEST_BRAINVSBODYWEIGHT_H
#define PSO_TEST_BRAINVSBODYWEIGHT_H

#include <cmath>

#include "RegressionFileReader.h"
#include "problem.h"

// data sourced from: http://people.sc.fsu.edu/~jburkardt/datasets/regression/x01.txt
class BrainVsBodyWeight : public Problem {
public:
	BrainVsBodyWeight();

	// returns the sigma value for a given linear regression attempt
  	REAL getOutput(const vector<REAL> &dimension_values) const;

private:
	string file_name = "brain_vs_body_weight.txt";

	// 0: brain weight 0: body weight (Y value)
	vector<vector<REAL>> data;
};


#endif //PSO_TEST_BRAINVSBODYWEIGHT_H
