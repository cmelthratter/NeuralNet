
#include <vector>
#include <iostream>

namespace MatrixUtil {

	using namespace std;


	template <typename T> 
	class Matrix {

	public:
		Matrix(const vector<vector<T> > values);

		Matrix();

		int getColumns();

		int getRows();

		vector<vector<T> >& getData();



	private:

		vector<vector<T> > values;


	};

	template <typename T> class MatrixManipulation {
	public:

		Matrix<T>& transpose();

		std::ostream& operator<<(const Matrix<T>& operand);

		Matrix<T>& operator*(const Matrix<T>& operand);

		vector<T>& operator[](const int i);

	private:

	};


}