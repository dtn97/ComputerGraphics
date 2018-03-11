#pragma once
#include "stdafx.h"

class Graphics {
private:
	vector<Shape*> arrShape;
public:
	Graphics() {}
	void Draw() {
		for (auto i : arrShape)
			i->Draw();
	}
	Shape* getShape(int x, int y) {
		int n = arrShape.size();
		for (int i = 0; i < n; ++i) {
			if (arrShape[i]->PointLiesInsideShape(x, y) == true)
				return arrShape[i];
		}
		return NULL;
	}
	void AddShape(int type, int x, int y) {
		switch (type) {
		case Line:
			arrShape.push_back(new GL_Line(x, y));
			cout << "Add line" << endl;
			break;
		case Triangle:
			arrShape.push_back(new GL_Triangle(x, y));
			cout << "Add triangle" << endl;
			break;
		case EquilateralTriangle:
			arrShape.push_back(new GL_EquilateralTriangle(x, y));
			cout << "Add equilateral triangle" << endl;
			break;
		case Circle:
			arrShape.push_back(new GL_Circle(x, y));
			cout << "Add circle" << endl;
			break;
		case Elipse:
			arrShape.push_back(new GL_Elipse(x, y));
			cout << "Add elipse" << endl;
			break;
		case Rectangle:
			arrShape.push_back(new GL_Rectangle(x, y));
			cout << "Add rectangle" << endl;
			break;
		case Square:
			arrShape.push_back(new GL_Square(x, y));
			cout << "Add square" << endl;
			break;
		case Pentagon:
			arrShape.push_back(new GL_Pentagon(x, y));
			cout << "Add pentagon" << endl;
			break;
		case Hexagon:
			arrShape.push_back(new GL_Hexagon(x, y));
			cout << "Add hexagon" << endl;
			break;
		case Arrow:
			arrShape.push_back(new GL_Arrow(x, y));
			cout << "Add arrow" << endl;
			break;
		case Star:
			arrShape.push_back(new GL_Star(x, y));
			cout << "Add star" << endl;
			break;
		case Add:
			arrShape.push_back(new GL_Add(x, y));
			cout << "Add Add" << endl;
			break;
		case Sub:
			arrShape.push_back(new GL_Sub(x, y));
			cout << "Add Sub" << endl;
			break;
		case Mul:
			arrShape.push_back(new GL_Multiply(x, y));
			cout << "Add Multiply" << endl;
			break;
		case Divide:
			arrShape.push_back(new GL_Divide(x, y));
			cout << "Add Divide" << endl;
			break;
		}
	}
	void RemoveShape(Shape* p) {

	}
};