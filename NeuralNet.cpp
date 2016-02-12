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
- IMPLEMENT INPUT LAYER POPULATION - EASY - DONE
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
using namespace std;


	//default training data file
const char *DEFAULT_TRAINING_DATA_PATH = "mnist_train.csv";
const char *DEFAULT_DATA_PATH = "mnist_test.csv";

class NeuralNetwork
{

public:


	NeuralNetwork(int numberOfInputNodes,
				  int numberOfHiddenNodes,
				  int numberOfOutputNodes,
				  float newLearningRate) : inputLayerNodes(numberOfInputNodes),
										   hiddenLayerNodes(numberOfHiddenNodes),
										   outputLayerNodes(numberOfOutputNodes),
										   learningRate(newLearningRate)

	{
	}

	void init() {
		cout << "Initiating NeuralNetwork\n";
		populateInputLayerTraining();
		populateWeightMatrix();
	}

	void setDataFilePath(const char* filePath) {
		this->dataFilePath = (char*) malloc(sizeof(filePath));
		strcpy (this->dataFilePath, filePath);
	}

	void setTrainingDataFilePath(const char* filePath) {
		this->trainingFilePath = (char*) malloc(sizeof(filePath));
		strcpy(this->trainingFilePath, filePath);
	}


	void train() 
	{
		this->init();
		cout << "Initiating training procedure \n";

	}

	void query()
	{

	}

	void printNeuralNetwork() {
		cout << "INPUT LAYER:\n";
		cout << inputLayer;

		cout << "INPUT TO HIDDEN WEIGHT MATRIX:\n";
		cout << inputToHiddenLinks;
		cout << "HIDDEN LAYER:\n";
		cout << hiddenLayer;
		cout << "HIDDEN TO OUTPUT WEIGHT MATRIX:\n";
		cout << hiddenToOutputLinks;
		cout << "OUTPUT LAYER:\n";
		cout << outputLayer;


		
	}

	void printVector(vector<float> v) {
		cout << "[ ";
		for (int i = 0; i < v.size() - 1; i++) {
			cout << v[i] << ", ";
		}
		cout << v.back() << "] \n";
	}


private:

	int inputLayerNodes;
	int hiddenLayerNodes;
	int outputLayerNodes;

	Matrix<float> inputLayer;
	Matrix<float> hiddenLayer;
	Matrix<float> outputLayer;
	Matrix<float> inputToHiddenLinks;
	Matrix<float> hiddenToOutputLinks;

	vector<int> trainingAnswers;
	
	float learningRate;

	char *dataFilePath;
	char *trainingFilePath;
	ifstream trainingFile;

	//populates all the layer with training data
	void populateInputLayerTraining() {
		if (!trainingFile.is_open()) openTrainingFile();
		//while(!trainingFile.eof())
		//{
			string line;
			std::getline(trainingFile, line);//read a line into the cstring
			trainingAnswers.push_back(parseTrainingDataLine(line));
		//}
		cout << "Successful\n";

	}


	//parses one line of data from the training file, and inserts it into the input layer
	//return: the number displayed by the pixel data in this line.
	int parseTrainingDataLine(string line) 
	{	 

		int trainingAnswer = -1;
		string token = "";
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != ',') token += line[i];
			else {
				inputLayer.push_back(normalizeValue(stoi(token)));
				token = "";
			}
		}



		return trainingAnswer;
	}	

	void parseDataLine(char* line)
	{

	}

	void openTrainingFile() {
		trainingFile.open(trainingFilePath);
	}

	//populates the weight value matrix with random normalized values
	void populateWeightMatrix()
	{
		std::srand(std::time(nullptr));
		for (int i = 0; i < this->inputLayer.capacity(); i++) {
			vector<float> row(this->hiddenLayer.capacity());
			for (int j = 0; j < this->hiddenLayer.capacity(); j++) {
				float rand = getRandomFloat();
				row[j] = rand;
			}

			this->inputToHiddenLinks.addRow(row);
		}

		for (int i = 0; i < this->hiddenLayer.capacity(); i++) {
			vector<float> row(this->outputLayer.capacity());
			for (int j = 0; j < this->outputLayer.capacity(); j++) {
				float rand = getRandomFloat();
				row[j] = rand;
			}

			this->hiddenToOutputLinks.addRow(row);

		}

	}	
	//returns a float between .01 and .99 for the weight matrix
	static float getRandomFloat() {
		int randInt = (std::rand() % 99);
		float rand = (float) (randInt / 100.0F) + 0.01F;
		return rand;
	}

	//normalize the value to between 0.01 - 0.99
	static float normalizeValue(int value)
	{
		return (float) (((value / 255.0F) * .99F) + .01F) ;
	}	


};

const char* help_string = "-lr :\t specifies a learning rate in place of the default (0.25)\n-t :\tspecifies a file path for training data in place of default\n-q :\tspecifies a file path for the data in which to query the Neural Network with\n-? :\tdisplay this text";
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
					strcpy(trainingDataFilePath, args[i + 1]);
			
			else if (strcmp(arg, "-q"))
					strcpy(dataFilePath, args[i + 1]);

		} else continue;
	}
	NeuralNetwork net(784, 100, 10, learningRate);
	net.setTrainingDataFilePath(trainingDataFilePath);
	net.setDataFilePath(dataFilePath);
	net.train();
}

