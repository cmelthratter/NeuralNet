#include "MatrixManipulation.cpp"
#include "MatrixManipulation.hpp"
#include <iostream>
#include <vector>

static bool training = false;

using namespace MatrixUtil;


template <typename T>
struct Node
{
	Matrix<T> matrix;
	T weight;
};

template <typename T>
struct Layer 
{

	vector<Node<T>> data;

};

int main() {};


template <typename T>
class NeuralNetwork
{

public:

	NeuralNetwork(Layer<T>& newInputLayer, Layer<T>& newHiddenLayer, Layer<T>& newOutputLayer, T newLearningRate)
	{
		this->inputLayer = newInputLayer;
		this->hiddenLayer = newHiddenLayer;
		this->outputLayer = newOutputLayer;
		this->learningRate = newLearningRate;
	}

	float normalize(int value) 
	{
		return (float) ((value / 255.0F) * .99F);
	}	

	void train() 
	{


	}

	void query()
	{

	}


	void parseData() 
	{

	}
private:

	Layer<T>& inputLayer;
	Layer<T>& hiddenLayer;
	Layer<T>& outputLayer;
	Matrix<T>& inputToHiddenLinks;
	Matrix<T>& hiddenToOutputLinks;
	
	T learningRate;

};

