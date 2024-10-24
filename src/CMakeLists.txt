 ##  Copyright (C) 2020-2024 Open Risk (www.openriskmanagement.com)
 ##
 ##  This file is part of the tailRisk C++ library.
 ##
 ##  Licensed under the Apache License, Version 2.0 (the "License");
 ##  you may not use this file except in compliance with the License.
 ##  You may obtain a copy of the License at
 ##
 ##    http://www.apache.org/licenses/LICENSE-2.0
 ##
 ##  Unless required by applicable law or agreed to in writing, software
 ##  distributed under the License is distributed on an "AS IS" BASIS,
 ##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ##  See the License for the specific language governing permissions and
 ##  limitations under the License.

 # Project metadata
 set(PROJECT_VENDOR "Open Risk")
 set(PROJECT_CONTACT "info@openrisk.eu")
 set(PROJECT_URL "https://github.com/open-risk/tailRisk")
 set(PROJECT_DESCRIPTION "tailRisk is a library for computing tail risk measures")

cmake_minimum_required(VERSION 3.19)
project(tailRisk)
 set(TAILRISK_VERSION_MAJOR 0)
 set(TAILRISK_VERSION_MINOR 2)
 set(TAILRISK_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -std=c++17)
add_definitions("-std=c++17")

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG)
set(CMAKE_PREFIX_PATH cmake-build-debug)

include_directories(..)
include_directories(.)

# tailRisk version
set(VERSION 0.2.0)

set(SOURCE_FILES
        random_var.cpp
        random_var.h)

set(TEST_FILES
        ../testing/rnd_statistics/test_random_var_bernulli.cpp
        ../testing/rnd_statistics/test_random_var_beta.cpp
        ../testing/rnd_statistics/test_random_var_binomial.cpp
        ../testing/rnd_statistics/test_random_var_normal.cpp
        ../testing/rnd_statistics/test_random_var_uniform.cpp
        ../testing/rnd_statistics/test_random_var_exponential.cpp
        ../testing/rnd_statistics/test_random_var_lognormal.cpp
        ../testing/test_histogram.cpp)

find_package(Poco REQUIRED COMPONENTS Foundation Net NetSSL Util Data)
find_package(Catch2 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(statslib REQUIRED)
find_package(gcem REQUIRED)


add_executable(tailRisk main.cpp ${SOURCE_FILES})
target_include_directories(tailRisk PRIVATE ${Eigen3_INCLUDE_DIRS})
target_include_directories(tailRisk PRIVATE ${statslib_INCLUDE_DIRS})
target_include_directories(tailRisk PRIVATE ${gcem_INCLUDE_DIRS})
target_link_libraries(tailRisk
        Poco::Foundation
        Poco::Data
        Poco::JSON
        Poco::Net
        Poco::Util)

# CATCH2 TESTING
include(Catch)
include(CTest)
enable_testing()

add_executable(unit_testing ${SOURCE_FILES} ${TEST_FILES})
catch_discover_tests(unit_testing)

target_include_directories(unit_testing PRIVATE ${Catch2_INCLUDE_DIRS})
target_include_directories(unit_testing PRIVATE ${Eigen3_INCLUDE_DIRS})
target_include_directories(unit_testing PRIVATE ${statslib_INCLUDE_DIRS})
target_include_directories(unit_testing PRIVATE ${gcem_INCLUDE_DIRS})
target_link_libraries(unit_testing Catch2::Catch2WithMain
        Poco::Data
        Poco::Foundation
        Poco::Net
        Poco::Util
        Poco::JSON)

