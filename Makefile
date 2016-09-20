CPPFLAGS=-std=c++11 -Wall -O2 -fopenmp

# add core files
FILES=src/main.cpp src/particle.cpp src/swarm.cpp 

# add problem files
FILES+= src/problems/problem.cpp src/problems/sphere_test_problem_5d.cpp src/problems/sphere_test_problem_25d.cpp src/problems/sphere_test_problem_50d.cpp src/problems/RegressionFileReader.cpp src/problems/BrainVsBodyWeight.cpp src/problems/PastureRentalPrice.cpp

all:
	g++-4.8 $(FILES) $(CPPFLAGS) -o pso_test
