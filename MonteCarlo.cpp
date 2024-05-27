#include <iostream>
#include <cmath>
#include "MonteCarlo.hpp"
#include "Payoff.hpp"
#include "Normal.h"
using namespace std;


void MonteCarloGBM::simulateOneStep(vector<double> & prices, map<string, double> kwargs) const {
    // Standard normal random variable
    double z = kwargs["z"];
    // Latest price in path
    double spot = prices[prices.size()-1];
    // dSt
    double increment = r * spot * (T/Steps) + sqrt(T/Steps) * z * sigma * spot;
    // St + dSt added to price vector
    prices.push_back(spot + increment);
}

void MonteCarloHeston::simulateOneStep(vector<double> & prices, map<string, double> kwargs) const {
    // Change in first Brownian motion (dWt_1)
    double dwt_1 = kwargs["z"] * sqrt(T/Steps);
    // Take into account correlation between Wiener processes
    // dWt_1 * dWt_2 = rho * dt -> dWt_2 = (rho * dt) / dWt_1
    double dwt_2 = (rho * (T/Steps)) / dwt_1;
    // Variance value
    double v = kwargs["v"];
    double spot = prices[prices.size()-1];
    // dSt
    double dSt = r * spot * (T/Steps) + sqrt(v) * spot * dwt_1;
    prices.push_back(spot + dSt);
    // dVt
    kwargs["v"] = v  + k * (theta - v) * (T/Steps) + sigv * sqrt(v) * dwt_2;
}


double MonteCarlo::getOptionPrice(unsigned long numOfPaths, Payoff& option) const{
    // Allows dynamic changing of inputs to accomodate for change in model
    map<string, double> kwargs;
    // Initialize vector of path payoffs 
    vector<double> payoffs = {};
    // Initialize sum value of payoffs
    double sum = 0.0;
    // numOfPaths number of simulations
    for(int i = 0; i < numOfPaths; i++){
        // First price value is spot price
        vector<double> prices = {Spot};
        // First variance is sigma^2
        double vi = pow(sigma, 2);
        // Step simulation for Steps number of steps
        for(int j = 0; j < Steps; j++){
            // Generate standard normal random variable
            kwargs["z"] = generateNormal();
            if(j == 0){
                // First map value for variance in Heston model is sigma^2, MonteCarloHeston::simulateOneStep will take care of rest of evolution
                kwargs["v"] = vi;
            }
            // Virtual function usage permits for correct use of simulateOneStep according to underlying model
            simulateOneStep(prices, kwargs);
        }
        // Calculate option payoff based on terminal node value and strike, add to vector of payoffs
        payoffs.push_back(option.operator()(prices));
        // Add payoff value to running sum
        sum += payoffs.back();
    }
    // Return present value of average payoff across all simulations
    return ((exp(-r * T) / numOfPaths) * sum);
}
