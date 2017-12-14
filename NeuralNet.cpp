#include "MatrixManipulation.cpp"
#include "MatrixManipulation.hpp"
#include <iostream>
#include <vector>
#include <fstream>


/**
-----------------------TODO-------------------------------------------------------------------------------------------
- IMPLEMENT DATA FILE PARSING - MEDIUM
- IMPLEMENT WEIGHT MATRIX POPULATION - EASY
- IMPLEMENT INPUT LAYER POPULATION - EASY
- IMPLEMENT HIDDEN LAYER POPULATION - HARD
- IMPLEMENT OUTPUT LAYER POPULATION - HARD
- IMPLEMENT LAYER CALCULATION - HARD
- IMPLEMENT SIGMOID FUNCTION - HARD
- IMPLEMENT WEIGHT CORRECTION BACK PROPOGATION - HARD
- IMPLEMENT ERROR CALCULATION FUNCITON - HARD
- IMPLEMENT LOGGING - EASY
----------------------------------------------------------------------------------------------------------------------
*/

using namespace MatrixUtil;


template <typename T>
struct Layer 
{

	vector<T> data;
	void addValues(T value) {
		data.push_back(value);
	}

};

int main() {};


class NeuralNetwork
{

public:

	//default training data file
	const char *DEFAULT_TRAINING_DATA_FP = "mnist.train.csv";


	NeuralNetwork(Layer<float>& newInputLayer, Layer<float>& newHiddenLayer, Layer<float>& newOutputLayer, float newLearningRate)
	{
		this->inputLayer = newInputLayer;
		this->hiddenLayer = newHiddenLayer;
		this->outputLayer = newOutputLayer;
		this->learningRate = newLearningRate;
		setTrainingDataFp(DEFAULT_TRAINING_DATA_FP);
	}

	void init() {
		cout << "Initiating NeuralNetwork";
		openTrainingFile();
		cout << "Opened training data file\n";
		char *line = malloc (sizeof(char*) * 1024);
		


	}

	void setTrainingDataFp(char* filePath) {
		strcpy (this->trainingDataFp, filePath);
	}


	void train() 
	{

	}

	void query()
	{

	}


private:

	Layer<T>& inputLayer;
	Layer<T>& hiddenLayer;
	Layer<T>& outputLayer;
	Matrix<T>& inputToHiddenLinks;
	Matrix<T>& hiddenToOutputLinks;

	vector<int> trainingAnswers {};//holds the answer to each sample of data
	
	float learningRate;

	char *trainingDataFp;
	ifstream trainingFile;



	//parses one line of data from the training file.
	void parseTrainingData(char* line) 
	{	
		cout << "parsing training data\n";
		trainingAnswers.push_back(atoi(line[0]));
		for (int i = 1; i < sizeof(line); i++ ) {
			if (line[i] != ',') inputLayer.addValue(normalizeValue(atoi(line[i])));
		}
	}	

	void openTrainingFile() {
		trainingFile.open(trainingDataFp);
	}

	//populates the weight value matrix with random normalized values
	void populateWeightMatrix()
	{

	}	

	//normalize the value to between 0.01 - 0.99
	float normalizeValue(int value) 
	{
		return (float) ((value / 255.0F) * .99F);
	}	


};

