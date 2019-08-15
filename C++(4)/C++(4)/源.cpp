#include"myPoint.h"
int main() {
	Trangle obj1;
	double x[5], y[5];
	int i;
	for (i = 1; i <= 3; i++)
	{
		cout << "输入第" << i << "个点的横坐标:";
		cin >> x[i];
		cout << "输入第" << i << "个点的纵坐标:";
		cin >> y[i];
	}
	obj1.getAll(x[1], x[2], x[3], y[1], y[2], y[3]);
	if (obj1.isfeasible(x[1], x[2], x[3], y[1], y[2], y[3]) == 1)
	{
		obj1.area();
		obj1.perimeter();
	}
	else
		cout << "无法构成三角形!" << endl;
	system("pause");
}