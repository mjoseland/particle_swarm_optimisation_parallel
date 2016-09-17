//
// Created by Malcolm Joseland on 17/09/2016.
//

#include <sstream>
#include <iostream>
#include "RegressionFileReader.h"

vector<vector<REAL>> RegressionFileReader::getFileData (string file_name) {
	vector<vector<REAL>> data;

	ifstream file;

	file.open("resources/" + file_name);
	if (!file.is_open()) {
		cerr << "File " << file_name << " couldn't be opened" << endl;
		return data;
	}

	string line;

	int line_index;
	REAL in_value;

	int i;

	for (i = 0; getline(file, line); i++) {
		istringstream in(line);

		// read the line index
		in >> line_index;

		data.push_back(vector<REAL>());

		// read all real numbers in the line and add them to the last vector in data
		while (!in.eof()) {
			in >> in_value;
			data.back().push_back(in_value);
		}
	}

	return data;
}
