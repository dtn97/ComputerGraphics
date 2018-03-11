#pragma once
#include "stdafx.h"
#include <vector>
#define PI 3.1415926535898
struct Point {
	double x, y, z;
	Point() {}
	Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	double* getVector() {
		double *res = new double[4];
		res[0] = x;
		res[1] = y;
		res[2] = z;
		res[3] = 1;
		return res;
	}
};

void drawPoint(Point p) {
	glVertex3d(p.x, p.y, p.z);
}

Point calNormal(Point x1, Point x2, Point x3) {
	Point n;
	n.x = n.y = n.z = 0;
	double a1 = x2.x - x1.x, b1 = x2.y - x1.y, c1 = x2.z - x1.z;
	double a2 = x3.x - x1.x, b2 = x3.y - x1.y, c2 = x3.z - x1.z;
	n.x = b1 * c2 - b2 * c1;
	n.y = c1 * a2 - c2 * a1;
	n.z = a1 * b2 - a2 * b1;
	double len = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	n.x /= len; n.y /= len; n.z /= len;
	return n;
}

double Cos(double d) {
	return cos(PI / 180 * d);
}

double Sin(double d) {
	return sin(PI / 180 * d);
}

Point vertex(double th2, double ph2)
{
	double x = Sin(th2)*Cos(ph2);
	double y = Cos(th2)*Cos(ph2);
	double z = Sin(ph2);
	return Point(x, y, z);
}

class MaTrix {
private:
	double arr[4][4];
	void MultiplyMatrix(double**);
	void deleteArr(double**&);
public:
	MaTrix();
	MaTrix(double*);
	MaTrix(double x1, double x2, double x3, double x4, double x5, double x6, double x7, double x8, double x9, double x10, double x11, double x12) {
		arr[0][0] = x1;
		arr[0][1] = x2;
		arr[0][2] = x3;
		arr[1][0] = x4;
		arr[1][1] = x5;
		arr[1][2] = x6;
		arr[2][0] = x7;
		arr[2][1] = x8;
		arr[2][2] = x9;
		arr[3][0] = x10;
		arr[3][1] = x11;
		arr[3][2] = x12;
		for (int i = 0; i < 4; ++i) arr[i][3] = 0;
		arr[3][3] = 1;
	}
	~MaTrix();
	MaTrix& operator = (const MaTrix& p) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j)
				arr[i][j] = p.arr[i][j];
		}
		return *this;
	}
	double** Elements();
	void Reset();
	void Invert();
	void Rotate(double);
	void Translate(double, double, double);
	void Scale(double, double, double);
	void Shear(double, double, double, double, double, double);
	void Multiply(MaTrix);
	Point TransformPoint(Point);
	vector<Point> TransformPoints(vector<Point>);
};

void MaTrix::deleteArr(double** &a) {
	for (int i = 0; i < 4; ++i)
		delete[] a[i];
	delete[] a;
}

MaTrix::MaTrix() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j)
				arr[i][j] = 1;
			else
				arr[i][j] = 0;
		}
	}
}

MaTrix::MaTrix(double* p) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			arr[i][j] = p[4 * i + j];
		}
	}
}

MaTrix::~MaTrix() {}

double** MaTrix::Elements() {
	double **res = new double*[4];
	for (int i = 0; i < 4; ++i) {
		res[i] = new double[4];
		memcpy(res[i], arr[i], sizeof(double) * 4);
	}
	return res;
}

void MaTrix::Reset() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j)
				arr[i][j] = 0;
			else
				arr[i][j] = 1;
		}
	}
}

void MaTrix::MultiplyMatrix(double **a) {
	double **tmp = new double*[4];
	for (int i = 0; i < 4; ++i) {
		tmp[i] = new double[4];
		memset(tmp[i], 0, sizeof(double) * 4);
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				tmp[i][j] += arr[i][k] * a[k][j];
			}
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j)
			arr[i][j] = tmp[i][j];
	}
	this->deleteArr(tmp);
	tmp = NULL;
}

void MaTrix::Invert() {

}

void MaTrix::Rotate(double alpha) {
	double t = alpha * PI / 180;
	double sina = sin(t);
	double cosa = cos(t);
	MaTrix p;
	double **tmp = this->Elements();
	p.MultiplyMatrix(tmp);
	this->deleteArr(tmp);
	*this = p;
}

void MaTrix::Translate(double tx, double ty, double tz) {
	MaTrix p(1, 0, 0, 0, 1, 0, 0, 0, 1, tx, ty, tz);
	double **tmp = this->Elements();
	p.MultiplyMatrix(tmp);
	this->deleteArr(tmp);
	*this = p;
}

void MaTrix::Scale(double sx, double sy, double sz) {
	MaTrix p(sx, 0, 0, 0, sy, 0, 0, 0, sz, 0, 0, 0);
	double **tmp = this->Elements();
	p.MultiplyMatrix(tmp);
	this->deleteArr(tmp);
	*this = p;
}

void MaTrix::Shear(double xy, double xz, double yx, double yz, double zx, double zy) {
	MaTrix p(1, yx, zx, xy, 1, zy, xz, yz, 1, 0, 0, 0);
	double **tmp = this->Elements();
	p.MultiplyMatrix(tmp);
	this->deleteArr(tmp);
	*this = p;
}

void MaTrix::Multiply(MaTrix p) {
	double **a = p.Elements();
	this->MultiplyMatrix(a);
	this->deleteArr(a);
}

Point MaTrix::TransformPoint(Point p) {
	double *tmp = p.getVector();
	double *res = new double[4];
	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += (arr[k][j] * tmp[k]);
		}
	}
	Point point(res[0], res[1], res[2]);
	delete[] tmp;
	delete[] res;
	return point;
}

vector<Point> MaTrix::TransformPoints(vector<Point> p) {
	vector<Point> res;
	for (auto i : p) {
		res.push_back(this->TransformPoint(i));
	}
	return res;
}