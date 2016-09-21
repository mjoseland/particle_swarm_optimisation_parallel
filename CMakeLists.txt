cmake_minimum_required(VERSION 3.5)
project(particle_swarm_optimisation_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2")

SET(CMAKE_CXX_COMPILER g++)

set(SOURCE_FILES
    resources/brain_vs_body_weight.txt
    resources/pasture_rental_price.txt
    src/problems/BrainVsBodyWeight.cpp
    src/problems/BrainVsBodyWeight.h
    src/problems/PastureRentalPrice.cpp
    src/problems/PastureRentalPrice.h
        src/problem.cpp
        src/problem.h
    src/problems/RegressionFileReader.cpp
    src/problems/RegressionFileReader.h
        src/problems/ParabolaTestProblem25d.cpp
    src/problems/sphere_test_problem_25d.h
        src/problems/ParabolaTestProblem50d.cpp
    src/problems/sphere_test_problem_50d.h
    src/problems/sphere_test_problem_5d.cpp
    src/problems/sphere_test_problem_5d.h
    src/main.cpp
    src/particle.cpp
    src/particle.h
    src/pso_types.h
    src/swarm.cpp
    src/Swarm.h
    Makefile src/ProblemOptimiser.cpp src/ProblemSolver.h src/problems/RegressionProblem.cpp src/problems/RegressionProblem.h)

add_executable(particle_swarm_optimisation_parallel ${SOURCE_FILES})