#pragma once
#include "stdafx.h"
#include "DrawSphere.h"
#include "DrawBox.h"
#include "DrawCylinder.h"
#include "DrawCone.h"
#include "DrawTorus.h"
#include "DrawHyperboloid.h"
#include "DrawParaboloid.h"
#include "DrawDisk.h"
char title[] = "1512387_Lab4";
int refreshMills = 10;
GLuint	texture[8];
string textures_name[] = { "textures/3.jpg",
"textures/2.jpg",
"textures/1.jpg",
"textures/4.jpg"
};


GLuint loadGLTextures()
{
	for (int i = 0; i < 8; i++) {
		int random = (rand() + rand() * rand() + i) % 4;
		texture[i] = SOIL_load_OGL_texture
		(
			textures_name[random].c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);
	}

	return true;
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	drawBox(texture[0]);
	drawSphere(texture[1]);
	drawCylinder(texture[2]);
	drawCone(texture[3]);
	drawTorus(texture[4]);
	drawHyperboloid(texture[5]);
	drawParaboloid(texture[6]);
	drawDisk(texture[7]);
	glutSwapBuffers();
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMills, timer, 0);
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}