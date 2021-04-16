/**
 * File: testing.cpp
 * Date: Apr 16 2021
 * Author: Open Risk  (www.openriskmanagement.com)
 *
 */

#include "stats.hpp"
#include <armadillo>
#include "random_var.h"


int main(int argc, char *argv[]) {


    int SampleSize = 100;
    int DataType = 1;
    RandomVar myR(SampleSize, DataType);

    cout << "Testing" << endl;
    for (int i = 0; i < myR.size(); i++) {
        double rval = stats::rt(30);
        myR.setS(i, rval);
    }

    myR.Print();

}
