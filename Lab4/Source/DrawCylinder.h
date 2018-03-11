#pragma once
#include "stdafx.h"
#include "Matrix.h"

float delta_Cylinder = 0;
void drawCylinder(GLuint texture) {
	glLoadIdentity();
	glTranslatef(0.9, -1.5, -7);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(delta_Cylinder, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glScalef(0.7, 0.7, 0.7);
	
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 360; i += 3) {
		for (int k = 0; k <= 1; k++) {
			double x = Cos(i);
			double y = Sin(i);
			glTexCoord2f(k, 1.0 * i / 360);
			glVertex3f(x, y, 1.0 / (1 - 2 * k));
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	delta_Cylinder += 0.2f;
	glFlush();
}