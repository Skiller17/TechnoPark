cmake_minimum_required(VERSION 3.24)
project(Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 main.cpp tests/unit_tests/test.cpp ActorTitles.cpp ActorTitles.h NonAdultMovies.cpp NonAdultMovies.h NamesOfTitles.cpp NamesOfTitles.h)
