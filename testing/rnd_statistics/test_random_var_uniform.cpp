/*################################################################################
  ##
  ##   Copyright (C) 2020-2022 Open Risk (www.openriskmanagement.com)
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

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "stats.hpp"
#include "random_var.h"

double uniform_mean(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(12776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::runif(param1, param2, engine));
    }
    return myR.Mean();
}

double uniform_var(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(12376);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::runif(param1, param2, engine));
    }
    return myR.Variance();
}

double uniform_quantile(size_t number, double param1, double param2, double param3) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(13776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::runif(param1, param2, engine));
    }
    return myR.Quantile(param3);
}

//double a_par3 = -1;
//double b_par3 = 3;

double a_par3 = 0;
double b_par3 = 1;

double m_uniform_mean = (a_par3 + b_par3) / 2.0;
double m_uniform_var = (b_par3 - a_par3) * (b_par3 - a_par3) / 12.0;

// QUANTILES
//std::vector<double> inp_vals = { 0.15,  0.5,  0.95 };
//std::vector<double> exp_vals = { -0.4,  1,    2.8 };

TEST_CASE("Uniform", "[statistics]") {
    SECTION("Mean") {
        REQUIRE_THAT(uniform_mean(100000, a_par3, b_par3), Catch::Matchers::WithinAbs(m_uniform_mean, 0.01));
    }SECTION("Variance") {
        REQUIRE_THAT(uniform_var(100000, a_par3, b_par3), Catch::Matchers::WithinAbs(m_uniform_var, 0.01));
    }SECTION("Quantile") {
        REQUIRE_THAT(uniform_quantile(100000, a_par3, b_par3, 0.15), Catch::Matchers::WithinAbs(0.15, 0.01));
        REQUIRE_THAT(uniform_quantile(100000, a_par3, b_par3, 0.5), Catch::Matchers::WithinAbs(0.5, 0.01));
        REQUIRE_THAT(uniform_quantile(100000, a_par3, b_par3, 0.95), Catch::Matchers::WithinAbs(0.95, 0.01));
    }
}