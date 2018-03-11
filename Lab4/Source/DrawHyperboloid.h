#pragma once
#include "stdafx.h"
#include "Matrix.h"

float delta_Hyperboloid = 0;
void drawHyperboloid(GLuint texture) {
	glLoadIdentity();
	glTranslatef(-3.2, -1.7, -7);
	glScalef(0.7, 0.7, 0.7);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(delta_Hyperboloid, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	for (float i = -1; i <= 1 + eps; i += 0.01) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= 360; j += 3) {
			for (int k = 0; k <= 1; k++) {
				double z = abs(i);
				double x = (z * z * 0.5 + 0.5) * Cos(j);
				double y = (z * z * 0.5 + 0.5 ) * Sin(j);
				glTexCoord2f(1.0 * j / 360, 1.0 * (i + 1) / 2);
				glVertex3f(x, y, -i + k * 0.02);
			}
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	delta_Hyperboloid += 0.2f;
	glFlush();
}
