#include <iostream>
#include <Eigen/Dense>
#include <time.h>

using namespace Eigen;
using namespace std;

const int SIZE = 100;

int main()
{
	clock_t begin, end;

	MatrixXf A, b, x1, x2;

	A = MatrixXf::Random(SIZE, SIZE);
	b = MatrixXf::Random(SIZE, 1);

	cout << "A :" << endl;
	cout << A << endl;
	cout << "b :" << endl;
	cout << b << endl;

	cout << "\nuse inverse matrix:" << endl;
	begin = clock();
	x1 = A.inverse() * b;
	end = clock();
	//cout << "result\n" << x1 << endl;
	cout << "cost time : " << end - begin << " ms" << endl;

	cout << "\nQR decomposition:" << endl;
	begin = clock();
	x2 = A.colPivHouseholderQr().solve(b);
	end = clock();
	//cout << "result\n" << x2 << endl;
	cout << "cost time : " << end - begin << " ms" << endl;

	return 0;
}