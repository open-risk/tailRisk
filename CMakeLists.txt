cmake_minimum_required(VERSION 3.14)
project(tailRisk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG)
set(CONAN_DISABLE_CHECK_COMPILER ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# tailRisk version
set(VERSION 0.1.0)

set(SOURCE_FILES main.cpp random_var.cpp)

set(TEST_FILES testing.cpp random_var.cpp)

find_package(Poco REQUIRED COMPONENTS Foundation JSON)

add_executable(tailRisk ${SOURCE_FILES})
target_link_libraries(tailRisk "${POCO_LIBS}"  Poco::Foundation Poco::JSON)

add_executable(testing ${TEST_FILES})
target_include_directories(testing PRIVATE $(POCO_INCLUDE_DIR))
target_link_libraries(testing "${POCO_LIBS}"  Poco::Foundation Poco::JSON)