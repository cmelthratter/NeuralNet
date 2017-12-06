#include "MatrixManipulation.hpp"
#include <vector>
#include <iostream>
using namespace MatrixUtil;

template <typename T>
Matrix<T>::Matrix() : values() {
}


template <typename T>
Matrix<T>::Matrix(const vector<vector<T> > values) : values(values) {
	
}
template <typename T>
Matrix<T>& MatrixManipulation<T>::operator*(const Matrix<T>& operand) 
{
	vector<vector<T> > newData;

	bool done = false;
	for (int i = 0; i < this.getRows; i++) {
		
		for (int j = 0; j < this.getRows; j++) {
			T sum;
			for (int k = 0; k < operand.getColumns; k++)
				sum += this.mValues[j][k] * operand[k][j];

			newData[i][j] = sum;
			sum = 0;
		
		}
		
	}

	return new Matrix<T>(newData);
}

template <typename T>
vector<T>& MatrixManipulation<T>::operator[](const int i) {
	return Matrix<T>::mValues[i];
}

template <typename T>
ostream& MatrixManipulation<T>::operator<<(const Matrix<T>& operand) {
	cout << "[";
	for (int i = 0; i < *operand.getRows; i++) {
		cout << "[";
		for (int j = 0; j < *operand.getColumns; j++) {
			cout << *operand[i][j];
		}
		cout << "]";
	}

	cout << "]";

	return cout;
}

template <typename T>
vector<vector<T> >& Matrix<T>::getData() {
	return Matrix<T>::mValues;
}

template <typename T>
int Matrix<T>::getRows() {
	return Matrix<T>::mValues.size;
}

template <typename T>
int Matrix<T>::getColumns() {
	return Matrix<T>::mValues[0].size;
}


template <typename T>
Matrix<T>& MatrixManipulation<T>::transpose() {
	vector<vector<T> > matrix;
	for (int i = 0; i < this.mValues.size; i++) {
		for (int j = 0; j < this.mValues[0].size; j++) {
			matrix[j][i] = this.mValues[i][j];
		}
	}

	return new Matrix<T>(matrix);
}
