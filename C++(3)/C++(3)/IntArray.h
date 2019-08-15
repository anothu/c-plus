#pragma once
#include<iostream>  
using namespace std;
class IntArray {
public:
	IntArray(int sz);      // 数组初始化为sz个元素，初值全为0
	IntArray(int *array, int sz);  // 用静态数组array的前sz个元素初始化新数组
	IntArray(const IntArray &rhs); // 拷贝构造函数
	void printAll();
	void common();//共享函数
	~IntArray();//析构函数
private:
	int *ia;
	int size;
};