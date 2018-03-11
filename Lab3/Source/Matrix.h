#pragma once
#include "stdafx.h"
using namespace std;
class Point2D;

#define PI 3.14159265

class MaTrix {
private:
	double arr[3][3];
	void MultiplyMatrix(double**);
	void deleteArr(double**&);
public:
	MaTrix();
	MaTrix(double, double, double, double, double, double);
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
	void Translate(double, double);
	void Scale(double, double);
	void Shear(double, double);
	void Multiply(MaTrix);
	Point2D TransformPoint(Point2D);
	vector<Point2D> TransformPoints(vector<Point2D>);
};

void MaTrix::deleteArr(double** &a) {
	for (int i = 0; i < 3; ++i)
		delete[] a[i];
	delete[] a;
}

MaTrix::MaTrix() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == j)
				arr[i][j] = 1;
			else
				arr[i][j] = 0;
		}
	}
}

MaTrix::MaTrix(double x1, double x2, double x3, double x4, double x5, double x6) {
	arr[0][0] = x1;
	arr[0][1] = x2;
	arr[1][0] = x3;
	arr[1][1] = x4;
	arr[2][0] = x5;
	arr[2][1] = x6;
	arr[0][2] = arr[1][2] = 0;
	arr[2][2] = 1;
}

MaTrix::~MaTrix() {}

double** MaTrix::Elements() {
	double **res = new double*[3];
	for (int i = 0; i < 3; ++i) {
		res[i] = new double[3];
		memcpy(res[i], arr[i], sizeof(double) * 3);
	}
	return res;
}

void MaTrix::Reset() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == j)
				arr[i][j] = 0;
			else
				arr[i][j] = 1;
		}
	}
}

void MaTrix::MultiplyMatrix(double **a) {
	double **tmp = new double*[3];
	for (int i = 0; i < 3; ++i) {
		tmp[i] = new double[3];
		memset(tmp[i], 0, sizeof(double) * 3);
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			tmp[i][j] = 0;
			for (int k = 0; k < 3; ++k) {
				tmp[i][j] += arr[i][k] * a[k][j];
			}
		}
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
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
	MaTrix p(cosa, sina, -sina, cosa, 0, 0);
	double **tmp = this->Elements();
	p.MultiplyMatrix(tmp);
	this->deleteArr(tmp);
	*this = p;
}

void MaTrix::Translate(double tx, double ty) {
	MaTrix p(1, 0, 0, 1, tx, ty);
	double **tmp = this->Elements();
	p.MultiplyMatrix(tmp);
	this->deleteArr(tmp);
	*this = p;
}

void MaTrix::Scale(double sx, double sy) {
	MaTrix p(sx, 0, 0, sy, 0, 0);
	double **tmp = this->Elements();
	p.MultiplyMatrix(tmp);
	this->deleteArr(tmp);
	*this = p;
}

void MaTrix::Shear(double a, double b) {
	MaTrix p(1, a, b, 1, 0, 0);
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

Point2D MaTrix::TransformPoint(Point2D p) {
	double *tmp = p.getVector();
	double *res = new double[3];
	for (int j = 0; j < 3; ++j) {
		res[j] = 0;
		for (int k = 0; k < 3; ++k) {
			res[j] += (arr[k][j] * tmp[k]);
		}
	}
	Point2D point((int)res[0], (int)res[1]);
	delete[] tmp;
	delete[] res;
	return point;
}

vector<Point2D> MaTrix::TransformPoints(vector<Point2D> p) {
	vector<Point2D> res;
	for (auto i : p) {
		res.push_back(this->TransformPoint(i));
	}
	return res;
}