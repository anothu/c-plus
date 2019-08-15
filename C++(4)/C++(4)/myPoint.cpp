#include"myPoint.h"
int Trangle::isfeasible(double x1, double x2, double x3, double y1, double y2, double y3)
{
	if (((x3 - x2) / (y3 - y2)) == ((x2 - x1) / (y2 - y1)))
		return 0;
	else
		return 1;
}
void Trangle::getAll(double x1, double x2, double x3, double y1, double y2, double y3)
{
	p1.SetX(x1);
	p2.SetX(x2);
	p3.SetX(x3);
	p1.SetY(y1);
	p2.SetY(y2);
	p3.SetY(y3);
	L1 = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	L2 = sqrt((x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3));
	L3 = sqrt((x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1));
	cos1 = (L2*L2 + L3*L3 - L1*L1) / (2 * L2*L3);
	sin1 = sqrt(1 - cos1*cos1);
}
void Trangle::area()
{
	double S;
	S = L2*L3*sin1 / 2;
	cout << "面积为:" << S << endl;;
}
void Trangle::perimeter()
{
	double L;
	L = L1 + L2 + L3;
	cout << "三角形周长为:" << L << endl;
}