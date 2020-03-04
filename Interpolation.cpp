#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "set"
#include <map>
#include <unordered_map>
#include "queue"
using namespace std;

const long double pi = acos(-1);

vector<long double> initializeVectorX(long double a, long double b, long double h);


vector<long double> calculate(vector<long double> X, long double eps);

long double getC(long double X, long double a_prev, long double eps);

long double FQ(int i, long double x);

long double longPower(long double a, int i);

vector<long double> getA0(vector<long double> X);

void printOut(vector<long double> C, vector<long double> X);

signed main() {

	long double a = 0;

	long double b = 1.5;

	long double h = 0.15;

	long double eps = 1e-6;


	vector<long double > X = initializeVectorX(a, b, h);
	vector<long double > C = calculate(X, eps);


	printOut(C, X);

}

void printOut(vector<long double> C, vector<long double> X) {
	for (int i = 0; i < C.size(); i++) {
		cout << X[i];
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
	long double FQix = longPower(pi, 2) * (long double)(4 * i + 1) * longPower(x, 4);

	FQix /= (4.0 * (long double)(2 * i + 1) * (long double)(2 * i + 2) * (long double)(4 * i + 5));

	return -FQix;

}

long double longPower(long double a, int i) {
	long double ret = 1.0;

	while (i--) {
		ret *= a;
	}

	return ret;
}
