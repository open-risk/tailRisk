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


/**
 * File: testing.cpp
 * Date: Apr 16 2021
 */

#include "stats.hpp"
#include "random_var.h"

int main(int argc, char *argv[]) {

    int SampleSize = 100;
    int DataType = 1;
    RandomVar myR(SampleSize, DataType);

    std::cout << "Testing" << std::endl;
    for (int i = 0; i < myR.size(); i++) {
        double rval = stats::rt(30);
        myR.setS(i, rval);
    }

    myR.Print();

}
