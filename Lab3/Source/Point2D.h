#pragma once
#include "stdafx.h"
using namespace std;

class Point2D {
public:
	int x;
	int y;
public:
	Point2D() {
		x = y = 0;
	}
	Point2D(int X, int Y) {
		x = X;
		y = Y;
	}
	Point2D(const Point2D &p) {
		x = p.x;
		y = p.y;
	}
	~Point2D() {}
	Point2D& operator = (const Point2D &p) {
		if (this != &p) {
			x = p.x;
			y = p.y;
		}
		return *this;
	}
	void drawPoint2D() {
		glVertex2i(x, y);
	}
	double* getVector() {
		double* res = new double[3];
		res[0] = (double)x;
		res[1] = (double)y;
		res[2] = 1;
		return res;
	}
	double getDistance(int X, int Y) {
		double a = x - X;
		double b = y - Y;
		a *= a;
		b *= b;
		return sqrt(a + b);
	}
	double getDistance(Point2D p) {
		return this->getDistance(p.x, p.y);
	}
	int X() {
		return x;
	}
	int Y() {
		return y;
	}
};