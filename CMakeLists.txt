cmake_minimum_required(VERSION 3.23)
project(prac2)

set(CMAKE_CXX_STANDARD 17)

set(src
        ${CMAKE_SOURCE_DIR}/src/FiniteStateMachine.h
        ${CMAKE_SOURCE_DIR}/src/DeterminedFiniteStateMachine.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/bin)

add_executable(prac2 main.cpp ${src})

add_subdirectory(tests)