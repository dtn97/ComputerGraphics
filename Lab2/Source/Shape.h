#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\glut.h"
#include "Dependencies\freeglut\freeglut.h"
#include <cmath>
#include <vector>
#include <ctime>
using namespace std;

const int width = 500;
const int height = 300;

void SetPixel(int x, int y) {
	glVertex2i(x, y);
	
}

void drawLine() {
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2i(0, 0);
	glVertex2i(width - 1, height - 1);
	glEnd();
	glFlush();
}

void drawTriangle1() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(30, 30);
	glVertex2i(30, 70);
	glVertex2i(70, 30);
	glEnd();
	glFlush();
}

void drawTriangle2() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(30, 30);
	glVertex2i(80, 30);
	glVertex2i(55, 73);
	glEnd();
	glFlush();
}

void drawRectangle() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(2 * 25, 2 * 25);
	glVertex2i(2 * 65, 2 * 25);
	glVertex2i(2 * 65, 2 * 45);
	glVertex2i(2 * 25, 2 * 45);
	glEnd();
	glFlush();
}

void drawSquare() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(2 * 25, 2 * 25);
	glVertex2i(2 * 25, 2 * 50);
	glVertex2i(2 * 50, 2 * 50);
	glVertex2i(2 * 50, 2 * 25);
	glEnd();
	glFlush();
}

void drawPentangle() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(20, 20);
	glVertex2i(60, 20);
	glVertex2i(72, 58);
	glVertex2i(40, 82);
	glVertex2i(8, 58);
	glEnd();
	glFlush();
}

void drawHexangle() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(1.2 * 50, 1.2 * 50);
	glVertex2i(70 * 1.2, 1.2 * 50);
	glVertex2i(1.2 * 80, 1.2 * 67);
	glVertex2i(70 * 1.2, 1.2 * 85);
	glVertex2i(50 * 1.2, 1.2 * 85);
	glVertex2i(40 * 1.2, 67 * 1.2);
	glEnd();
	glFlush();
}

void drawCircle() {
	int x = 100, y = 100, r = 30;
	int p = 1 - r;
	const int _r = r * r;
	int start = 0;
	int end = r / sqrt(2.0);
	int value = r;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
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
	glEnd();
	glFlush();
}

void drawElipse() {
	int a = 40, b = 20;
	int x = 100, y = 100;
	int p = (int)floor(a * 2 / 4.0) + b * b - a * a * b;
	int _x = 0;
	int _y = b;
	int dx = 2 * b * b * _x;
	int dy = 2 * a * a * _y;
	int _a = a * a;
	int _b = b * b;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
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
	glEnd();
	glFlush();
}

void drawStar() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(0.8 * 40, 0.8 * 140);
	glVertex2i(0.8 * 160, 0.8 * 140);
	glVertex2i(0.8 * 100, 0.8 * 100);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(0.8 * 100, 0.8 * 180);
	glVertex2i(0.8 * 50, 0.8 * 70);
	glVertex2i(0.8 * 100, 0.8 * 100);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(0.8 * 100, 0.8 * 180);
	glVertex2i(0.8 * 150, 0.8 * 70);
	glVertex2i(0.8 * 100, 0.8 * 100);
	glEnd();
	glFlush();
}

void drawArrow() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(120, 175);
	glVertex2i(200, 175);
	glVertex2i(200, 195);
	glVertex2i(120, 195);
	glEnd();
	glFlush(); 
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(200, 210);
	glVertex2i(240, 180);
	glVertex2i(200, 160);
	glEnd();
	glFlush();
	
}

void drawAdd() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(150, 150);
	glVertex2i(160, 150);
	glVertex2i(160, 220);
	glVertex2i(150, 220);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(130, 180);
	glVertex2i(180, 180);
	glVertex2i(180, 190);
	glVertex2i(130, 190);
	glEnd();
	glFlush();
}

void drawSub() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(120, 180);
	glVertex2i(200, 180);
	glVertex2i(200, 190);
	glVertex2i(120, 190);
	glEnd();
	glFlush();
}

void drawMultiple() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(100, 100);
	glVertex2i(120, 100);
	glVertex2i(160, 190);
	glVertex2i(140, 190);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(100, 190);
	glVertex2i(120, 190);
	glVertex2i(160, 100);
	glVertex2i(140, 100);
	glEnd();
	glFlush();
}

void drawDivide() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(100, 100);
	glVertex2i(120, 100);
	glVertex2i(160, 190);
	glVertex2i(140, 190);
	glEnd();
}

