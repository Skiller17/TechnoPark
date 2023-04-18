cmake_minimum_required(VERSION 3.25)
project(DZ2)

set(CMAKE_CXX_STANDARD 17)

add_executable(DZ2 src/main.cpp src/textEditorOperations.cpp src/support.cpp)

if (test)
    add_executable(Tests tests/unit_tests/tests.cpp)

    find_package(GTest REQUIRED)

    target_include_directories(
            Tests PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )

    target_link_libraries(
            Tests PRIVATE
            gtest gtest_main
    )

    SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
    SET(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
    SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
endif ()