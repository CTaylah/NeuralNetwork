#pragma once

#include "Math.h"

#include "Eigen/Dense"

#include <vector>
#include <iostream>

class Layer {

    public:
        //numInputs: number of neurons in previous layer
        Layer(int numInputs, int size) : m_size(size){
            if(numInputs < 0 || size <= 0){
                throw std::invalid_argument("Layer: invalid number of inputs or size");
            }

            m_weights = Eigen::MatrixXd::Random(size, numInputs) * sqrt(2.0 / numInputs);
            m_biases = Eigen::VectorXd::Zero(size);
        }
        
        Eigen::VectorXd FeedForward(const Eigen::VectorXd& inputs);

        Eigen::VectorXd GetActivations(){ return m_activations; }
        Eigen::VectorXd GetWeightedSums(){ return m_weightedSums; }
        Eigen::MatrixXd GetWeights(){ return m_weights; }
        Eigen::VectorXd GetBiases(){ return m_biases; }

        void SetWeights(const Eigen::MatrixXd& weights){ 
            if(weights.rows() != m_weights.rows() || weights.cols() != m_weights.cols())
                throw std::invalid_argument("Layer::SetWeights: invalid size of weights");

            m_weights = weights; 
        }

        void SetBiases(const Eigen::VectorXd& biases){ 
            if(biases.size() != m_biases.size())
                throw std::invalid_argument("Layer::SetBiases: invalid size of biases");

            m_biases = biases; 
        }

    private:
        //Number of rows = number of neurons
        Eigen::MatrixXd m_weights;
        Eigen::VectorXd m_biases;
        Eigen::VectorXd m_weightedSums;

        Eigen::VectorXd m_activations;
        int m_size;

    friend class InputLayer;    

};

class InputLayer : Layer{
    public:
        InputLayer(int size) : Layer(0, size) {}

    void SetActivations(const Eigen::VectorXd& activations){
        if(activations.size() != m_activations.size())
            throw std::invalid_argument("InputLayer::SetActivations: invalid size of activations");

        m_activations = activations;
    }
};