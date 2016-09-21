//
// Created by Malcolm Joseland on 21/09/2016.
//

#include "regression_problem.h"

RegressionProblem::RegressionProblem(string file_name, DIMENSION num_dimensions, REAL range_min, REAL range_max,
									vector<bool> ignore_columns, size_t y_value_index, size_t num_columns) :
									Problem("Regression Problem from file: " + file_name, num_dimensions, range_min,
									range_max, true) {

	data_ = RegressionFileReader::getFileData(file_name, ignore_columns, y_value_index, num_columns);
}

inline REAL RegressionProblem::getOutput(const vector<REAL> &dimension_values) const {
	REAL squared_difference = 0.0;
	REAL output;		// ie. Y

	// for each data point in the data vector, add its squared difference to the line
	// all linear regression problems are in the form Y = A0 * X0 + A1 * X1 + A2 * X2 ...
	for (vector<REAL> data_point: data_) {
		output = 0.0;

		// add Aj * Xj for all dimensions
		for (DIMENSION j = 0; j < num_dimensions_; j++) {
			output += data_point[j] * dimension_values[j];
		}

		squared_difference += pow(output - data_point.back(), 2);
	}

	// return the square root of the average squared difference between data points
	return sqrt(squared_difference / data_.size());
}
