#include "MatrixManipulation.cpp"
#include "MatrixManipulation.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>


/**
-----------------------TODO-------------------------------------------------------------------------------------------
- IMPLEMENT TRAINING DATA FILE PARSING - MEDIUM -TESTING
- IMPLEMENT DATA FILE PARSING - MEDIUM -
- IMPLEMENT WEIGHT MATRIX POPULATION - EASY - TESTING
- IMPLEMENT INPUT LAYER POPULATION - EASY - TESTING 
- IMPLEMENT HIDDEN LAYER POPULATION - HARD
- IMPLEMENT OUTPUT LAYER POPULATION - HARD
- IMPLEMENT LAYER CALCULATION - HARD
- IMPLEMENT SIGMOID FUNCTION - HARD
- IMPLEMENT WEIGHT CORRECTION BACK PROPOGATION - HARD
- IMPLEMENT ERROR CALCULATION FUNCITON - HARD
- IMPLEMENT LOGGING - EASY
- IMPLEMENT COMMAND LINE ARGUMENT PARSING
----------------------------------------------------------------------------------------------------------------------
*/
class NeuralNetwork;
using namespace MatrixUtil;


	//default training data file
const char *DEFAULT_TRAINING_DATA_PATH = "mnist.train.csv";
const char *DEFAULT_DATA_PATH = "mnist_test.csv";


template <typename T>
struct Layer 
{

	vector<T> data;

	void addValue(T value) {
		data.push_back(value);
	}

	int size() {
		return data.size();
	}

};

const char* help_string = "-lr :\t specifies a learning rate in place of the default (.25)\n-t :\tspecifies a file path for training data in place of default\n-q :\tspecifies a file path for the data in which to query the Neural Network with\n-? :\tdisplay this text";
float learningRate = 0.25f;
int main(int argc, char** args) 
{
	char* trainingDataFilePath = (char*) malloc(257);
	char* dataFilePath = (char*) malloc(257);

	strcpy (trainingDataFilePath, DEFAULT_TRAINING_DATA_PATH);
	strcpy (dataFilePath, DEFAULT_DATA_PATH);
	for (int i = 0; i < argc; i++) {
		char* arg = args[i];
		if (arg[0] == '-') {
			if (strcmp(arg, "-lr")) 
				learningRate = atoi(args[i + 1]);
			
			else if (strcmp(arg, "-t"))	
					strcpy(trainingDataFilePath, trainingDataFilePath args[i + 1]);
			
			else if (strcmp(arg, "-q"))
					strcpy(dataFilePath, args[i + 1]);

		} else continue;
	}
	
	Layer<float> inputLayer {};
	Layer<float> hiddenLayer {};
	Layer<float> outputLayer {};
	NeuralNetwork net(inputLayer, hiddenLayer, outputLayer, learningRate);
	net.init();
	net.train();
}


class NeuralNetwork
{

public:


	NeuralNetwork(Layer<float>& newInputLayer, Layer<float>& newHiddenLayer, Layer<float>& newOutputLayer, float newLearningRate)
	{
		this->inputLayer = newInputLayer;
		this->hiddenLayer = newHiddenLayer;
		this->outputLayer = newOutputLayer;
		this->learningRate = newLearningRate;
	}

	void init() {
		cout << "Initiating NeuralNetwork\n";
		populateInputLayerTraining();
		populateWeightMatrix();
	}

	void setDataFilePath(char* filePath) {
		strcpy (this->dataFilePath, filePath);
	}

	void setTrainingDataFilePath(char* filePath) {
		strcpy(this->trainingFilePath, filePath);
	}


	void train() 
	{
		cout << "Initiating training procedure \n";
	}

	void query()
	{

	}


private:

	Layer<float> inputLayer;
	Layer<float> hiddenLayer;
	Layer<float> outputLayer;
	Matrix<float> inputToHiddenLinks;
	Matrix<float> hiddenToOutputLinks;

	vector<int> trainingAnswers {};//holds the answer to each sample of data
	
	float learningRate;

	char *dataFilePath;
	char *trainingFilePath;
	ifstream trainingFile;

	//populates all the layer with training data
	void populateInputLayerTraining() {
		if (!trainingFile.is_open()) cout << "Training file is not open\n";
		cout << "reading training data...\n";
		while(!trainingFile.eof())
		{
			char *line = (char*) malloc (sizeof(char*) * 1025);//1024 + 1 for null terminator
			trainingFile.getline(line, 1024);//read a line into the cstring
			parseTrainingDataLine(line);
		}
		cout << "Sucessful\n";

	}


	//parses one line of data from the training file, and inserts it into the input layer
	void parseTrainingDataLine(const char* line) 
	{	
		cout << "parsing training data\n";
		char* lineCopy = (char*) malloc (sizeof(line));
		strcpy(lineCopy, line);

		trainingAnswers.push_back(stoi(strtok(lineCopy, ",")));
		char *token = (char*) malloc(4);

		 while (token != NULL)
		  {
		    inputLayer.addValue(stoi(token));
		    strcpy(token, strtok(lineCopy, ","));
		  }

		free (lineCopy);
		free (token);
	}	

	void parseDataLine(char* line)
	{

	}

	void openTrainingFile() {
		cout << "opening training data file...\n";
		trainingFile.open(trainingFilePath);
	}

	//populates the weight value matrix with random normalized values
	void populateWeightMatrix()
	{
		std::srand(std::time(nullptr));
		for (int i = 0; i < inputLayer.size(); i++) {
			for (int j = 0; j < hiddenLayer.size(); j++) {
				inputToHiddenLinks.add((float) std::rand() / RAND_MAX);
			}
		}

		for (int i = 0; i < hiddenLayer.size(); i++) {
			for (int j = 0; j < outputLayer.size(); j++) {
				hiddenToOutputLinks.add((float) std::rand() / RAND_MAX);
			}
		}

	}	

	//normalize the value to between 0.01 - 0.99
	float normalizeValue(int value) 
	{
		return (float) ((value / 255.0F) * .99F);
	}	


};

