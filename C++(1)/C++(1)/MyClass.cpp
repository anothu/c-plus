#include <iostream> 
#include"MyClass.h"
using namespace std;
MyClass::MyClass(int a, int b)
{
	x = a;
	y = b;
}

void MyClass::Print()
{
	cout << "x=" << x<< endl;
	cout << "y=" << y<<endl;
}

