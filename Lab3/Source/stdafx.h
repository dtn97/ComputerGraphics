#pragma once
#pragma comment(lib, "windowscodecs.lib")
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\glut.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <string>
#include "stdint.h"
using namespace std;

#define width 1000
#define height 800

#define Line 1
#define Triangle 2
#define EquilateralTriangle 3
#define Rectangle 4
#define Square 5
#define Pentagon 6
#define Hexagon 7
#define Add 8
#define Sub 9
#define Mul 10
#define Divide 11
#define Arrow 12
#define Star 13
#define Circle 14
#define Elipse 15
#define Red 16
#define Yellow 17
#define Green 18

#define RO_LEFT 'l'
#define RO_RIGHT 'r'
#define TR_UP GLUT_KEY_UP
#define TR_DOWN GLUT_KEY_DOWN
#define TR_LEFT GLUT_KEY_LEFT
#define TR_RIGHT GLUT_KEY_RIGHT
#define ZOOM_IN '+'
#define ZOOM_OUT '-'
#define DELETE 127

#define DCX 720

#include "Point2D.h"
#include "Matrix.h"
#include "Shape.h"
#include "Graphics.h"
#include "GL_Tool.h"

