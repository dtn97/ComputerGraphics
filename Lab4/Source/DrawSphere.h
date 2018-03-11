#pragma once
#include "stdafx.h"
#include "Matrix.h"

float delta_Sphere = 0;
void drawSphere(GLuint texture){
	glLoadIdentity();
	glTranslatef(0.9f, 1.3f, -7);
	glRotatef(delta_Sphere, 0, 1, 0);
	glScalef(0.6, 0.6, 0.6);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	Point normal;
	for (int i = -90; i <= 90; i += 3) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= 360; j += 2 * 3) {
			Point p1 = vertex(j, i);
			Point p2 = vertex(j + 2 * 3, i);
			Point p3 = vertex(j, i + 3);
			normal = calNormal(p1, p2, p3);
			glNormal3f(-normal.x, -normal.y, -normal.z);
			glTexCoord2f(1.0 * (j) / 360, 1.0 * (90 + i) / 180);
			drawPoint(p1);
			glTexCoord2f(1.0 * (j) / 360, 1.0 * (90 + i + 3) / 180);
			drawPoint(p3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	delta_Sphere -= 0.2f;
}