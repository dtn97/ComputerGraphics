#include "stdafx.h"

int main(int argc, char** argv) {

	initWindow(argc, argv);
	createMenu();
	glutDisplayFunc(process);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutMainLoop();

	return 0;
}