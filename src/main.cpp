/*################################################################################
  ##
  ##   Copyright (C) 2020-2023 Open Risk (www.openriskmanagement.com)
  ##
  ##   This file is part of the tailRisk C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/**
 * File: main.cpp
 * Date: Mon Nov  9 10:31:35 CET 2020
 *
 * Examples of using the tailRisk library to compute tail risk measures
 *
 */

#include "random_var.h"

int main(int argc, char *argv[]) {

    // Reading in some data for a type 0 representation (discrete distribution)
    int LossGrid = 1000;
    int DataType = 0;
    RandomVar L(LossGrid, DataType);
    std::string filename =  "../../data/example5.json";
    L.ReadFromJSON(filename);
    L.Print();

    // Calculate various measures
    double alpha = 0.8;
    int threshold = 0;

    std::cout << "Mean Value: " << L.Mean() << std::endl;
    std::cout << "Median Value: " << L.Median() << std::endl;
    std::cout << "STD Value: " << L.StandardDeviation() << std::endl;
    std::cout << "Kurtosis: " << L.Kurtosis() << std::endl;
    std::cout << "Skeweness: " << L.Skeweness() << std::endl;
    std::cout << "Quantile @ " << alpha << ": " << L.Quantile(alpha) << std::endl;
    std::cout << "Quantile Index @ " << alpha << ": " << L.Quantile_Index(alpha) << std::endl;
    std::cout << "VaR @ " << alpha << ": " << L.VaR(alpha) << std::endl;
    std::cout << "Expected Shortfall @ " << alpha << ": " << L.ExpectedShortFall(alpha) << std::endl;
    std::cout << "Exceedance Probability: " << L.ExceedanceProbability(threshold) << std::endl;
    std::cout << "Mean Excess: " << L.MeanExcess(threshold ) << std::endl;

    return 0;
}