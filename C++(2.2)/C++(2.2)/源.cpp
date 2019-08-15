#include <iostream>
#include<math.h>
using namespace std;

class Point {
public:
	Point() { /*x = 0; y = 0; */ }
	Point(double xv, double yv) { x = xv; y = yv; }
	Point(Point& pt) { x = pt.x;  y = pt.y; }
	double getx() { return x; }
	double gety() { return y; }
	double Area() { return 0; }
	void Show() { cout << "x=" << x << ' ' << "y=" << y << endl; }
private:
	double x, y;
};

class Rectangle :public Point {
private:
	double length, width;
public:
	Rectangle(double xv, double yv) :Point(xv, yv) {
		cout << "长、宽分别为：";
		cin >> length >> width;
	}
	double Area() { return length * width; }
	double Perimeter() { return (length + width) * 2; }
	void position(Point &pt) {
		double px = pt.getx();
		double py = pt.gety();
		double x = getx();
		double y = gety();
		if (px > length + x || py < y - width || px < x || py > y) {
			cout << "out the Rectangle" << endl;
		}
		else if (px < length + x || py > y - width || px > x || py < y) {
			cout << "in the Rectangle" << endl;
		}
		else {
			cout << "on the Rectangle" << endl;
		}
	}
};

class Circle :Point {
private:
	double r;
public:
	Circle(double xv, double yv) :Point(xv, yv) {
		cout << "半径为：";
		cin >> r;
	}
	double Area() { return 3.14*r*r; }
	double Perimeter() { return 3.14*r * 2; }
	void position(Point &pt) {
		double px = pt.getx();
		double py = pt.gety();
		if (pow(px - getx(), 2) + pow(py - gety(), 2) > r*r) {
			cout << "on the Circle" << endl;
		}
		else if (pow(px - getx(), 2) + pow(py - gety(), 2) == r * r) {
			cout << "out the Circle" << endl;
		}
		else {
			cout << "in the Circle" << endl;
		}
	}
};

int main() {
	cout << "左上角的顶点坐标为：";
	double xv1, yv1;
	cin >> xv1 >> yv1;
	Rectangle rec(xv1, yv1);

	cout << "圆心的坐标为：";
	double xv2, yv2;
	cin >> xv2 >> yv2;
	Circle cil(xv2, yv2);

	double x, y;
	cout << "给出坐标为：";
	cin >> x >> y;

	Point pt(x, y);
	rec.position(pt);
	cil.position(pt);
	system("pause");
}
