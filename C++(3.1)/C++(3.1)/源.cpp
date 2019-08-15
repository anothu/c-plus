#include"head.h"

int main()
{
	Geometric_shape * gs[] = { new	Circle(10),new 	Rectangle(6,8),new	Triangle(3,4,5),
		new Box(6,8,3),new	Cylinder(10,3),new 	Cone(10,3),new T_pyramid(3,4,5,3),new T_prism(3,4,5,3) };
	for (int i = 0; i < 8; i++)
	{
		gs[i]->Show();
		cout << endl;
	}
	for (int i = 0; i < 8; i++)
	{
		gs[i]->Show();
		cout << endl;
	}
	cout << "平面图形：" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "图形周长：" << gs[i]->perimeter() << '\t';
		cout << "图形面积：" << gs[i]->area() << '\t';
		cout << "图形体积：" << gs[i]->volume() << endl;
	}
	cout << "立体图形：" << endl;
	for (int i = 3; i < 8; i++)
	{
		cout << "图形底周长：" << gs[i]->perimeter() << '\t';
		cout << "图形底面积：" << gs[i]->area() << '\t';
		cout << "图形体积  ：" << gs[i]->volume() << endl;
	}
	system("pause");
	return 0;
}
