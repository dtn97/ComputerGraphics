#include "Draw2D.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Dependencies\freeglut\freeglut.h"

int n;
int x, y, a, b, type;
float _time;

void init2D(int argc, char** argv)
{
	int mode = GLUT_RGB | GLUT_SINGLE;
	glutInit(&argc, argv);
	glutInitDisplayMode(mode);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Simple");
	gluOrtho2D(0, 500, 0, 500);

	
}

void show() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(1.0, 0.0, 0.0);

	clock_t t = clock();

	switch (type) {
	case 0:
		DrawLine_DDA(x, y, a, b);
		break;
	case 1:
		DrawLine_Bresenham(x, y, a, b);
		break;
	case 2:
		DrawLine_MidPoint(x, y, a, b);
		break;
	case 3:
		DrawCircle_MidPoint(x, y, a);
		break;
	case 4:
		DrawElipse_MidPoint(x, y, a, b);
		break;
	case 5:
		DrawParapol_MidPoint(x, y, a);
		break;
	case 6:
		DrawHyperbol_MidPoint(x, y, a, b);
		break;
	}

	t = (1.0 * (clock() - t) / CLOCKS_PER_SEC);

	glFlush();
}

int main(int argc, char** argv) {
	fstream f;
	f.open("input.txt", ios_base::in);
	f >> n;
	
	for (int i = 0; i < n; ++i) {
		f >> type;
		if (type == 3 || type == 5) {
			f >> x >> y >> a;
		}
		else {
			f >> x >> y >> a >> b;
		}

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Computer Graphics");
		glClearColor(0, 0, 0, 0.0);
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0.0, 1200, 0.0, 1000);
		glutDisplayFunc(show);
		cout << "Test number " << i + 1 << ": " << setprecision(10) << _time << endl;
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutMainLoop();
	}

	system("pause");
	return 0;
}