/*################################################################################
  ##
  ##   Copyright (C) 2020-2024 Open Risk (www.openriskmanagement.com)
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
#include "../../src/random_var.h"

double beta_mean(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rbeta(param1, param2, engine));
    }
    return myR.Mean();
}

double beta_var(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rbeta(param1, param2, engine));
    }
    return myR.Variance();
}

double beta_quantile(size_t number, double param1, double param2, double param3) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rbeta(param1, param2, engine));
    }
    return myR.Quantile(param3);
}

/*
 * Numbers based on the Stats test
 * https://github.com/kthohr/stats/blob/master/tests/rand/rbeta.cpp
*/

double a_par = 3.0;
double b_par = 2.0;

double alpha = 3;
double beta = 2;

double m_beta_mean = alpha / (alpha + beta);
double m_beta_var = alpha * beta / (std::pow(alpha + beta, 2) * (alpha + beta + 1.0));

// QUANTILES
//std::vector<double> inp_vals = {0.15, 0.5, 0.95};
//std::vector<double> exp_vals = {0.3734678, 0.6142724, 0.9023885};

TEST_CASE("Beta", "[statistics]") {
    SECTION("Mean") {
        REQUIRE_THAT(beta_mean(1000, a_par, b_par), Catch::Matchers::WithinAbs(m_beta_mean, 0.01));
    }SECTION("Variance") {
        REQUIRE_THAT(beta_var(1000, a_par, b_par), Catch::Matchers::WithinAbs(m_beta_var, 0.01));
    }SECTION("Quantile") {
        REQUIRE_THAT(beta_quantile(1000, a_par, b_par, 0.15), Catch::Matchers::WithinAbs(0.3734678, 0.01));
        REQUIRE_THAT(beta_quantile(1000, a_par, b_par, 0.5), Catch::Matchers::WithinAbs(0.6142724, 0.01));
        REQUIRE_THAT(beta_quantile(1000, a_par, b_par, 0.95), Catch::Matchers::WithinAbs(0.9023885, 0.01));
    }
}