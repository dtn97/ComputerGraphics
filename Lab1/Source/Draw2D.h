#pragma once


#include <cmath>
#include <algorithm>
#include <ctime>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\glut.h"
using namespace std;

void SetPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void DrawLine_DDA(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	int step = 0;

	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);

	if (step == 0) {
		SetPixel(x1, y1);
		return;
	}

	float X_Increment = 1.0 * dx / step;
	float Y_Increment = 1.0 * dy / step;

	float x = 1.0 * x1;
	float y = 1.0 * y1;

	int i = 0;
	while (i < step) {
		SetPixel(round(x), round(y));
		x += X_Increment;
		y += Y_Increment;
		++i;
	}
}

void DrawLine_Bresenham(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx == 0 && dy == 0) {
		SetPixel(x1, y1);
		return;
	}

	int p = 2 * dy - dx;
	const int d1 = 2 * abs(dy);
	const int d2 = 2 * (abs(dy) - abs(dx));

	int X_Increment = (x1 < x2 ? 1 : -1);
	int Y_Increment = (y1 < y2 ? 1 : -1);

	SetPixel(x1, y1);
	while (x1 != x2) {
		if (p < 0) {
			p += d1;
		}
		else {
			p += d2;
			y1 += Y_Increment;
		}
		x1 += X_Increment;
		SetPixel(x1, y1);
	}
}

void DrawLine_MidPoint(int x1, int y1, int x2, int y2) {
	if (y1 >= y2) {
		swap(x1, x2);
		swap(y1, y2);
	}

	int a = y2 - y1;
	int b = x1 - x2;
	int c = x2 * y1 - x1 * y2;

	if (a == 0 && b == 0) {
		SetPixel(x1, y1);
		return;
	}

	const int _a = 2 * a;
	const int _b = 2 * b;
	const int _c = 2 * c;
	const int X_Increment = (x1 < x2 ? 1 : -1);

	while (x1 != x2) {
		SetPixel(x1, y1);
		x1 += X_Increment;
		if ((_a * x1 + _b * y1 + _b + _c) >= 0)
			++y1;
	}
}

void DrawCircle_MidPoint(int x, int y, int r) {
	int p = 1 - r;
	const int _r = r * r;
	int start = 0;
	int end = r / sqrt(2.0);
	int value = r;

	while (start != end) {
		for (int i = -1; i <= 1; i += 2) {
			for (int j = -1; j <= 1; j += 2) {
				SetPixel(i * start + x, j * value + y);
				SetPixel(j * value + y, i * start + x);
			}
		}
		if (p < 0) {
			p += (start * 2 + 3);
		}
		else {
			p += (start * 2 - value * 2 + 5);
		}
		if (p >= 0)
			--value;
		++start;
	}
}

void DrawElipse_MidPoint(int x, int y, int a, int b) {
	int p = (int)floor(a * 2 / 4.0) + b * b - a * a * b;

	int _x = 0;
	int _y = b;
	int dx = 2 * b * b * _x;
	int dy = 2 * a * a * _y;
	int _a = a * a;
	int _b = b * b;

	do {
		SetPixel(_x + x, _y + y);
		SetPixel(-_x + x, _y + y);
		SetPixel(_x + x, -_y + y);
		SetPixel(-_x + x, -_y + y);
		if (p < 0) {
			++_x;
			dx += 2 * _b;
			p += dx + _b;
		}
		else {
			++_x;
			--_y;
			dx += +2 * _b;
			dy -= 2 * _a;
			p += dx - dy + _b;
		}
	} while (dx < dy);

	p = _b * (_x + 0.5) * (_x + 0.5) + _a *(_y - 1) * (_y - 1) - _a * _b;
	while (_y > 0) {
		SetPixel(_x + x, _y + y);
		SetPixel(-_x + x, _y + y);
		SetPixel(_x + x, -_y + y);
		SetPixel(-_x + x, -_y + y);
		if (p <= 0) {
			++_x;
			--_y;
			p += 2 * _b * _x - 2 * _a * _y + _a;
		}
		else {
			--_y;
			p += -2 * _a * _y + _a;
		}
	}

}

void DrawParapol_MidPoint(int x, int y, int a) {
	int p = 2 * a - 1;
	int _x = 0;
	int _y = 0;
	int pivot = 2 * a;

	while (_x <= pivot) {
		SetPixel(_x + x, _y + y);
		SetPixel(-_x + x, _y + y);
		if (p < 0) {
			p += 4 * a - 3 - 2 * _x;
			++_x;
			++_y;
		}
		else {
			p -= 3 + 2 * _x;
			++_x;
		}
	}

	p = floor(4 * a * (_y + 1) - (_x + 0.5) * (_x + 0.5));
	while (_x < 500) {
		SetPixel(_x + x, _y + y);
		SetPixel(-_x + x, _y + y);
		if (p < 0) {
			p += 4 * a;
			++_y;
		}
		else {
			p += 4 * a - 2 - 2 * _x;
			++_x;
			++_y;
		}
	}
}

void DrawHyperbol_MidPoint(int x, int y, int a, int b) {

	int p = 0;
	int _x = a;
	int _y = 0;
	int _a = a * a;
	int _b = b * b;

	p = 1.0 * _b / 4 + a * _b - _a;

	int end = (a <= b ? 500 : b * b / sqrt(_a - _b));

	while (_y < end) {
		SetPixel(x + _x, y + _y);
		SetPixel(x - _x, y + _y);
		SetPixel(x + _x, y - _y);
		SetPixel(x - _x, y - _y);
		if (p < 0) {
			p += (2 * _x + 2) * _b - (2 * _y + 3) * _a;
			++_x;
		}
		else {
			p -= _a * (2 * _y + 3);
		}
		++_y;
	}

	p = _b * pow(_a / sqrt(_a - _b) + 1, 2.0) - _a *pow(_b / sqrt(_a - _b) + 0.5, 2) - _a * _b;
	while (_x < 500) {
		SetPixel(x + _x, y + _y);
		SetPixel(x - _x, y + _y);
		SetPixel(x + _x, y - _y);
		SetPixel(x - _x, y - _y);
		if (p < 0) {
			p += (2 * _x + 3) * _b;
		}
		else {
			p += (2 * _x + 3) * _b - (2 * _y + 2) * _a;
			++_y;
		}
		++_x;
	}
}
