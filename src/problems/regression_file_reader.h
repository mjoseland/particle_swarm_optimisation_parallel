//
// Created by Malcolm Joseland on 17/09/2016.
//

#ifndef PSO_TEST_REGRESSIONFILEREADER_H
#define PSO_TEST_REGRESSIONFILEREADER_H

#include <vector>
#include <fstream>
#include <string>

#include "../pso_types.h"

using namespace std;

class RegressionFileReader {
public:
	static vector<vector<REAL>> getFileData(string file_name, vector<bool> ignore_columns, size_t y_value_index,
											size_t num_columns);
};

#endif //PSO_TEST_REGRESSIONFILEREADER_H
