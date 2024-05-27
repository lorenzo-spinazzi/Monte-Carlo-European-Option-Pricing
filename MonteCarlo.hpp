#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Payoff.hpp"

using namespace std;

class MonteCarlo{
    // Member variables (used for both GBM and Heston)
    protected:
        double Spot;
        double T;
        unsigned long Steps;
        double r;
        double sigma; // sqrt(v0)
        // Protected pure virtual function declaration for a single step simulation that will be overwritten
        virtual void simulateOneStep(std::vector<double> & prices, std::map<std::string, double> kwargs) const = 0;

    public:
        // Abstract class constructor
        MonteCarlo(double Spot, double T, unsigned long Steps, double r, double sigma): Spot(Spot), T(T), Steps(Steps), r(r), sigma(sigma){}
        // Public virtual function declaration to calculate price of option using Monte Carlo methadology
        virtual double getOptionPrice(unsigned long numOfPaths, Payoff& option)const;
};

class MonteCarloGBM: public MonteCarlo{

    public:
        // Inherit abstract class constructor
        MonteCarloGBM(double Spot, double T, unsigned long Steps, double r, double sigma): MonteCarlo(Spot, T, Steps, r, sigma){}
        // Declaration of GBM override of simulateOneStep
        virtual void simulateOneStep(std::vector<double> & prices, std::map<std::string, double> kwargs) const override;
};

class MonteCarloHeston: public MonteCarlo{
    // Heston model specific member variables
    protected:
        double theta;
        double rho;
        double k;
        double sigv;

    public:
        // Inherit abstract class constructor + include additional variable values
        MonteCarloHeston(double Spot, double T, unsigned long Steps, double r, double sigma, double theta, double rho, double k, double sigv): MonteCarlo(Spot, T, Steps, r, sigma), theta(theta), rho(rho), k(k), sigv(sigv){}
        // Declaration of Heston override of simulateOneStep
        virtual void simulateOneStep(std::vector<double> & prices,  std::map<std::string, double> kwargs) const override;
};