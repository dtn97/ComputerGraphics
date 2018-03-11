#pragma once
#include "stdafx.h"
#include "Matrix.h"

float delta_Paraboloid = 0;
void drawParaboloid(GLuint texture) {
	glLoadIdentity();
	glTranslatef(-1.3, -2.3, -7);
	glScalef(1.3, 1.3, 1.3);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(delta_Paraboloid, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (float i = 0; i <= 1 + eps; i += 0.01) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= 360; j += 3) {
			for (int k = 0; k <= 1; k++) {
				double x = (sqrt(i) * 0.5 + 0.1) * Cos(j);
				double y = (sqrt(i) * 0.5 + 0.1) * Sin(j);
				glTexCoord2f(1.0 * j / 360, i);
				glVertex3f(x, y, -i + k * 0.02);
			}
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	delta_Paraboloid += 0.2f;
	glFlush();
}