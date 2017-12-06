#include "MatrixManipulation.hpp"
#include <iostream>
#include <vector>

using namespace MatrixUtil;

int main() {

	std::vector<std::vector<int> > data {{1, 2, 3},
								 		 {4, 5, 6},
								 		 {7, 8, 9}};
	Matrix<int> matrix(data);

	cout << &matrix;

}