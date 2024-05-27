#include <iostream>
#include <cmath>
#include "Payoff.hpp"
using namespace std;

// Call option payoff function definition
double PayoffCall::operator()(std::vector<double> &path) const{
    // [S - K]
    double output = path.back() - strike;

    // max[S - K, 0]
    output = (output > 0) ? output : 0;
    return output;
}

// Put option payoff function definition
double PayoffPut::operator()(std::vector<double> &path) const{
    // [K - S]
    double output = strike - path.back();

    // max[K - S, 0]
    output = (output > 0) ? output : 0;
    return output;

}



