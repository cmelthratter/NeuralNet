#ifndef MATRIXMANIPULATION_H
#define MATRIXMANIPULATION_H
#include <vector>
#include <iostream>

namespace MatrixUtil {

	using namespace std;
	using std::ostream;


	template <typename T> 
	class Matrix {

	public:
		Matrix(vector<vector<T> >& mValues);

		Matrix();

		int getColumns() const;

		int getRows() const;

		vector<vector<T> >& getData();

		vector<T>& operator[](int i);

		Matrix<T> operator*(Matrix<T>& operand);

		void add(T value);

		void addRow(const vector<T> row);


		


	private:

		vector<vector<T> > values;

	};

	template <typename T> class MatrixManipulation {
	public:

		Matrix<T>& transpose();

		friend ostream& operator<< <>(ostream& os, Matrix<T>& operand);

	private:

	};


}

#endif