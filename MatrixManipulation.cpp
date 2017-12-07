#include "MatrixManipulation.hpp"
#include <vector>
#include <iostream>
using namespace MatrixUtil;
using namespace std;
using std::ostream;
template <typename T>
Matrix<T>::Matrix() : values() {
}


template <typename T>
Matrix<T>::Matrix(vector<vector<T> >& mValues) : values(mValues) {
	
}
template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& operand) 
{
	vector<vector<T> > newData (this->getRows());
	cout << "hello " << operand << "\n";
	for (int i = 0; i < this->getRows(); i++) {

		cout<<"first loop " << this->getRows() <<"\n";
		for (int j = 0; j < this->getRows(); j++) {
			T sum{};
			cout<<"second loop\n";
			for (int k = 0; k < operand.getColumns(); k++) {
				cout<<"third loop " << operand.getColumns() << "\n";
				sum += this->values[i][k] * operand[k][j];
				cout << sum << "\n";
			}

			newData[i].push_back(sum);
			cout<<"done with second\n";
		}
		
	}

	
	cout <<"balls\n";
	return Matrix<T>(newData);
}

template <typename T>
void MatrixManipulation<T>::addRow(vector<T> row) {
	this->values.push_back(row);
}

template <typename T>
void MatrixManipulation<T>::add(T value) {
	this->values.back.push_back(value);
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
	return (int) this->values.size();
}

template <typename T>
int Matrix<T>::getColumns() const {
	return (int) this->values[0].size();
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
