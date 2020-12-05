#include <iostream>
#include <vector>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

void read_data(vector <double>& x, vector <double>& y) {
	ifstream fin;
	fin.open("data.txt");
	if (!fin.is_open()) {
		cout << "Error reading the file" << endl;
		system("pause");
	}
	double tmp;
	while (!fin.eof()) {
		fin >> tmp;
		x.push_back(tmp);
		fin >> tmp;
		y.push_back(tmp);
	}
	fin.close();
}
void Newton(vector <double> x, vector <double> y) {
	vector <vector<double>>  dy;
	double q, h,x0,mult,sum;
	int n, fact_;

	h = (x[1] - x[0]);
	for (unsigned i = 0; i < x.size(); ++i) {
		cout << "x[" << i << "] " << x[i] << " " << "y[" << i << "]" << " " << y[i] << endl;
	}
	n = x.size()-1;
	//выделяем память под вектор
	dy.resize(n);
	for (int i = 0; i < n; ++i) {
		dy[i].resize(n);
		for (int j = 0; j < n ; ++j) {
			dy[i][j] = 0;
		}
	}

	// считаем конечные разности 1-ый столбец
	for (int i = 0; i < n; ++i) {
		dy[i][0] = y[i+1] - y[i];
	}

	// считаем оставшиеся конечные разности
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < n - i; ++j) {
			dy[j][i] = dy[j + 1][i - 1] - dy[j][i - 1];
		}
	}
	cout << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; j++) {
			printf("%.9f ", dy[i][j]);
		}
		cout << endl;
	}
	// точка в которой считаем интерполяционный многочлен
	x0 = M_PI/9;
	mult = 1; 
	sum = y[0];
	q = (x0 - x[0]) / h;
	fact_ = 1;
	for (int i = 0; i < n; ++i) {
		mult *= (q-i);
		fact_ *= i+1;
		sum += mult * dy[0][i] / (fact_);
	}
	printf("FirstNewton= %.9f \n", sum) ;

	// Вторая формула
	q = (x0 - x[n]) / h;
	sum = y[n];
	mult = 1;
	fact_ = 1;
	for (int i = 0; i < n; ++i) {
		mult *= (q + i);
		fact_ *= i + 1;
		sum += mult * dy[n - i - 1][i] / (fact_);
	}
	printf("SecondNewton= %.9f \n", sum);
}
int main()
{
	vector <double> x, y;
	read_data(x, y);
	Newton(x, y);
}
