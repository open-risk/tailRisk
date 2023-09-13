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

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "stats.hpp"
#include "../../src/random_var.h"

double binomial_mean(size_t number, int param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(6123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rbinom(param1, param2, engine));
    }
    return myR.Mean();
}

double binomial_var(size_t number, int param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(3123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rbinom(param1, param2, engine));
    }
    return myR.Variance();
}

int n_trials = 10;
double prob_par1 = 0.75;

double m_binomial_mean = (double) n_trials *prob_par1;
double m_binomial_var = n_trials*prob_par1*(1.0 - prob_par1);

TEST_CASE("Binomial", "[statistics]") {
    SECTION("Mean") {
        REQUIRE_THAT(binomial_mean(100000, n_trials, prob_par1), Catch::Matchers::WithinAbs(m_binomial_mean, 0.01));
    }SECTION("Variance") {
        REQUIRE_THAT(binomial_var(100000, n_trials, prob_par1), Catch::Matchers::WithinAbs(m_binomial_var, 0.01));
    }
}