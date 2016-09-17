cmake_minimum_required(VERSION 3.5)
project(particle_swarm_optimisation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2")

SET(CMAKE_CXX_COMPILER g++)

set(SOURCE_FILES src/main.cpp src/particle.cpp src/particle.h src/swarm.cpp src/swarm.h src/problems/problem.cpp src/problems/problem.h src/problems/sphere_test_problem_5d.cpp src/problems/sphere_test_problem_5d.h src/pso_types.h src/main.cpp src/problems/sphere_test_problem_25d.cpp src/problems/sphere_test_problem_25d.h src/problems/sphere_test_problem_50d.cpp src/problems/sphere_test_problem_50d.h src/problems/BrainVsBodyWeight.h src/problems/BrainVsBodyWeight.cpp src/problems/BrainVsBodyWeight.h src/problems/RegressionFileReader.cpp src/problems/RegressionFileReader.h src/problems/PastureRentalPrice.cpp src/problems/PastureRentalPrice.h)

add_executable(particle_swarm_optimisation ${SOURCE_FILES})
