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

double bernulli_mean(size_t number, double param) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rbern(param, engine));
    }
    return myR.Mean();
}

double bernulli_var(size_t number, double param) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::rbern(param, engine));
    }
    return myR.Variance();
}

double prob_par = 0.75;
double m_bernulli_mean = prob_par;
double m_bernulli_var = prob_par * (1.0 - prob_par);

TEST_CASE("Bernulli", "[statistics]") {
    SECTION("Mean") {
        REQUIRE_THAT(bernulli_mean(1000, prob_par), Catch::Matchers::WithinAbs(m_bernulli_mean, 0.01));
    }SECTION("Variance") {
        REQUIRE_THAT(bernulli_var(1000, prob_par), Catch::Matchers::WithinAbs(m_bernulli_var, 0.01));
    }
}