
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>

using namespace std;
using namespace Eigen;

int main(int argc, char** argv)
{
	size_t rows = 100;
	size_t cols = 100;
	if(argc == 3) {
		rows = atoi(argv[1]);
		cols = atoi(argv[2]);
	} else {
		cerr << "Provide 2 arguments if you want to set rows and columns" << endl;
	}

	Eigen::MatrixXd mat(rows, cols);
	mat.setRandom();

	HouseholderQR<MatrixXd> qr(mat);

	MatrixXd tmp = qr.householderQ()*MatrixXd::Identity(rows, std::min(rows, cols));
}
