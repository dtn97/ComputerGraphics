#pragma once
#include "stdafx.h"
#include "Matrix.h"

float delta_Disk = 0;
void drawDisk(GLuint texture) {
	glLoadIdentity();
	glTranslatef(2.7f, -1.5f, -7);
	glRotatef(delta_Disk, 0, 1, 0);
	glScalef(0.6, 0.6, 0.6);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	int delta = 5;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 360; i += delta) {
		Point p1(0, 0, 0);
		Point p2(Cos(i), Sin(i), 0);
		Point p3(Cos(i + delta), Sin(i + delta), 0);
		Point normal = calNormal(p1, p2, p3);
		glNormal3f(-normal.x, -normal.y, -normal.z);
		glTexCoord2f(0.5, 0.5);
		drawPoint(p1);
		if (i < 90) {
			glTexCoord2f(0, 1.0 * (i) / 90);
			glTexCoord2f(0, 1.0 * (i + 1) / 90);
		}
		else if (i < 180) {
			glTexCoord2f(1.0 * (i) / 180, 1);
			glTexCoord2f(1.0 * (i + 1) / 180, 1);
		}
		else if (i < 270) {
			glTexCoord2f(1, 1.0 * (270 - i) / 270);
			glTexCoord2f(1, 1.0 * (270 - i - 1) / 270);
		}
		else {
			glTexCoord2f(1.0 * (360 - i) / 360, 0);
			glTexCoord2f(1.0 * (360 - i - 1) / 360, 0);

		}
		drawPoint(p2);
		drawPoint(p3);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	delta_Disk -= 0.2f;
}