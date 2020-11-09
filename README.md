# tailRisk
A library for the calculation of various tail risk measures

PRELIMINARY RELEASE

## Dependencies
* Poco
* Armadillo

## Examples
The data directory contains sample datafiles with various sampled distributions

```c++
    // Reading in some data for a type 0 representation (discrete distribution)
int LossGrid = 1000;
int DataType = 0;
RandomVar L(LossGrid, DataType);
L.ReadFromJSON("../data/example5.json");
L.Print();

// Calculate various measures
double alpha = 0.8;
int threshold = 0;

std::cout << "Mean Value: " << L.Mean() << std::endl;
std::cout << "Median Value: " << L.Median() << std::endl;
std::cout << "STD Value: " << L.StandardDeviation() << std::endl;
std::cout << "Kurtosis: " << L.Kurtosis() << std::endl;
std::cout << "Skeweness: " << L.Skeweness() << std::endl;
std::cout << "Quantile @ " << alpha << ": " << L.Quantile(alpha) << std::endl;
std::cout << "Quantile Index @ " << alpha << ": " << L.Quantile_Index(alpha) << std::endl;
std::cout << "VaR @ " << alpha << ": " << L.VaR(alpha) << std::endl;
std::cout << "Expected Shortfall @ " << alpha << ": " << L.ExpectedShortFall(alpha) << std::endl;
std::cout << "Exceedance Probability: " << L.ExceedanceProbability(threshold) << std::endl;
std::cout << "Mean Excess: " << L.MeanExcess(threshold ) << std::endl;
```