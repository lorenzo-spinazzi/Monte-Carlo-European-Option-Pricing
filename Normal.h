#pragma once
#include <random>
using namespace std;

inline double generateNormal() {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> dist(0, 1);
    return dist(gen);
}