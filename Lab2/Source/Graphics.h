#pragma once
#include "Shape.h"
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

const int Line = 1;
const int Triangle_1 = 2;
const int Triangle_2 = 3;
const int Rectangle = 4;
const int Square = 5;
const int Pentangle = 6;
const int Hexangle = 7;
const int Add = 8;
const int Sub = 9;
const int Multiple = 10;
const int Divide = 11;
const int Arrow = 12;
const int Star = 13;
const int Circle = 14;
const int Elipse = 15;
const int Red = 16;
const int Yellow = 17;
const int Green = 18;

int win = 0;
int btn = 0;
int shape = -1;

unsigned char Fill_color[3];
unsigned char Backround_color[3];

unsigned char* getPixel(int x, int y) {
	unsigned char * ptr = new unsigned char[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);
	return ptr;
}

void putPixel(int x, int y) {
	glRasterPos2i(x, y);
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, Fill_color);
	glFlush();
}

bool checkCoord(int x, int y) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

bool compareColor(unsigned char c1[], unsigned char c2[]) {
	for (int i = 0; i < 3; ++i)
		if (c1[i] != c2[i])
			return false;
	return true;
}

void boundaryFill(int x, int y) {
	if (!checkCoord(x, y)) return;
	unsigned char *cur_color = getPixel(x, y);
	if (!compareColor(cur_color, Fill_color) && !compareColor(cur_color, Backround_color)) {
		putPixel(x, y);
		delete[] cur_color;
		boundaryFill(x - 1, y);
		boundaryFill(x, y + 1);
		boundaryFill(x + 1, y);
		boundaryFill(x, y - 1);
	}
	else {
		delete[] cur_color;
	}
}

string getShape() {
	switch (shape)
	{
	case 1:
		return "duong thang";
		break;
	case 2:
		return "tam giac vuong can";
		break;
	case 3:
		return "tam giac deu";
		break;
	case 4:
		return "hinh chu nhat";
		break;
	case 5:
		return "hinh vuong";
		break;
	case 6:
		return "ngu giac deu";
		break;
	case 7:
		return "luc giac deu";
		break;
	case 8:
		return "dau cong";
		break;
	case 9:
		return "dau tru";
		break;
	case 10:
		return "dau nhan";
		break;
	case 11:
		return "dau chia";
		break;
	case 12:
		return "mui ten";
		break;
	case 13:
		return "ngoi sao";
		break;
	case 14:
		return "hinh tron";
		break;
	case 15:
		return "elipse";
		break;
	default:
		return "";
		break;
	}
}

void processMouseEvent(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cout << "To mau " << getShape() << ":" << endl;
		clock_t t = clock();
		boundaryFill(x, height - y);
		cout << (double)(clock() - t) / CLOCKS_PER_SEC << " (s)" << endl;
	}
}

void initWindow(int argc, char** argv) {
	Fill_color[0] = 255;
	Fill_color[1] = 0;
	Fill_color[2] = 0;
	int mode = GLUT_RGB | GLUT_SINGLE;
	glutInit(&argc, argv);
	glutInitDisplayMode(mode);
	glutInitWindowSize(width, height);
	glutCreateWindow("Shapes");
	gluOrtho2D(0, width, 0, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void menu(int value) {
	if (value == 0) {
		glutDestroyWindow(win);
		exit(0);
	}
	else {
		btn = value;
	}
	glutPostRedisplay();
}

void createMenu(void) {

	int tamGiac = glutCreateMenu(menu);
	glutAddMenuEntry("Vuong can", Triangle_1);
	glutAddMenuEntry("Deu", Triangle_2);

	int tuGiac = glutCreateMenu(menu);
	glutAddMenuEntry("Hinh chu nhat", Rectangle);
	glutAddMenuEntry("Hinh vuong", Square);


	int oval = glutCreateMenu(menu);
	glutAddMenuEntry("Hinh tron", Circle);
	glutAddMenuEntry("Elip", Elipse);

	int daGiacDeu = glutCreateMenu(menu);
	glutAddMenuEntry("Ngu giac deu", Pentangle);
	glutAddMenuEntry("Luc giac deu", Hexangle);

	int hinhKhac = glutCreateMenu(menu);
	glutAddMenuEntry("Mui ten", Arrow);
	glutAddMenuEntry("Ngoi sao", Star);

	int dau = glutCreateMenu(menu);
	glutAddMenuEntry("Cong", Add);
	glutAddMenuEntry("Tru", Sub);
	glutAddMenuEntry("Nhan", Multiple);
	glutAddMenuEntry("Chia", Divide);

	int toMau = glutCreateMenu(menu);
	glutAddMenuEntry("Xanh", Green);
	glutAddMenuEntry("Do", Red);
	glutAddMenuEntry("Vang", Yellow);

	int chonHinh = glutCreateMenu(menu);

	glutAddMenuEntry("Duong thang", Line);
	glutAddSubMenu("Tam giac", tamGiac);
	glutAddSubMenu("Tu giac", tuGiac);
	glutAddSubMenu("Oval", oval);
	glutAddSubMenu("Da giac deu", daGiacDeu);
	glutAddSubMenu("Hinh khac", hinhKhac);
	glutAddSubMenu("Dau", dau);
	glutAddSubMenu("To mau", toMau);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void process() {
	glClear(GL_COLOR_BUFFER_BIT);
	switch (btn) {
	case Line:
		drawLine();
		shape = Line;
		break;
	case Triangle_1:
		drawTriangle1();
		shape = Triangle_1;
		break;
	case Triangle_2:
		drawTriangle2();
		shape = Triangle_2;
		break;
	case Rectangle:
		drawRectangle();
		shape = Rectangle;
		break;
	case Square:
		drawSquare();
		shape = Square;
		break;
	case Pentangle:
		drawPentangle();
		shape = Pentangle;
		break;
	case Hexangle:
		drawHexangle();
		shape = Hexangle;
		break;
	case Circle:
		drawCircle();
		shape = Circle;
		break;
	case Elipse:
		drawElipse();
		shape = Elipse;
		break;
	case Star:
		drawStar();
		shape = Star;
		break;
	case Arrow:
		shape = Arrow;
		drawArrow();
		break;
	case Add:
		drawAdd();
		shape = Add;
		break;
	case Sub:
		drawSub();
		shape = Sub;
		break;
	case Multiple:
		drawMultiple();
		shape = Multiple;
		break;
	case Divide:
		drawDivide();
		shape = Divide;
		break;
	case Red:
		Fill_color[0] = 255;
		Fill_color[1] = 0;
		Fill_color[2] = 0;
		break;
	case Green:
		Fill_color[0] = 0;
		Fill_color[1] = 255;
		Fill_color[2] = 0;
		break;
	case Yellow:
		Fill_color[0] = 255;
		Fill_color[1] = 255;
		Fill_color[2] = 0;
		break;
	default:
		break;


	}
	glutMouseFunc(processMouseEvent);
	btn = -1;
}