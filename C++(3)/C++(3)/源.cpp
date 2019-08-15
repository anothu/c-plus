#include"IntArray.h"
int main()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	IntArray arr1(10), arr2(a, 5), arr3(arr2);
	arr1.printAll();
	//arr2.~IntArray();
	arr2.printAll();
	arr3.printAll();
	system("pause");
	return 0;
}