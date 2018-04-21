#include "MatrixManipulation.cpp"
#include "MatrixManipulation.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <chrono>


/**
-----------------------TODO-------------------------------------------------------------------------------------------
- IMPLEMENT TRAINING DATA FILE PARSING - MEDIUM - DONE
- IMPLEMENT DATA FILE PARSING - MEDIUM - DONE
- IMPLEMENT WEIGHT MATRIX POPULATION - EASY - DONE
- IMPLEMENT INPUT LAYER POPULATION - EASY - DONE
- IMPLEMENT HIDDEN LAYER POPULATION - HARD - DONE
- IMPLEMENT OUTPUT LAYER POPULATION - HARD - DONE
- IMPLEMENT SIGMOID FUNCTION - EASY - DONE
- IMPLEMENT WEIGHT CORRECTION BACK PROPOGATION - HARD - IN PROGRESS
- IMPLEMENT ERROR CALCULATION FUNCTION - EASY - DONE
- IMPLEMENT LOGGING - EASY - ONGOING
- IMPLEMENT COMMAND LINE ARGUMENT PARSING - EASY - DONE
----------------------------------------------------------------------------------------------------------------------
*/
class NeuralNetwork;
using namespace MatrixUtil;
using namespace std;


	//default training data file
const char *DEFAULT_TRAINING_DATA_PATH = "mnist_train.csv";
const char *DEFAULT_DATA_PATH = "mnist_test.csv";
const int AMOUNT_OF_NUMBERS_FOR_TRAINING = 100;

class NeuralNetwork
{

public:


	NeuralNetwork(int numberOfInputNodes,
				  int numberOfHiddenNodes,
				  int numberOfOutputNodes,
				  float newLearningRate) : inputLayer(1, numberOfInputNodes),
										   inputToHiddenLinks(numberOfInputNodes, numberOfHiddenNodes),
										   hiddenLayer(1, numberOfHiddenNodes),
										   hiddenToOutputLinks(numberOfHiddenNodes, numberOfOutputNodes),
										   outputLayer(1, numberOfOutputNodes),
										   hiddenNodes(numberOfHiddenNodes),
										   outputNodes(numberOfOutputNodes),
										   learningRate(newLearningRate)

	{
		
		srand(time(nullptr));
		numCorrect = 0;
		//cout << "Created new NeuralNetwork\n";
	}

	void init() 
	{
		//cout << "Initiating NeuralNetwork\n";
		
		populateWeightMatrix();
	}

	void setDataFilePath(const char* filePath) 
	{
		this->dataFilePath = (char*) malloc(sizeof(filePath));
		strcpy (this->dataFilePath, filePath);
	}

	void setTrainingDataFilePath(const char* filePath) 
	{
		this->trainingFilePath = (char*) malloc(sizeof(filePath));
		strcpy(this->trainingFilePath, filePath);
	}


	void train() 
	{
		this->init();
		string line = "";
		//cout << "Initiating training procedure \n";
		openTrainingFile();
		int count = 0;
		time_t startTime = clock();
		while(trainingFile.is_open() && count++ < AMOUNT_OF_NUMBERS_FOR_TRAINING)
		{
			
			time_t iterStartTime = clock();
			trainingFile >> line;
			currentAnswer = parseTrainingDataLine(line);
			calculateHiddenLayer();
			calculateOutputLayer();
			calculateErrorValues();
			time_t iterEndTime = clock();
			int label = getCorrectLabel();
			if (label == currentAnswer) numCorrect++;
			cout << "The Neural Network says... " << label << " ! Answer: " << currentAnswer <<  "; Total time for calculation: " << (double) ((iterEndTime - iterStartTime) / (double) CLOCKS_PER_SEC) << " seconds. " << '\n';

		}
		time_t endTime = clock();
		cout <<  numCorrect << " out of 100 correct, " <<  numCorrect << "% accuracy; completed in " << (double) ((endTime - startTime) / CLOCKS_PER_SEC) << " seconds."<< '\n';
		count = 0;
		numCorrect = 0;
		startTime = clock();
		while(trainingFile.is_open() && count++ < AMOUNT_OF_NUMBERS_FOR_TRAINING)
		{
			
			time_t iterStartTime = clock();
			trainingFile >> line;
			currentAnswer = parseTrainingDataLine(line);
			calculateHiddenLayer();
			calculateOutputLayer();
			time_t iterEndTime = clock();
			int label = getCorrectLabel();
			if (label == currentAnswer) numCorrect++;
			cout << "The Neural Network says... " << label << " ! Answer: " << currentAnswer <<  "; Total time for calculation: " << (double) ((iterEndTime - iterStartTime) / (double) CLOCKS_PER_SEC) << " seconds. " << '\n';

		}
		endTime = clock();
		cout <<  numCorrect << " out of 100 correct, " <<  numCorrect << "% accuracy; completed in " << (double) ((endTime - startTime) / CLOCKS_PER_SEC) << " seconds."<< '\n';
		

	}

