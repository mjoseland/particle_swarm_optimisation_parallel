//
// Created by Malcolm Joseland on 17/09/2016.
//

#include "PastureRentalPrice.h"

PastureRentalPrice::PastureRentalPrice() :
		Problem("Predicting Pasture Rent per Grassy Acre", 3, 0.0, 100.0, true){
	data = RegressionFileReader::getFileData(file_name);
}

REAL PastureRentalPrice::getOutput(const vector<REAL> &dimension_values) const {
	REAL squared_difference = 0.0;
	REAL output;		// ie. Y

	// for each data point in the data vector, add its squared difference to the line
	// all linear regression problems are in the form Y = A0 * X0 + A1 * X1 + A2 * X2 ...
	for (auto data_point: data) {
		output = 0.0;

		// add Aj * Xj for all dimensions
		for (DIMENSION j = 0; j < num_dimensions_; j++) {
			output += data_point[j] * dimension_values[j];
		}

		squared_difference += pow(output - data_point.back(), 2);
	}

	squared_difference /= data.size();

	return sqrt(squared_difference);
}

//Problem *PastureRentalPrice::getCopy() {
	//return new PastureRentalPrice();
//}