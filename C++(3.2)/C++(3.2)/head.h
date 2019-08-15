#pragma once
#pragma once
#include<iostream>
using namespace std;

class Complex
{
public:
	Complex(double r = 0, double i = 0);
	Complex operator+(Complex c2) {
		return Complex(real + c2.real, imag + c2.imag);
	}
	Complex operator-(Complex c2) {
		return Complex(real - c2.real, imag - c2.imag);
	}
	void display() {
		cout << real;
		if (imag > 0) cout << "+";
		cout << imag << "i" << endl;
	}
private:
	double real;
	double imag;
};

Complex::Complex(double r, double i)
{
	real = r; imag = i;
}