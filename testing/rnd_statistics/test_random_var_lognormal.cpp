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

double lognormal_mean(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rlnorm(param1, param2, engine));
    }
    return myR.Mean();
}

double lognormal_var(size_t number, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rlnorm(param1, param2, engine));
    }
    return myR.Variance();
}

/*
 * Numbers based on the Stats test
 * https://github.com/kthohr/stats/blob/master/tests/rand/rlnorm.cpp
*/

double mu2 = 0.1;
double sigma2 = 1;
double a_par4 = mu2;
double b_par4 = sigma2;

double m_lnorm_mean = std::exp(mu2 + sigma2 * sigma2 / 2.0);
double m_lnorm_var = (std::exp(sigma2 * sigma2) - 1.0) * std::exp(2 * mu2 + sigma2 * sigma2);

TEST_CASE("LogNormal", "[statistics]") {
    SECTION("Mean") {
        REQUIRE_THAT(lognormal_mean(100000, a_par4, b_par4), Catch::Matchers::WithinAbs(m_lnorm_mean, 0.01));
    }SECTION("Variance") {
        REQUIRE_THAT(lognormal_var(100000, a_par4, b_par4), Catch::Matchers::WithinAbs(m_lnorm_var, 0.1));
    }
}