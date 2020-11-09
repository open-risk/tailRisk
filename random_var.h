/** 
 * File:   random_var.h
 * Date: Mon Nov  9 10:31:35 CET 2020
 * Author: Open Risk  (www.openriskmanagement.com)
 *
 */

#ifndef RANDOM_VARIABLE_H
#define RANDOM_VARIABLE_H

#include <iostream>
#include <armadillo>

using namespace arma;

class RandomVar {
    friend std::ostream &operator<<(std::ostream &os, const RandomVar &R);

public:

    // constructor with size and distribution type

    RandomVar(size_t S, int type) {
        if (type == 0) {
            m_type = 0;
            m_P.resize(S);
            m_C.resize(S);
            m_X.resize(S);
        } else if (type == 1) {
            m_type = 1;
            m_S.resize(S);
        } else {
            cout << "Error in random variable representation type" << endl;
        }
    }

    // constructor directly from existing data

    RandomVar(vec x, vec p, const int size) {
        m_type = 0;
        m_X.resize(size);
        m_P.resize(size);
        m_C.resize(size);
        for (int i = 0; i < size; i++) {
            m_X[i] = x[i];
            m_P[i] = p[i];
        }
    }

    // overload assignment operator

    RandomVar &operator=(const RandomVar &R);

    size_t size() const {
        return m_P.size();
    };

    int type() const {
        return m_type;
    };

    double getP(int index) const {
        return m_P[index];
    };

    double getC(int index) const {
        return m_C[index];
    };

    double getX(int index) const {
        return m_X[index];
    };

    double getS(int index) const {
        return m_S[index];
    };

    void setP(int index, double arg) {
        m_P[index] = arg;
    };

    void setC(int index, double arg) {
        m_C[index] = arg;
    };

    void setX(int index, double arg) {
        m_X[index] = arg;
    };

    void setS(int index, double arg) {
        m_S[index] = arg;
    };

    void Sort();

    void Cumulative();

    void Probability();

    double Average() const;

    double Mean() const;

    double Median() const;

    double Variance() const;

    double Vol() const;

    double StandardDeviation() const;

    double Kurtosis() const;

    double Skeweness() const;

    double ExpectedShortFall(double alpha) const;

    double ExceedanceProbability(int index) const;

    double MeanExcess(int index) const;

    double Quantile(double alpha) const;

    double VaR(double alpha) const;

    int Quantile_Index(double alpha) const;

    void ReadFromJSON(const char *fileName);

    void Print();

private:
    // 0 Type: exact representation
    // 1 Type: sampling representation
    int m_type;
    vec m_P; // storage of probability mass
    vec m_C; // storage of cumulative probability
    vec m_X; // storage of discrete values (random variable range)
    vec m_S; // storage of sampling data from simulation experiments
};

#endif
