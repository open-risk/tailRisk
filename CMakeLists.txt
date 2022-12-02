cmake_minimum_required(VERSION 3.10)
project(tailRisk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG)
set(CONAN_DISABLE_CHECK_COMPILER ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(..)
include_directories(.)

# tailRisk version
set(VERSION 0.1.0)

set(SOURCE_FILES
        random_var.cpp
        random_var.h)

set(TEST_FILES
        testing/rnd_statistics/test_random_var_bernulli.cpp
        testing/rnd_statistics/test_random_var_beta.cpp
        testing/rnd_statistics/test_random_var_binomial.cpp
        testing/rnd_statistics/test_random_var_normal.cpp
        testing/rnd_statistics/test_random_var_uniform.cpp
        testing/rnd_statistics/test_random_var_exponential.cpp
        testing/test_histogram.cpp)

find_package(Poco REQUIRED COMPONENTS Foundation JSON)
find_package(Catch2)

add_executable(tailRisk main.cpp ${SOURCE_FILES})
target_link_libraries(tailRisk "${POCO_LIBS}" Poco::Foundation Poco::JSON)

# CATCH2 TESTING
include(Catch)
enable_testing()
add_executable(testing ${SOURCE_FILES} ${TEST_FILES})
target_include_directories(testing PRIVATE $(POCO_INCLUDE_DIR))
target_link_libraries(testing "${POCO_LIBS}" Poco::Foundation Poco::JSON Catch2::Catch2WithMain)
catch_discover_tests(testing)
