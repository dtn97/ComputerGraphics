#pragma once
#include "stdafx.h"

int win, val = -1;
Shape* curShape;
Graphics gp;
int curX = 200;
int curY = 200;

void processMouseEvent(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		curX = x;
		curY = height - y;
		curShape = gp.getShape(curX, curY);
		if (curShape != NULL)
			cout << curShape->getName() << endl;
	}
}

void SpecialInput(int key, int x, int y) {
	if (curShape != NULL)
		curShape->process(key);
	glClear(GL_COLOR_BUFFER_BIT);
	gp.Draw();
}

void MyKeyboardFunc(unsigned char key, int x, int y) {
	if (curShape != NULL)
		curShape->process(key);
	glClear(GL_COLOR_BUFFER_BIT);
	gp.Draw();
}

void initWindow(int argc, char** argv) {
	int mode = GLUT_RGB | GLUT_SINGLE;
	glutInit(&argc, argv);
	glutInitDisplayMode(mode);
	glutInitWindowSize(width, height);
	glutCreateWindow("1512387_Lab3");
	gluOrtho2D(0, width, 0, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void menu(int value) {
	if (value == 0) {
		glutDestroyWindow(win);
		exit(0);
	}
	else {
		val = value;
	}
	glutPostRedisplay();
}

void createMenu(void) {

	int tamGiac = glutCreateMenu(menu);
	glutAddMenuEntry("Vuong can", Triangle);
	glutAddMenuEntry("Deu", EquilateralTriangle);

	int tuGiac = glutCreateMenu(menu);
	glutAddMenuEntry("Hinh chu nhat", Rectangle);
	glutAddMenuEntry("Hinh vuong", Square);


	int oval = glutCreateMenu(menu);
	glutAddMenuEntry("Hinh tron", Circle);
	glutAddMenuEntry("Elip", Elipse);

	int daGiacDeu = glutCreateMenu(menu);
	glutAddMenuEntry("Ngu giac deu", Pentagon);
	glutAddMenuEntry("Luc giac deu", Hexagon);

	int hinhKhac = glutCreateMenu(menu);
	glutAddMenuEntry("Mui ten", Arrow);
	glutAddMenuEntry("Ngoi sao", Star);

	int dau = glutCreateMenu(menu);
	glutAddMenuEntry("Cong", Add);
	glutAddMenuEntry("Tru", Sub);
	glutAddMenuEntry("Nhan", Mul);
	glutAddMenuEntry("Chia", Divide);

	int chonHinh = glutCreateMenu(menu);

	glutAddMenuEntry("Duong thang", Line);
	glutAddSubMenu("Tam giac", tamGiac);
	glutAddSubMenu("Tu giac", tuGiac);
	glutAddSubMenu("Oval", oval);
	glutAddSubMenu("Da giac deu", daGiacDeu);
	glutAddSubMenu("Hinh khac", hinhKhac);
	glutAddSubMenu("Dau", dau);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void process() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (val != -1) {
		gp.AddShape(val, curX, curY);
	}
	glutMouseFunc(processMouseEvent);
	glutKeyboardFunc(MyKeyboardFunc);
	glutSpecialFunc(SpecialInput);
	gp.Draw();
	val = -1;
}