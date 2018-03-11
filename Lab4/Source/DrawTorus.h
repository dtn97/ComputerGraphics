#pragma once
#include "stdafx.h"
#include "Matrix.h"

float delta_Torus = 0;
void drawTorus(GLuint texture) {
	glLoadIdentity();
	glTranslatef(2.9, 1.0, -7);
	glRotatef(120, 1, 0, 0);
	glRotatef(delta_Torus, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glFrontFace(GL_CW);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	const double TAU = 2 * PI;
	float r = 0.1, c = 0.35;
	for (int i = 0; i <= 120; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= 120; j++) {
			for (int k = 0; k <= 1; k++) {
				double s = (i + k) % 120 + 0.5;
				double t = j % (120 + 1);

				double x = (c + r * cos(s * TAU / 120)) * cos(t * TAU / 120);
				double y = (c + r * cos(s * TAU / 120)) * sin(t * TAU / 120);
				double z = r * sin(s * TAU / 120);

				double u = (i + k) / (float)120;
				double v = t / (float)120;

				glTexCoord2d(u, v);
				glNormal3f(2 * x, 2 * y, 2 * z);
				glVertex3f(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd();
	}
	glFrontFace(GL_CCW);

	glDisable(GL_TEXTURE_2D);
	delta_Torus += 0.2f;
}