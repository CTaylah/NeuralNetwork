#pragma once

#include <random>


double RandomDouble(double min, double max){
    std::uniform_real_distribution<double> uniformReal(min,max);
    std::default_random_engine randomEngine;
    return uniformReal(randomEngine);
}

double ReLU(double x){
    return x > 0 ? x : 0;
}

double ReLUDerivative(double x){
    return x > 0 ? 1 : 0;
}