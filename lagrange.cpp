#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "set"
#include <map>
#include <unordered_map>
#include "queue"
#include "iomanip"
using namespace std;

const long double pi = acos(-1);

vector<long double> initializeVectorX(long double a, long double b, long double h);


vector<long double> calculate(vector<long double> X, long double eps);

long double getC(long double X, long double a_prev, long double eps);

long double FQ(int i, long double x);

long double longPower(long double a, int i);

vector<long double> getA0(vector<long double> X);

void printOut(vector<long double> C, vector<long double> X);

vector<long double> Lagrange(vector<long double>& X, vector<long double>& F, vector<long double>& X1);

long double getLagrangeValue(vector<long double>& X, vector<long double>& F, long double x1);

long double& product(vector<long double>& X, int i, long double x);

signed main() {

	long double a = 0;

	long double b = 2;

	long double h = 0.4;

	long double h1 = 0.2;

	long double eps = 1e-6;


	vector<long double > X = initializeVectorX(a, b, h);
	vector<long double > C = calculate(X, eps);

	vector<long double> X1 = initializeVectorX(a, b, h1);
	vector<long double > L = Lagrange(X, C, X1);



	printOut(C, X);
	cout << "\n\n";

	printOut(L, X1);
}

vector<long double> Lagrange(vector<long double>& X, vector<long double>& F, vector<long double>& X1) {
	int n = X.size();


	vector<long double> lagrange;

	for (auto x1 : X1) {
		lagrange.push_back(getLagrangeValue(X, F, x1));
	}

	return lagrange;
}

long double getLagrangeValue(vector<long double>& X, vector<long double>& F, long double x1) {
	long double returnValue = 0;

	for (int i = 0; i < F.size(); i++) {
		returnValue += F[i] * product(X, i, x1);
	}
	return returnValue;
}

long double& product(vector<long double>& X, int i, long double x) {
	long double products = 1.0;

	for (int j = 0; j < X.size(); j++) {
		if (j == i)
			continue;
		products = products * ((x - X[j]) / (X[i] - X[j]));
	}

	return products;
}

void printOut(vector<long double> C, vector<long double> X) {
	for (int i = 0; i < C.size(); i++) {

		cout << fixed << setprecision(10) << X[i];
		cout.width(15);
		cout << C[i];
		cout << '\n';
	}
}

vector<long double> calculate(vector<long double> X, long double eps) {
	vector<long double> A0 = getA0(X);

	vector<long double> C;

	for (int i = 0; i < X.size(); i++) {
		C.push_back(getC(X[i], A0[i], eps));
	}

	return C;

}

vector<long double> getA0(vector<long double> X) {
	return X;
}

long double getC(long double X, long double a_prev, long double eps) {

	long double Cx = 0;

	int i = 0;

	while (abs(a_prev) > eps) {
		Cx += a_prev;

		a_prev = a_prev * FQ(i++, X);

	}

	Cx *= 2.0;

	Cx /= (long double)sqrt(pi);
	return Cx;

}

vector<long double> initializeVectorX(long double a, long double b, long double h) {
	vector<long double> X;

	long double curVal = a;

	while (curVal <= b) {
		X.push_back(curVal);

		curVal += h;
	}

	return X;
}

long double FQ(int i, long double x) {
	long double FQix = longPower(x, 2) * (long double)(2 * i + 1);

	FQix /= (long double)(i + 1) * (long double)(2 * i + 3);

	return -FQix;

}

long double longPower(long double a, int i) {
	long double ret = 1.0;

	while (i--) {
		ret *= a;
	}

	return ret;
}
