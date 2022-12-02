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

double exponential_mean(size_t number, double param1) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(812776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rexp(param1, engine));
    }
    return myR.Mean();
}

double exponential_var(size_t number, double param1) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(712376);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rexp(param1, engine));
    }
    return myR.Variance();
}

double exponential_quantile(size_t number, double param1, double param3) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(613776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rexp(param1,  engine));
    }
    return myR.Quantile(param3);
}

double rate_par = 0.8;
double a_par1 = rate_par;
double m_exponential_mean = 1.0 / rate_par;
double m_exponential_var = std::pow(rate_par,-2);

// QUANTILES
//std::vector<double> inp_vals = { 0.1,        0.6,       0.95 };
//std::vector<double> exp_vals = { 0.1317006,  1.145363,  3.744665 };

TEST_CASE("Exponential", "[statistics]") {
    SECTION("Mean") {
        REQUIRE_THAT(exponential_mean(100000, a_par1), Catch::Matchers::WithinAbs(m_exponential_mean, 0.01));
    }SECTION("Variance") {
        REQUIRE_THAT(exponential_var(1000000, a_par1), Catch::Matchers::WithinAbs(m_exponential_var, 0.01));
    }SECTION("Quantile") {
        REQUIRE_THAT(exponential_quantile(100000, a_par1, 0.1), Catch::Matchers::WithinAbs(0.1317006, 0.01));
        REQUIRE_THAT(exponential_quantile(100000, a_par1, 0.6), Catch::Matchers::WithinAbs(1.145363, 0.01));
        REQUIRE_THAT(exponential_quantile(100000, a_par1, 0.95), Catch::Matchers::WithinAbs(3.744665, 0.01));
    }
}