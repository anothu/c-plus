#pragma once
#include<iostream>
#include<math.h>
using namespace std;
class myPoint {
public:
	myPoint(double x0 = 0.0, double y0 = 0.0) :x(x0), y(y0) {}
	myPoint(myPoint &np) :x(np.x), y(np.y) {}
	double GetX() { return x; }
	double GetY() { return y; }
	void SetX(double x0) { x = x0; }
	void SetY(double y0) { x = y0; }
	void SetPoint(double x0, double y0) { x = x0; y = y0; }
	void SetPoint(myPoint &np) { x = np.x; y = np.y; }
	double  GetLength(myPoint p) {
		return sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y));
	}
	void Printit() { cout << " (" << x << "," << y << ") "; }
private:
	double x, y;
};

class Trangle {
public:
	void area();
	void perimeter();
	void getAll(double x1, double x2, double x3, double y1, double y2, double y3);
	int isfeasible(double x1, double x2, double x3, double y1, double y2, double y3);
private:
	myPoint p1, p2, p3;;
	double sin1, cos1, L1, L2, L3, x1, x2, x3, y1, y2, y3;
};