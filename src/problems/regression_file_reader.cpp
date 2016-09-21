//
// Created by Malcolm Joseland on 17/09/2016.
//

#include <sstream>
#include <iostream>
#include "regression_file_reader.h"

vector<vector<REAL>> RegressionFileReader::getFileData (string file_name, vector<bool> ignore_columns,
														size_t y_value_index, size_t num_columns) {
	ifstream file;

	file.open("resources/" + file_name);
	if (!file.is_open()) {
		cerr << "File " << file_name << " couldn't be opened" << endl;
		exit(1);
	}

	string line;
	string read_string;
	REAL output_value;

	vector<vector<REAL>> data;

	int i;

	for (i = 0; getline(file, line); i++) {
		istringstream line_stream(line);
		data.push_back(vector<REAL>());

		// read all real numbers in the line and add them to the last vector in data
		for (size_t j = 0; j < num_columns; j++) {
			// check for line eof, ie ensure there are enough columns on this line to fit in the vector
			if (line_stream.eof()) {
				cerr << "EOF in file name, line: " << file_name << ", " << i << endl;
				exit(1);
			}

			line_stream >> read_string;

			if (!ignore_columns[j] && j != y_value_index) {
				data.back().push_back(stof(read_string));
			}

			// the current column is the one intended to
			if (j == y_value_index) {
				output_value = stof(read_string);
			}
		}

		// add the output (Y value) of the regression to the end of the vector
		data.back().push_back(output_value);
	}

	return data;
}
