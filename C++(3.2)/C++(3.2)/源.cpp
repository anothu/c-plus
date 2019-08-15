#include"head.h"

int main() {
	Complex c1(6, 7), c2(7, 8), c3;
	c3 = c1 + c2;
	c3.display();
	c3 = c1 - c2;
	c3.display();
	system("pause");
}