	void query()
	{
		this->init();
		cout << "Querying the Neural Network...\n";
		calculateHiddenLayer();
		calculateOutputLayer();
		cout << "The Neural Network says... " << getCorrectLabel() << " !\n";
	}


	friend ostream& operator<<(ostream& os, NeuralNetwork& operand) 
	{
		operand.printNeuralNetwork();
		return os;
	}


private:

	Matrix<float> inputLayer;
	Matrix<float> hiddenLayer;
	Matrix<float> outputLayer;
	Matrix<float> inputToHiddenLinks;
	Matrix<float> hiddenToOutputLinks;

	vector<int> trainingAnswers;
	int currentAnswer;

	int inputNodes;
	int hiddenNodes;
	int outputNodes;
	int numCorrect;
	
	float learningRate;

	char *dataFilePath;
	char *trainingFilePath;
	ifstream trainingFile;


	void calculateHiddenLayer() 
	{
		//cout << "Calculating hidden layer\n";
		this->hiddenLayer = (inputLayer * inputToHiddenLinks);
		for (int i = 0; i < this->hiddenLayer.getRows(); i++)
		{
			for (int j = 0; j < this->hiddenLayer.getColumns(); j++)
			{
				this->hiddenLayer[i][j] = sigmoid(this->hiddenLayer[i][j]);
			}
		}
	}

	void calculateOutputLayer() 
	{
		//cout << "Calculating output layer\n";
		this->outputLayer = (hiddenLayer * hiddenToOutputLinks);
		for (int i = 0; i < this->outputLayer.getRows(); i++)
		{
			for (int j = 0; j < this->outputLayer.getColumns(); j++)
			{
				this->outputLayer[i][j] = sigmoid(this->outputLayer[i][j]);
			}
		}
	}

	int getCorrectLabel() 
	{
		float max = -1.0f;
		int label = -1;
		int i;
		for (i = 0; i < outputLayer.getColumns(); i++) {
			if (outputLayer[0][i] > max) 
				{
					label = i;
					max = outputLayer[0][i];
				}
		}
		cout << "Output Values: " << outputLayer << '\n';
		return label;
	}
	//TODO
	void calculateErrorValues() 
	{
		//Matrix<float> outputT = &(outputLayer.transpose());
		Matrix<float> e_row(outputLayer);
		for (int i = 0; i < e_row.getRows(); i++)
		{
			for (int j = 0; j < e_row.getColumns(); j++ )
			{
				
				if (j == currentAnswer) e_row[i][j] -= (0.95);
				else e_row[i][j] -= 0.01;
			}
		}

		for (int i = 0; i < hiddenToOutputLinks.getRows(); i++)
		{
			for (int j = 0; j < hiddenToOutputLinks.getColumns(); j++)
			{
				
				hiddenToOutputLinks[i][j] += learningRate * (-(e_row[0][j]) 
					* sigmoid(outputLayer[0][j]) 
					* (1 - sigmoid(outputLayer[0][j])) 
					* outputLayer.transpose()[j][0]);
			}
		}

		

		for (int i = 0; i < inputToHiddenLinks.getRows(); i++)
		{
			for (int j = 0; j < inputToHiddenLinks.getColumns(); j++)
			{
				inputToHiddenLinks[i][j] +=  learningRate * (-(e_row[0][j]) 
					* sigmoid(hiddenLayer[0][j]) 
					* (1 - sigmoid(hiddenLayer[0][j])) 
					* hiddenLayer.transpose()[j][0]);
			}
		}
	}

