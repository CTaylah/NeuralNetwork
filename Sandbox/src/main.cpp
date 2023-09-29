#include "Model/NeuralNetwork.h"
#include "Common/Data.h"
#include "Testing/CrossValidation.h"

#include <iostream>
#include <ctime>
#include <omp.h>

int main(int argc, char** argv){

    srand(time(NULL));

    Eigen::MatrixXi examples(784, 60000);

    Eigen::Ref<Eigen::MatrixXi> examplesRef = examples; 
    
    bool success = ReadMNISTImages("MNIST/training_images/train-images.idx3-ubyte", examplesRef);

    if(!success){
        std::cout << "Failed to read MNIST data" << std::endl;
        return 1;
    }

    Eigen::MatrixXd examplesDouble = examplesRef.cast<double>();
    examplesDouble = examplesDouble / 255.0;

    //For testing purposes, only using subset of data
    Eigen::MatrixXd examplesSubset = examplesDouble.block(0, 0, examplesDouble.rows(), 5600);

    NeuralNetwork neuralNetwork({784, 162, 784});
    TrainingSettings settings(70, 20, 0.00087);
    
    NeuralNetwork network2({784, 356, 784});

    MonteCarloCV(neuralNetwork, 0.8, examplesSubset, settings);

    //MonteCarloCV(network2, 0.8, examplesSubset, settings);
}
