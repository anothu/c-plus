#pragma once
#include<iostream>
using namespace std;

class Geometric_shape {
public:
	virtual double area() {
		return 0;
	}
	virtual double perimeter() {
		return 0;
	}
	virtual double volume() {
		return 0;
	}
	virtual void Show() {}
};

class Circle : public Geometric_shape {
public:
	Circle() {}
	Circle(double r) {
		this->r = r;
	}
	double area() {
		s = 3.14*r*r;
		return s;
	}
	double perimeter() {
		l = 3.14 * 2 * r;
		return l;
	}
	void Show() {
		cout << "圆的面积为：" << area() << endl;
		cout << "圆的周长为：" << perimeter() << endl;
	}
private:
	double r;
	double s;
	double l;
};

class Rectangle : public Geometric_shape {
public:
	Rectangle() {}
	Rectangle(double length, double width) {
		this->length = length;
		this->width = width;
	}
	double area() {
		s = length * width;
		return s;
	}
	double perimeter() {
		l = 2 * (length + width);
		return l;
	}
	void Show() {
		cout << "矩形的面积为：" << area() << endl;
		cout << "矩形的周长为：" << perimeter() << endl;
	}
private:
	double length;
	double width;
	double s;
	double l;
};

class Triangle :public Geometric_shape {
public:
	Triangle() {}
	Triangle(double a, double b, double c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
	double area() {
		double p = 0.5*(a + b + c);
		s = pow(p*(p - a)*(p - b)*(p - c), 0.5);
		return s;
	}
	double perimeter() {
		l = a + b + c;
		return l;
	}
	void Show() {
		cout << "三角形的面积为：" << area() << endl;
		cout << "三角形的周长为：" << perimeter() << endl;
	}
private:
	double a;
	double b;
	double c;
	double s;
	double l;
};

class Box :public Rectangle {
private:
	//double length;
	//double width;
	double height;
	//double s;
	//double l;
	double v;

public:
	Box() {}
	Box(double length, double width, double height) :Rectangle(length, width) {
		this->height = height;
	}
	double volume() {
		v = area()*height;
		return v;
	}
	void Show() {
		cout << "长方体底面图形的面积为：" << area() << endl;
		cout << "长方体底面图形的周长为：" << perimeter() << endl;
		cout << "长方体的体积为：" << volume() << endl;
	}
};

class Cylinder :public Circle {
private:
	double height;
	double v;

public:
	Cylinder() {}
	Cylinder(double r, double height) :Circle(r) {
		this->height = height;
	}
	double volume() {
		v = area()*height;
		return v;
	}
	void Show() {
		cout << "圆柱体底面图形的面积为：" << area() << endl;
		cout << "圆柱体底面图形的周长为：" << perimeter() << endl;
		cout << "圆柱体的体积为：" << volume() << endl;
	}
};

class Cone :public Circle {
private:
	double height;
	double v;
public:
	Cone() {}
	Cone(double r, double height) :Circle(r) {
		this->height = height;
	}
	double volume() {
		v = area()*height / 3;
		return v;
	}
	void Show() {
		cout << "圆锥体底面图形的面积为：" << area() << endl;
		cout << "圆锥体底面图形的周长为：" << perimeter() << endl;
		cout << "圆锥体的体积为：" << volume() << endl;
	}
};

class T_pyramid :public Triangle {
private:
	double height;
	double v;
public:
	T_pyramid() {}
	T_pyramid(double a, double b, double c, double height) :Triangle(a, b, c) {
		this->height = height;
	}
	double volume() {
		v = area()*height / 3;
		return v;
	}
	void Show() {
		cout << "三棱锥体底面图形的面积为：" << area() << endl;
		cout << "三棱锥体底面图形的周长为：" << perimeter() << endl;
		cout << "三棱锥体的体积为：" << volume() << endl;
	}
};

class T_prism :public Triangle {
private:
	double height;
	double v;

public:
	T_prism() {}
	T_prism(double a, double b, double c, double height) :Triangle(a, b, c) {
		this->height = height;
	}
	double volume() {
		v = area()*height;
		return v;
	}
	void Show() {
		cout << "三棱柱体底面图形的面积为：" << area() << endl;
		cout << "三棱柱体底面图形的周长为：" << perimeter() << endl;
		cout << "三棱柱体的体积为：" << volume() << endl;
	}
};