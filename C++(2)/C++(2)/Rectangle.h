#pragma once
#include<iostream>
using namespace std;
class rectangle
{
private:
	int length;
	int wide;
public:
	rectangle()
	{
		length = 20;
		wide = 50;
	}
	int area()
	{
		return length*wide;
	};
	int perimeter()
	{
		return 2 * (length + wide);
	};
};