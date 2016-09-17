//
// Created by Malcolm Joseland on 1/08/2016.
//

#include "problem.h"

Problem::Problem(string name, DIMENSION n_dimensions, bool minimum_optimal, double lower_bound,
                 double upper_bound) :
			name_(name), num_dimensions_(n_dimensions), minimum_optimal_(minimum_optimal),
			lower_bound_(lower_bound), upper_bound_(upper_bound) { }

Problem::~Problem() { }

