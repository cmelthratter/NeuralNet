
#include "MatrixManipulation.cpp"
#include "MatrixManipulation.hpp"
#include <iostream>
#include <vector>

using namespace MatrixUtil;
using namespace std;

int main() {

	vector<vector<int> > data {{1, 2, 3},
							   {4, 5, 6},
							   {7, 8, 9}};
	Matrix<int> matrix(data);

	Matrix<int> newMatrix = (matrix * matrix);

	cout << newMatrix << "\n";

}