/** 
 * File: random_var.cpp
 * Date: Mon Nov  9 10:31:35 CET 2020
 * Author: Open Risk  (www.openriskmanagement.com)
 *
 */

#include <cmath>
#include <iostream>
#include <cassert>

#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <armadillo>

#include "random_var.h"

using namespace Poco;

RandomVar &RandomVar::operator=(const RandomVar &R) {
    assert(R.size() == this->size()); // check that size matches
    for (size_t i = 0; i < R.size(); i++) {
        this->setX(i, R.getX(i));
        this->setP(i, R.getP(i));
        this->setC(i, R.getC(i));
    }
    return (*this);
};

/**
 * ... text ...
 */
void RandomVar::Sort() {
    arma::sort(m_S);
}

/**
 * ... text ...
 */
void RandomVar::Cumulative() {
    m_C[0] = m_P[0];
    for (size_t i = 1; i < m_P.size(); i++)
        m_C[i] = m_C[i - 1] + m_P[i];
}

/**
 * ... text ...
 */
void RandomVar::Probability() {
    m_P[0] = m_C[0];
    for (size_t i = 1; i < m_P.size(); i++)
        m_P[i] = m_C[i] - m_C[i - 1];
}

/**
 * ... text ...
 */
double RandomVar::Average() const {
    double expectation = 0.0;
    if (m_type == 0) {
        for (size_t i = 0; i < m_P.size(); i++) {
            expectation += m_P[i] * m_X[i];
        }
    } else if (m_type == 1) {
        for (size_t i = 0; i < m_S.size(); ++i) {
            expectation += m_S[i];
        }
        expectation /= m_S.size();
    }
    return expectation;
}

/**
 * ... text ...
 */
double RandomVar::Mean() const {
    return Average();
}

/**
 * ... text ...
 */
double RandomVar::Median() const {
    return Quantile(0.5);
}

/**
 * ... text ...
 */
double RandomVar::Variance() const {
    double var = 0;
    if (m_type == 0) {
        for (size_t i = 0; i < m_P.size(); i++)
            var += m_P[i] * m_X[i] * m_X[i];
        var -= Average() * Average();
    } else if (m_type == 1) {
        for (size_t i = 0; i < m_S.size(); i++)
            var += m_S[i] * m_S[i];
        var /= m_S.size();
        var -= Average() * Average();
    }
    return var;
}

/**
 * ... text ...
 */
double RandomVar::Vol() const {
    return sqrt(Variance());
}

/**
 * ... text ...
 */
double RandomVar::StandardDeviation() const {
    return Vol();
}

/**
 * ... text ...
 */
double RandomVar::Skeweness() const {
    double skew = 0;
    double mean = Average();
    for (size_t i = 0; i < m_P.size(); i++)
        skew += m_P[i] * pow(m_X[i] - mean, 3);
    skew = skew / pow(Variance(), 3 / 2);
    return skew;
}

/**
 * ... text ...
 */
double RandomVar::Kurtosis() const {
    double kurt = 0;
    double mean = Average();
    for (size_t i = 0; i < m_P.size(); i++)
        kurt += m_P[i] * pow(m_X[i] - mean, 4);
    kurt = kurt / pow(Variance(), 2);
    return kurt;
}

/**
 * ... text ...
 */
int RandomVar::Quantile_Index(double alpha) const {
    int index = 0;
    for (int i = 0; i< m_P.size(); i++) {
        if (m_C[i] > 1 - alpha) {
            index = i;
            break;
        }
    }
    return index;
}

/**
 * ... text ...
 */
double RandomVar::Quantile(double alpha) const {
    int index = this->Quantile_Index(alpha);
    return m_X[index];
}

/**
 * ... text ...
 */
double RandomVar::VaR(double alpha) const {
    return Quantile(1.0 - alpha);
}

/**
 * ... text ...
 */
double RandomVar::ExpectedShortFall(double alpha) const {
    int iVaR = this->Quantile_Index(alpha);
    double es = 0;
    for (int k = iVaR; k < m_P.size(); k++) {
        es += m_P[k] * m_X[k];
    }
      es /= alpha;
    return es;
}

/**
 * ... text ...
 */
double RandomVar::ExceedanceProbability(int index) const {
    double ep = 0;
    for (size_t k = index; k < m_P.size(); k++)
        ep += m_P[k];
    return ep;
}

/**
 * ... text ...
 */
double RandomVar::MeanExcess(int index) const {
    double alpha = ExceedanceProbability(index);
    double es = 0;
    for (size_t k = index; k < m_P.size(); k++)
        es += m_P[k] * m_X[k];
    es /= alpha;
    return es;
}

std::ostream &operator<<(std::ostream &os, const RandomVar &R) {
    std::ostringstream out;
    for (size_t k = 0; k < R.size(); k++)
        out << R.getX(k) << "\t" << R.getP(k) << "\t" << R.getC(k) << std::endl;
    return os << out.str();
};

void RandomVar::Print() {
    if (this->m_type == 1) {
        for (size_t s = 0; s < this->m_S.size(); s++) {
            cout << s << "\t" << this->m_S[s] << std::endl;
        }
    } else if (this->m_type == 0) {
        for (size_t s = 0; s < this->m_X.size(); s++) {
            cout << s << "\t" << this->m_X[s] << "\t" << this->m_P[s] << "\t" << this->m_C[s] << std::endl;
        }
    }
}

void RandomVar::ReadFromJSON(const char *fileName) {

    Poco::JSON::Parser loParser;
    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string json = buffer.str();
    // Parse the JSON and get the Results
    Poco::Dynamic::Var loParsedJson = loParser.parse(json);
    Poco::Dynamic::Var loParsedJsonResult = loParser.result();

    // Random variable data are an array of objects
    //[
    // {"value": 1, "probability" : 0.2, "cumulative" : 0.2},
    // {"value": 2, "probability" : 0.2, "cumulative" : 0.4},
    // {"value": 3, "probability" : 0.2, "cumulative" : 0.6},
    // {"value": 4, "probability" : 0.2, "cumulative" : 0.8},
    // {"value": 5, "probability" : 0.2, "cumulative" : 1.0}
    //]    

    Poco::JSON::Array::Ptr arr = loParsedJsonResult.extract<Poco::JSON::Array::Ptr>();
    size_t size = arr->size();
    cout << "Reading " << size << " records." << endl;

    m_P.resize(size);
    m_C.resize(size);
    m_X.resize(size);

    // Individual data rows
    Poco::JSON::Object::Ptr object;
    for (size_t i = 0; i < size; i++) {
        object = arr->getObject(i);
        this->setX(i, object->getValue<double>("value"));
        this->setP(i, object->getValue<double>("probability"));
        this->setC(i, object->getValue<double>("cumulative"));
    }

}
