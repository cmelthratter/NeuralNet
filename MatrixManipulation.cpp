#include "MatrixManipulation.hpp"
#include <vector>
#include <iostream>
using namespace MatrixUtil;
using namespace std;
using std::ostream;
template <typename T>
Matrix<T>::Matrix(int rows, int columns) : values(rows, vector<T>(columns)), mRows(rows), mColumns(columns) 
{

}

template<typename T>
Matrix<T>::Matrix() : values(1, vector<T>(1)), mRows(1), mColumns(1) 
{

}

template <typename T>
Matrix<T>::Matrix(vector<vector<T> >& nValues) : values(nValues), mRows(nValues.size()), mColumns(nValues[0].size())
{
	
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>& matrix) : values(matrix.getData()) , mRows(matrix.getRows()), mColumns(matrix.getColumns())
{

}

template <typename T>
Matrix<T>  Matrix<T>::operator*(Matrix<T>& operand) 
{
	if(this->getColumns() != operand.getRows())  {
		cout << "ERROR: MATRICES ARE INCOMPATIBLE (A Columns =  " << this->getColumns() << ", B Rows: " << operand.getRows() << ")\n";
		Matrix<T> newMatrix(0, 0);
		return newMatrix;
	}
	vector<vector<T> > newData (this->getRows(), vector<T>(operand.getColumns()));
	for (int i = 0; i < this->getRows(); i++) {

		for (int j = 0; j < operand.getColumns(); j++) {
			T sum{};
			for (int k = 0; k < operand.getColumns(); k++) {
				sum += this->values[i][k] * operand[k][j];
			}

			newData[i][j] = sum;
		}
		
	}
	Matrix<T> newMatrix(newData);
	return newMatrix;
}
//add a row to the
template <typename T>
void Matrix<T>::addRow(vector<T> row) {
	this->values.push_back(row);
}
//add a value to the end of the two matrix
template <typename T>
void Matrix<T>::add(T value) {
	this->values.back().push_back(value);
}

template <typename T>
vector<T>& Matrix<T>::operator[](int i){
	return Matrix<T>::values[i];
}

template <typename T>
ostream& operator<<(ostream& os, Matrix<T>& operand) {
	os << "[";
	for (int i = 0; i < operand.getRows(); i++) {
		os << "[";
		for (int j = 0; j < operand.getColumns(); j++) {
			os << operand[i][j] << " ";
		}
		if (i != operand.getRows() - 1) os << "]\n";
		else os <<"]";
	}

	os << "]\n";

	return os;
}

template <typename T>
vector<vector<T> >& Matrix<T>::getData(){
	return this->values;
}

template <typename T>
int Matrix<T>::getRows() const {
	return (int) this->mRows;
}

template <typename T>
int Matrix<T>::getColumns() const {
	return (int) this->mColumns;
}


template <typename T>
Matrix<T>& MatrixManipulation<T>::transpose() {
	vector<vector<T> > matrix;
	for (int i = 0; i < this.getRows(); i++) {
		for (int j = 0; j < this.getColumns(); j++) {
			matrix[j][i] = this[i][j];
		}
	}

	return new Matrix<T>(matrix);
}
