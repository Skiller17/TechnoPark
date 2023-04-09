cmake_minimum_required(VERSION 3.24)
project(Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 src/main.cpp src/ActorTitles.cpp src/ActorTitles.h src/NamesOfTitles.cpp src/NamesOfTitles.h src/NonAdultMovies.cpp src/NonAdultMovies.h)

if (test)
add_executable(Tests tests/unit_tests/test.cpp src/ActorTitles.cpp src/ActorTitles.h src/NonAdultMovies.cpp src/NonAdultMovies.h src/NamesOfTitles.cpp src/NamesOfTitles.h)

find_package(GTest REQUIRED)

target_include_directories(
        Tests PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
        Tests PRIVATE
        gtest gtest_main
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LCOV_COMPILE_FLAGS} -coverage -lgcov -g -Wall -Werror")
set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${LCOV_LINK_FLAGS}")
endif()