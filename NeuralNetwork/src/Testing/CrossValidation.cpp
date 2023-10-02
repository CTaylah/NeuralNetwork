#include "CrossValidation.h"

void Test(NeuralNetwork network, const Eigen::MatrixXd& testingSet){
    Eigen::VectorXd prediction;
    Eigen::VectorXd target;
    double cost = 0.0;

    for(int i = 0; i < testingSet.cols(); i++){
        prediction = network.GetPrediction(testingSet.col(i));
        cost += Math::MeanSquaredError(prediction, testingSet.col(i));
    }

    cost /= testingSet.cols();
    std::cout << "Test cost: " << cost << std::endl;

    //Randomly select an example to visualize
    int index = 5;
    Eigen::VectorXd predictionExample = network.GetPrediction(testingSet.col(index));
    std::cout << "Prediction Cost: " << Math::MeanSquaredError(predictionExample, testingSet.col(index)) << std::endl;
    
    VectorToPPM((predictionExample * 255).cast<int>(), "Prediction");
    VectorToPPM((testingSet.col(index) * 255).cast<int>(), "Input");

}


void MonteCarloCV(NeuralNetwork network, double trainingPercent, Eigen::MatrixXd& examples, TrainingSettings settings)
{
    if(trainingPercent < 0 || trainingPercent > 1)
        throw std::invalid_argument("MonteCarloCV: trainingPercent must be between 0 and 1");

    Eigen::Ref<Eigen::MatrixXd> examplesRef = examples;
    Math::ShuffleMatrix(examplesRef);

    int trainingSize = examples.cols() * trainingPercent;
    int testSize = examples.cols() - trainingSize;

    Eigen::MatrixXd trainingSet = examples.block(0, 0, examples.rows(), trainingSize);
    Eigen::MatrixXd testingSet = examples.block(0, trainingSize, examples.rows(), testSize);

    network.Train(settings, trainingSet, trainingSet);
    Test(network, testingSet);


}

