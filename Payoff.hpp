#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Payoff {
    public:
        // Strike member variable
        double strike;

        // Constructor
        Payoff(double strike): strike(strike){};

        // Pure virtual function for the payoff calculation
        virtual double operator()(std::vector<double> &path) const = 0;

        // Default destructor
        virtual ~Payoff() {};
    };

// Call option payoff declaration
class PayoffCall: public Payoff {
    public:
        PayoffCall(double strike): Payoff(strike){};
        virtual double operator()(std::vector<double> &path) const override;
};

// Put option payoff declaration
class PayoffPut: public Payoff {
    public:
        PayoffPut(double strike): Payoff(strike){};
        virtual double operator()(std::vector<double> &path) const override;
};





