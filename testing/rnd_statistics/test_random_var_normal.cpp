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

double normal_mean(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(12776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rnorm(param1, param2, engine));
    }
    return myR.Mean();
}

double normal_var(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(12376);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rnorm(param1, param2, engine));
    }
    return myR.Variance();
}

double normal_quantile(size_t number, double param1, double param2, double param3) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(13776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rnorm(param1, param2, engine));
    }
    return myR.Quantile(param3);
}

double mu = 0;
double sigma = 1;
double m_normal_mean = mu;
double m_normal_var = sigma*sigma;
double a_par2 = mu;
double b_par2 = sigma;

// QUANTILES
//std::vector<double> inp_vals = { 0.15,       0.5,  0.79 };
//std::vector<double> exp_vals = { -1.072867,  1.0,  2.612842 };

TEST_CASE("Normal", "[statistics]") {
    SECTION("Mean") {
        REQUIRE_THAT(normal_mean(100000, a_par2, b_par2), Catch::Matchers::WithinAbs(m_normal_mean, 0.01));
    }SECTION("Variance") {
        REQUIRE_THAT(normal_var(100000, a_par2, b_par2), Catch::Matchers::WithinAbs(m_normal_var, 0.01));
    }SECTION("Quantile") {
        REQUIRE_THAT(normal_quantile(100000, a_par2, b_par2, 0.5), Catch::Matchers::WithinAbs(0.0, 0.01));
        REQUIRE_THAT(normal_quantile(100000, a_par2, b_par2, 0.95), Catch::Matchers::WithinAbs(1.644854, 0.01));
        REQUIRE_THAT(normal_quantile(100000, a_par2, b_par2, 0.05), Catch::Matchers::WithinAbs(-1.644854, 0.01));
    }
}