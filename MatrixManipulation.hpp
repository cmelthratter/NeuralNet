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

		Matrix(int rows, int columns);
		Matrix();
		Matrix(Matrix<T>& matrix);
		int getColumns() const;

		int getRows() const;

		vector<vector<T> >& getData();

		vector<T>& operator[](int i);

		Matrix<T> operator*(Matrix<T>& operand);

		void add(T value);


		void addRow(const vector<T> row);
		Matrix<T> transpose();


		


	private:

		vector<vector<T> > values;
		int mRows;
		int mColumns;

	};

	template <typename T> class MatrixManipulation {
	public:

		
		friend ostream& operator<< <>(ostream& os, Matrix<T>& operand);

	private:

	};


}

#endif