#pragma once
#include<iostream>
using namespace std;
const int MaxSize = 100; 
template<typename T>
class  Istack
{
public:
	Istack();          
	void Push(T& n);    
	void Pop();         
	T GetTop();       
	bool Empty();      
	int Size();         
	void ClearStack(); 
	~Istack();

private:
	T elem[MaxSize];  
	int Top;          
};
void menu();

void menu()
{
	cout << "1.让元素入栈" << endl;
	cout << "2.让元素出栈" << endl;
	cout << "3.返回非空栈的栈顶元素" << endl;
	cout << "4.判断栈是否为空" << endl;
	cout << "5.返回栈中元素的个数" << endl;
	cout << "6.将栈清空" << endl;
}

template<typename T>
Istack<T>::Istack()
{
	int *elem = new int[MaxSize];
	Top = 0;
}

template<typename T>
Istack<T>::~Istack()
{
	delete[] elem;
	Top = 0;
}

template<typename T>
void Istack<T>::Push(T& n)
{
	elem[Top++] = n;
}

template<typename T>
void Istack<T>::Pop()
{
	if (Top == 0)
		cout << "栈为空!" << endl;
	else
	{
		cout << "出栈的元素值: " << elem[Top - 1] << endl;
		Top--;
	}

}

template<typename T>
T Istack<T>::GetTop()
{
	if (Top == 0)
		cout << "栈为空!" << endl;
	else
		return elem[Top - 1];
}

template<typename T>
bool Istack<T>::Empty()
{
	if (Top == 0)
		return true;
	else
		return false;
}

template<typename T>
int Istack<T>::Size()
{
	return Top;
}

template<typename T>
void Istack<T>::ClearStack()
{
	Top = 0;
}