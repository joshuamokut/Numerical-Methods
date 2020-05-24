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

vector<long double> calculate(const vector<long double>& X, long double eps);

void printOut(vector<long double> C, vector<long double> X);

signed main() {

	long double a = 0.4;

	long double b = 4;

	long double h = 0.2;

	long double eps = 1e-6;


	vector<long double > X = initializeVectorX(a, b, h);
	vector<long double > C = calculate(X, eps);


	printOut(C, X);

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
void printOut(vector<long double> C, vector<long double> X) {
	for (int i = 0; i < C.size(); i++) {
		cout << X[i];
		cout.width(15);
		cout << C[i];
		cout << '\n';
	}
}

long double phi(long double t){
    return exp(-pow(t, 2));
}

long double S(long double hN, long double z1, long double z2){
    long double result=(hN/(long double)6.0);
    result *= (phi(z1)+4.0 * phi((z1+z2)/2.0)+phi(z2));

    return result;
}

long double sumS(int N, long double c, long double d){
    long double hN=(d-c)/(long double)N;

    long double result=0.0;

    for(int i=1; i<=N; i++){
        result+=S(hN, c+(long double)(i-1)* hN, c+(long double)(i)*hN);
    }

    return result;
}

bool accurate(long double x, int N, long double eps){
    return abs(sumS(N, 0, x)- sumS(2*N, 0, x))<=eps;
}

long double getSumS(long double x, long double eps){
    int N=1;

    while(!accurate(x, N, eps))
        N+=5;

    return sumS(N, 0, x);
}

vector<long double> calculate(const vector<long double>& X, long double eps) {

    vector<long double> C;

    for(long double x : X){
        long double result=(long double)2.0/(long double)sqrt(pi);

        result = result * getSumS(x, eps);

        C.push_back(result);
    }

    return C;
}

    
    