	double sigmoid(float f)
	{
		return  (double) (1 / (1 + pow(M_E, (double) -(f))));
	}


	//parses one line of data from the training file, and inserts it into the input layer
	//return: the number displayed by the pixel data in this line.
	int parseTrainingDataLine(string line) 
	{	 
		//cout << "parsing training data: " << line.length() << "\n";

		string token = "";
		token += line[0];
		int trainingAnswer = stoi(token);
		token = "";
		int tokenCount = 0;
		for (int i = 2; i < line.length(); i++) {

			if (line[i] != ',') token += line[i];
			else 
			{
				float normalizedValue = normalizeValue(stoi(token));
				this->inputLayer[0][tokenCount++] = normalizedValue; 
				token = "";
			}
		}



		return trainingAnswer;
	}	

	void parseDataLine(string line)
	{

	}

	void openTrainingFile() 
	{
		trainingFile.open(trainingFilePath);
	}

	//populates the weight value matrix with random normalized values
	void populateWeightMatrix()
	{
		//cout << "populating weight matrix\n";
		for (int i = 0; i < this->inputLayer.getColumns(); i++) {
			vector<float> row(this->hiddenLayer.getColumns());
			for (int j = 0; j < this->hiddenLayer.getColumns(); j++) {

				float rand = getRandomFloat();
				row[j] = rand;
			}
			this->inputToHiddenLinks[i] = row;
		}



		//cout << "rows: " << this->inputToHiddenLinks.getRows() << ", columns: " << this->inputToHiddenLinks.getColumns() << '\n';
		for (int i = 0; i < this->hiddenNodes ; i++) 
		{
			vector<float> row(this->outputNodes);
			for (int k = 0; k < this->outputNodes ; k++) 
			{
				float rand = getRandomFloat();
				row[k] = rand;
			}
			this->hiddenToOutputLinks[i] = row;

		}
		//cout << "rows: " << this->hiddenToOutputLinks.getRows() << ", columns: " << this->hiddenToOutputLinks.getColumns() << '\n';

	}	
	//returns a float between .01 and .99 for the weight matrix
	static float getRandomFloat() 
	{
		int randInt = (std::rand() % 99);
		int negative = (std::rand() % 2);
		float rand = (float) ((randInt / 100.0F) + 0.01F) * (pow(-1.0, (double) negative));
		return rand;
	}

	//normalize the value to between 0.01 - 0.99
	static float normalizeValue(int value)
	{
		return (float) (((value / 255.0F) * .99F) + .01F) ;
	}	

	void printNeuralNetwork() 
	{
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

	

};



const char* help_string = "-lr :\t specifies a learning rate in place of the default (0.25)\n-t :\tspecifies a file path for training data in place of default\n-q :\tspecifies a file path for the data in which to query the Neural Network with\n-? :\tdisplay this text";
float learningRate = 0.1f;
int main(int argc, char** args) 
{
	char* trainingDataFilePath = (char*) malloc(257);
	char* dataFilePath = (char*) malloc(257);

	strcpy (trainingDataFilePath, DEFAULT_TRAINING_DATA_PATH);
	strcpy (dataFilePath, DEFAULT_DATA_PATH);
	for (int i = 0; i < argc; i++) 
	{
		char* arg = args[i];
		if (arg[0] == '-') 
		{
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
	net.query();
}

