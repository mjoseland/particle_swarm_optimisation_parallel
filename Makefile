CPPFLAGS=-std=c++11 -Wall -O2 -fopenmp

# add core files
FILES=src/main.cpp src/particle.cpp src/swarm.cpp src/problem.cpp src/problem_optimiser.cpp

# add problem files
FILES += src/problems/parabola_test_problem_5d.cpp src/problems/parabola_test_problem_25d.cpp 
FILES += src/problems/parabola_test_problem_50d.cpp src/problems/regression_file_reader.cpp 
FILES += src/problems/regression_problem.cpp

all:
	mpicxx $(FILES) $(CPPFLAGS) -o pso_test
