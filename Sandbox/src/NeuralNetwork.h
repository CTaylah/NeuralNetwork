#pragma once

#include "Layer.h"

#include "Eigen/Dense"

#include <vector>


struct Topology
{
    //Do not include input layer in neuronsPerLayer
    Topology(int inputSize, std::vector<unsigned int> neuronsPerLayer) 
        : inputSize(inputSize), neuronsPerLayer(neuronsPerLayer) {}
    unsigned int inputSize, outputSize;

    std::vector<unsigned int> neuronsPerLayer;

};

class NeuralNetwork {

    public:
        NeuralNetwork(Topology topology); 

        
        ~NeuralNetwork() = default;
        Eigen::VectorXd Prediction();

    private:
        Topology m_topology;
        std::vector<Layer> m_layers;
};