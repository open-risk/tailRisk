cmake_minimum_required(VERSION 3.14)
project(tailRisk)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -std=c++11)
set( CMAKE_VERBOSE_MAKEFILE on )
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# tailRisk version
set(VERSION 0.1.0)

set(SOURCE_FILES main.cpp
        random_var.cpp)


set(TEST_FILES testing.cpp
        random_var.cpp)

# set the POCO paths and libs
set(POCO_PREFIX "/usr/local") # the directory containing "include" and "lib"
set(POCO_INCLUDE_DIR"${POCO_PREFIX}/include")

# set installed shared libraries
set(POCO_LIB_DIR "${POCO_PREFIX}/lib")

set(POCO_LIBS
        "${POCO_LIB_DIR}/libPocoNet.so"
        "${POCO_LIB_DIR}/libPocoUtil.so"
        "${POCO_LIB_DIR}/libPocoJSON.so"
        "${POCO_LIB_DIR}/libPocoNetSSL.so"
        "${POCO_LIB_DIR}/libPocoFoundation.so")

# set the ARMA paths and libs
set(ARMA_PREFIX "/usr")
set(ARMA_LIB_DIR "${ARMA_PREFIX}/lib/x86_64-linux-gnu")
set(ARMA_LIBS "${ARMA_LIB_DIR}/libarmadillo.so")

include_directories(.)
include_directories(/usr/local/include/eigen3)
include_directories(/usr/local/include/Poco)


add_executable(tailRisk ${SOURCE_FILES})
target_include_directories(tailRisk PRIVATE $(POCO_INCLUDE_DIR))
target_link_libraries(tailRisk "${POCO_LIBS}" "${ARMA_LIBS}")

add_executable(testing ${TEST_FILES})
target_include_directories(testing PRIVATE $(POCO_INCLUDE_DIR))
target_link_libraries(testing "${POCO_LIBS}" "${ARMA_LIBS}")