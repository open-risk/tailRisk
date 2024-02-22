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
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "stats.hpp"
#include "../src/random_var.h"

RandomVar uniform_histogram(size_t number, size_t bins, double param1, double param2) {
    RandomVar myR(number, 1);
    stats::rand_engine_t engine(123776);
    for (int i = 0; i < number; i++) {
        myR.setS(i, stats::runif(param1, param2, engine));
    }
    RandomVar H = myR.Histogram(bins);
    return H;
}

TEST_CASE("Uniform Histogram", "[histogram]") {
    SECTION("Bins=1") {
        REQUIRE_THAT(uniform_histogram(1000, 1, 0, 1).getP(0), Catch::Matchers::WithinAbs(1, 0.01));
        REQUIRE_THAT(uniform_histogram(1000, 1, 0, 1).getX(0), Catch::Matchers::WithinAbs(0.5, 0.01));
    }
    SECTION("Shifted Bins=1") {
        REQUIRE_THAT(uniform_histogram(1000, 1, 1, 2).getP(0), Catch::Matchers::WithinAbs(1, 0.01));
        REQUIRE_THAT(uniform_histogram(1000, 1, 1, 2).getX(0), Catch::Matchers::WithinAbs(1.5, 0.01));
    }
    SECTION("Bins=2") {
        REQUIRE_THAT(uniform_histogram(100000, 2, 0, 1).getP(0), Catch::Matchers::WithinAbs(0.5, 0.01));
        REQUIRE_THAT(uniform_histogram(100000, 2, 0, 1).getP(1), Catch::Matchers::WithinAbs(0.5, 0.01));
        REQUIRE_THAT(uniform_histogram(100000, 2, 0, 1).getX(0), Catch::Matchers::WithinAbs(0.25, 0.01));
        REQUIRE_THAT(uniform_histogram(100000, 2, 0, 1).getX(1), Catch::Matchers::WithinAbs(0.75, 0.01));
    }
    SECTION("Bins=4") {
        REQUIRE_THAT(uniform_histogram(100000, 4, 0, 1).getX(0), Catch::Matchers::WithinAbs(0.125, 0.01));
        REQUIRE_THAT(uniform_histogram(100000, 4, 0, 1).getX(1), Catch::Matchers::WithinAbs(0.375, 0.01));
        REQUIRE_THAT(uniform_histogram(100000, 4, 0, 1).getX(2), Catch::Matchers::WithinAbs(0.625, 0.01));
        REQUIRE_THAT(uniform_histogram(100000, 4, 0, 1).getX(3), Catch::Matchers::WithinAbs(0.875, 0.01));
    }
    SECTION("Bins=10") {
        auto i = GENERATE(range(0, 10));
        REQUIRE_THAT(uniform_histogram(10000, 10, 0, 1).getP(i), Catch::Matchers::WithinAbs(0.1, 0.01));
    }
}