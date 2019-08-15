#include"MyClass.h"
#include<stdlib.h>
int main()
{
	MyClass obj1, obj2(5, 8);
	obj1.Print();
	obj2.Print();
	system("pause");
	return 0;
}
