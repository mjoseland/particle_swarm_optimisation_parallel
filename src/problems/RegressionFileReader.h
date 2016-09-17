//
// Created by Malcolm Joseland on 17/09/2016.
//

#ifndef PSO_TEST_REGRESSIONFILEREADER_H
#define PSO_TEST_REGRESSIONFILEREADER_H

#include <vector>
#include <fstream>

#include "../pso_types.h"

using namespace std;

class RegressionFileReader {
public:
	static vector<vector<REAL>> getFileData(string file_name);
};

#endif //PSO_TEST_REGRESSIONFILEREADER_H
