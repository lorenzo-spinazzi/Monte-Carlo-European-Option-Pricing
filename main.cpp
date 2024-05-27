#include <iostream>
#include <cmath>
#include "Payoff.hpp"
#include "MonteCarlo.hpp"
#include "Normal.h"
using namespace std;

int main(){

    // Given parameters to test
    double S0;
    double r;
    double T;
    double sigma;
    double strike;
    unsigned long steps;
    double k;
    double theta;
    double sigv;
    double rho;
    unsigned long numOfPaths;

    // User inputs parameters
    cout << "Enter stock spot price (input type: double): ";
    cin >> S0;
    cout << endl;
    cout << "Enter risk-free rate (input type: double): ";
    cin >> r;
    cout << endl;
    cout << "Enter time to maturity in years (input type: double): ";
    cin >> T;
    cout << endl;
    cout << "Enter stock volatility (input type: double): ";
    cin >> sigma;
    cout << endl;
    cout << "Enter strike price (input type: double): ";
    cin >> strike;
    cout << endl;
    cout << "Enter number of time steps for simulation (input type: int): ";
    cin >> steps;
    cout << endl;
    cout << "Enter stock long-run average variance (input type: double): ";
    cin >> theta;
    cout << endl;
    cout << "Enter reversion rate of stock variance to long-run average variance (input type: double): ";
    cin >> k;
    cout << endl;
    cout << "Enter the volatility of the volatility (input type: double): ";
    cin >> sigv;
    cout << endl;
    cout << "Enter the correlation of the two Brownian motions (input type: double): ";
    cin >> rho;
    cout << endl;
    cout << "Enter the number of simulations (input type: int): ";
    cin >> numOfPaths;
    cout << endl;

    // Create Payoff objects for both European call and European put
    PayoffCall Payoff_call(strike);
    PayoffPut Payoff_put(strike);

    // Geometric Brownian Motion Implementation
    cout << "#####################################" << endl;
    cout << "GBM MONTE CARLO SIMULATION RESULTS" << endl;
    cout << "#####################################" << endl;
    // Create MonteCarlo object for GBM implementation
    MonteCarloGBM GBM_MC(S0, T, steps, r, sigma);
    // Calculate European call option price using GBM
    double GBM_MC_call_output = GBM_MC.getOptionPrice(numOfPaths, Payoff_call);
    cout << "European Call Option Price: $" << GBM_MC_call_output << endl;
    // Calculate European put option price using GBM
    double GBM_MC_put_output = GBM_MC.getOptionPrice(numOfPaths, Payoff_put);
    cout << "European Put Option Price: $" << GBM_MC_put_output<< endl;
    // Put-call parity test: D * K - P = S - C
    double LHS = exp(-r * T) * strike - GBM_MC_put_output;
    double RHS = S0 - GBM_MC_call_output;
    cout << "Put-call parity Test (LHS - RHS): " << (LHS - RHS) << endl;

    // Heston Model Implementation
    cout << "#####################################" << endl;
    cout << "HESTON MODEL SIMULATION RESULTS" << endl;
    cout << "#####################################" << endl;
    // Create MonteCarlo object for Heston implementation
    MonteCarloHeston Heston_MC(S0, T, steps, r, sigma, theta, rho, k, sigv);
    // Calculate European call option price using Heston
    double Heston_MC_call_output = Heston_MC.getOptionPrice(numOfPaths, Payoff_call);
    cout << "European Call Option Price: $" << Heston_MC_call_output<< endl;
    // Calculate European put option price using Heston
    double Heston_MC_put_output = Heston_MC.getOptionPrice(numOfPaths, Payoff_put);
    cout << "European Put Option Price: $" << Heston_MC_put_output << endl;
    // Put-call parity test: D * K - P = S - C
    LHS = exp(-r * T) * strike - Heston_MC_put_output;
    RHS = S0 - Heston_MC_call_output;
    cout << "Put-call parity Test (LHS - RHS): " << (LHS - RHS) << endl;

    return 0;
}