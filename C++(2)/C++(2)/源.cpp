#include<iostream>
#include"Rectangle.h"
using namespace std;
int main() {
	rectangle obj1;
	cout << "此矩形的面积为:" << obj1.area() << endl;
	cout << "此矩形的周长为:" << obj1.perimeter() << endl;
	system("pause");
}