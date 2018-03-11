#pragma once
#include "stdafx.h"

class Shape {
public:
	Shape() {}
	virtual ~Shape() {}
	virtual void Draw() {

	}
	virtual void process(int) {

	}
	virtual bool PointLiesInsideShape(int, int) {
		return false;
	}
	virtual string getName() {
		return "shape";
	}
};

class Polygon : public Shape {
private:
	MaTrix f;
	vector<Point2D> arrPoints;

	bool onSegment(Point2D p, Point2D q, Point2D r)
	{
		if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
			q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
			return true;
		return false;
	}
	int orientation(Point2D p, Point2D q, Point2D r)
	{
		int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

		if (val == 0) return 0;  // colinear
		return (val > 0) ? 1 : 2; // clock or counterclock wise
	}

	bool doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2)
	{
		int o1 = orientation(p1, q1, p2);
		int o2 = orientation(p1, q1, q2);
		int o3 = orientation(p2, q2, p1);
		int o4 = orientation(p2, q2, q1);

		if (o1 != o2 && o3 != o4)
			return true;
		if (o1 == 0 && onSegment(p1, p2, q1)) return true;

		if (o2 == 0 && onSegment(p1, q2, q1)) return true;

		if (o3 == 0 && onSegment(p2, p1, q2)) return true;

		if (o4 == 0 && onSegment(p2, q1, q2)) return true;

		return false; // Doesn't fall in any of the above cases
	}

	bool isInside(Point2D p)
	{
		int n = arrPoints.size();
		vector<Point2D> arr = this->Transform();
		if (n < 3)  return false;
		Point2D extreme(10000, p.y);
		int count = 0, i = 0;
		do
		{
			int next = (i + 1) % n;
			if (doIntersect(arr[i], arr[next], p, extreme))
			{
				if (orientation(arr[i], p, arr[next]) == 0)
					return onSegment(arr[i], p, arr[next]);

				count++;
			}
			i = next;
		} while (i != 0);

		return count & 1;  // Same as (count%2 == 1)
	}

	Point2D getCenterPoint() {
		int n = arrPoints.size();
		double x = 0;
		double y = 0;
		for (auto i : arrPoints) {
			x += i.x;
			y += i.y;
		}
		x = (1.0 * x) / n;
		y = (1.0 * y) / n;
		return Point2D(x, y);
	}

protected:
	void print() {
		vector<Point2D> p = this->Transform();
		for (auto i : p) {
			cout << i.x << "  " << i.y << endl;
		}
		cout << endl;
	}

	virtual vector<Point2D> Transform() {
		return f.TransformPoints(arrPoints);
	}

	virtual void Rotate(double alpha) {
		Point2D g = this->getCenterPoint();
		f.Translate(-g.x, -g.y);
		f.Rotate(alpha);
		f.Translate(g.x, g.y);
	}

	virtual void Translate(double dx, double dy) {
		f.Translate(dx, dy);
	}

	virtual void TranslateRoot() {
		Point2D g = this->getCenterPoint();
		f.Translate(-g.x, -g.y);
	}

	virtual void Scale(double sx, double sy) {
		Point2D g = this->getCenterPoint();
		f.Translate(-g.x * sx, -g.y * sy);
		f.Scale(sx, sy);
		f.Translate(g.x / sx, g.y / sy);
	}

protected:
	virtual void AddPoint(Point2D p) {
		arrPoints.push_back(p);
	}
	virtual void AddPoint(int x, int y) {
		arrPoints.push_back(Point2D(x, y));
	}
	virtual void AddPoint(vector<Point2D> p) {
		for (auto i : p)
			arrPoints.push_back(i);
	}

public:
	Polygon() : Shape() {}
	Polygon(vector<Point2D> p) : Shape() {
		for (auto i : p)
			arrPoints.push_back(i);
	}
	virtual ~Polygon() {}
	virtual void Draw() {
		glBegin(GL_LINES);
		glColor3f(255, 0, 0);
		int n = arrPoints.size();
		for (int i = 0; i < n; ++i) {
			f.TransformPoint(arrPoints[i]).drawPoint2D();
			int j = (i + 1) % n;
			f.TransformPoint(arrPoints[j]).drawPoint2D();
		}
		glEnd();
		glFlush();
	}
	virtual bool PointLiesInsideShape(int x, int y) {
		return this->isInside(Point2D(x, y));
	}
	virtual void process(int type) {
		if (type == '=')
			type = ZOOM_IN;
		if (type == '_')
			type = ZOOM_OUT;
		switch (type) {
		case RO_LEFT:
			this->Rotate(1);
			break;
		case RO_RIGHT:
			this->Rotate(-1);
			break;
		case TR_LEFT:
			this->Translate(-1, 0);
			break;
		case TR_RIGHT:
			this->Translate(1, 0);
			break;
		case TR_UP:
			this->Translate(0, 1);
			break;
		case TR_DOWN:
			this->Translate(0, -1);
			break;
		case ZOOM_IN:
			this->Scale(1.1, 1.1);
			break;
		case ZOOM_OUT:
			this->Scale(0.9, 0.9);
			break;
		}
	}
	virtual string getName() {
		return "polygon";
	}
};

class GL_Rectangle : public Polygon {
public:
	GL_Rectangle(int x, int y) : Polygon() {
		Polygon::AddPoint(0, 0);
		Polygon::AddPoint(80, 0);
		Polygon::AddPoint(80, 40);
		Polygon::AddPoint(0, 40);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	GL_Rectangle() : Polygon() {}
	~GL_Rectangle() {}
	virtual string getName() {
		return "Retangle";
	}
	virtual void add(int x, int y) {
		Polygon::AddPoint(x, y);
	}
	virtual void Translate(int dx, int dy) {
		Polygon::Translate(dx, dy);
	}
	virtual void Translate() {
		Polygon::TranslateRoot();
	}
};

class GL_Square : public Polygon {
public:
	GL_Square(int x, int y) : Polygon() {
		Polygon::AddPoint(0, 0);
		Polygon::AddPoint(0, 50);
		Polygon::AddPoint(50, 50);
		Polygon::AddPoint(50, 0);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Square";
	}
};

class GL_Triangle : public Polygon {
public:
	GL_Triangle(int x, int y) : Polygon() {
		Polygon::AddPoint(0, 0);
		Polygon::AddPoint(0, 40);
		Polygon::AddPoint(40, 0);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	GL_Triangle() : Polygon() {}
	virtual string getName() {
		return "Isosceles Right Triangle";
	}
	virtual void add(int x, int y) {
		Polygon::AddPoint(x, y);
	}
	virtual void Translate(int dx, int dy) {
		Polygon::Translate(dx, dy);
	}
	virtual void Translate() {
		Polygon::TranslateRoot();
	}
};

class GL_EquilateralTriangle : public Polygon {
public:
	GL_EquilateralTriangle(int x, int y) : Polygon() {
		Polygon::AddPoint(0, 0);
		Polygon::AddPoint(50, 0);
		Polygon::AddPoint(25, 43);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Equilateral Triangle";
	}
};

class GL_Pentagon : public Polygon {
public:
	GL_Pentagon(int x, int y) : Polygon() {
		Polygon::AddPoint(12, 12);
		Polygon::AddPoint(58, 12);
		Polygon::AddPoint(64, 50);
		Polygon::AddPoint(32, 74);
		Polygon::AddPoint(0, 50);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Pentagon";
	}
};

class GL_Hexagon : public Polygon {
public:
	GL_Hexagon(int x, int y) : Polygon() {
		Polygon::AddPoint(60, 60);
		Polygon::AddPoint(84, 60);
		Polygon::AddPoint(96, 80);
		Polygon::AddPoint(84, 102);
		Polygon::AddPoint(60, 102);
		Polygon::AddPoint(48, 80);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Hexagon";
	}
};

class GL_Add : public Polygon {
public:
	GL_Add(int x, int y) : Polygon() {
		Polygon::AddPoint(100, 100);
		Polygon::AddPoint(130, 100);
		Polygon::AddPoint(130, 70);
		Polygon::AddPoint(160, 70);
		Polygon::AddPoint(160, 100);
		Polygon::AddPoint(190, 100);
		Polygon::AddPoint(190, 130);
		Polygon::AddPoint(160, 130);
		Polygon::AddPoint(160, 160);
		Polygon::AddPoint(130, 160);
		Polygon::AddPoint(130, 130);
		Polygon::AddPoint(100, 130);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Add";
	}
};

class GL_Sub : public Polygon {
public:
	GL_Sub(int x, int y) : Polygon() {
		Polygon::AddPoint(120, 180);
		Polygon::AddPoint(200, 180);
		Polygon::AddPoint(200, 190);
		Polygon::AddPoint(120, 190);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Sub";
	}
};

class GL_Divide : public Polygon {
public:
	GL_Divide(int x, int y) : Polygon() {
		Polygon::AddPoint(100, 100);
		Polygon::AddPoint(120, 100);
		Polygon::AddPoint(160, 190);
		Polygon::AddPoint(140, 190);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Divide";
	}
};

class GL_Arrow : public Polygon {
public:
	GL_Arrow(int x, int y) : Polygon() {
		Polygon::AddPoint(100, 100);
		Polygon::AddPoint(160, 100);
		Polygon::AddPoint(160, 90);
		Polygon::AddPoint(190, 115);
		Polygon::AddPoint(160, 140);
		Polygon::AddPoint(160, 130);
		Polygon::AddPoint(100, 130);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Arrow";
	}
};

class GL_Star : public Polygon {
public:
	GL_Star(int x, int y) : Polygon() {
		Polygon::AddPoint(100, 100);
		Polygon::AddPoint(130, 114);
		Polygon::AddPoint(160, 100);
		Polygon::AddPoint(156, 131);
		Polygon::AddPoint(179, 157);
		Polygon::AddPoint(146, 157);
		Polygon::AddPoint(130, 192);
		Polygon::AddPoint(114, 157);
		Polygon::AddPoint(81, 157);
		Polygon::AddPoint(104, 131);
		Polygon::TranslateRoot();
		Polygon::Translate(x, y);
	}
	virtual string getName() {
		return "Star";
	}
};

class GL_Circle : public Shape {
private:
	Point2D centerPoint;
	double r;

	virtual void Rotate(double alpha) {

	}

	virtual void Translate(double dx, double dy) {
		centerPoint.x += dx;
		centerPoint.y += dy;
	}

	virtual void Scale(double sx, double sy) {
		r *= sx;
	}
public:
	GL_Circle(int x, int y) : Shape(), centerPoint(x, y) {
		r = 30;
	}
	virtual void Draw() {
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0, 0, 255);
		int x = centerPoint.x, y = centerPoint.y;
		int p = 1 - r;
		const int _r = r * r;
		int start = 0;
		int end = r / sqrt(2.0);
		int value = r;
		while (start != end) {
			for (int i = -1; i <= 1; i += 2) {
				for (int j = -1; j <= 1; j += 2) {
					Point2D(i * start + x, j * value + y).drawPoint2D();
					Point2D(j * value + x, i * start + y).drawPoint2D();
				}
			}
			if (p < 0) {
				p += (start * 2 + 3);
			}
			else {
				p += (start * 2 - value * 2 + 5);
			}
			if (p >= 0)
				--value;
			++start;
		}
		glEnd();
		glFlush();
	}
	virtual bool PointLiesInsideShape(int x, int y) {
		return centerPoint.getDistance(x, y) <= r;
	}
	virtual void process(int type) {
		if (type == '=')
			type = ZOOM_IN;
		if (type == '_')
			type = ZOOM_OUT;
		switch (type) {
		case RO_LEFT:
			this->Rotate(1);
			break;
		case RO_RIGHT:
			this->Rotate(-1);
			break;
		case TR_LEFT:
			this->Translate(-1, 0);
			break;
		case TR_RIGHT:
			this->Translate(1, 0);
			break;
		case TR_UP:
			this->Translate(0, 1);
			break;
		case TR_DOWN:
			this->Translate(0, -1);
			break;
		case ZOOM_IN:
			this->Scale(1.1, 1.1);
			break;
		case ZOOM_OUT:
			this->Scale(0.9, 0.9);
			break;
		}
	}
	virtual string getName() {
		return "Circle";
	}
};

class GL_Elipse : public Shape {
private:
	Point2D centerPoint;
	double rx, ry;
	MaTrix f;

	virtual void Rotate(double alpha) {
		f.Translate(-centerPoint.x, -centerPoint.y);
		f.Rotate(alpha);
		f.Translate(centerPoint.x, centerPoint.y);
	}

	virtual void Translate(double dx, double dy) {
		f.Translate(dx, dy);
	}

	virtual void Scale(double sx, double sy) {
		rx *= sx;
		ry *= sy;
	}
public:
	GL_Elipse(int x, int y) : Shape(), centerPoint(x, y), f() {
		rx = 40;
		ry = 25;
	}
	virtual void Draw() {
		int a = rx, b = ry;
		int x = centerPoint.x, y = centerPoint.y;
		int p = (int)floor(a * 2 / 4.0) + b * b - a * a * b;
		int _x = 0;
		int _y = b;
		int dx = 2 * b * b * _x;
		int dy = 2 * a * a * _y;
		int _a = a * a;
		int _b = b * b;
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0, 255, 0);
		do {
			f.TransformPoint(Point2D(_x + x, _y + y)).drawPoint2D();
			f.TransformPoint(Point2D(-_x + x, _y + y)).drawPoint2D();;
			f.TransformPoint(Point2D(_x + x, -_y + y)).drawPoint2D();
			f.TransformPoint(Point2D(-_x + x, -_y + y)).drawPoint2D();
			if (p < 0) {
				++_x;
				dx += 2 * _b;
				p += dx + _b;
			}
			else {
				++_x;
				--_y;
				dx += +2 * _b;
				dy -= 2 * _a;
				p += dx - dy + _b;
			}
		} while (dx < dy);

		p = _b * (_x + 0.5) * (_x + 0.5) + _a *(_y - 1) * (_y - 1) - _a * _b;
		while (_y > 0) {
			f.TransformPoint(Point2D(_x + x, _y + y)).drawPoint2D();
			f.TransformPoint(Point2D(-_x + x, _y + y)).drawPoint2D();;
			f.TransformPoint(Point2D(_x + x, -_y + y)).drawPoint2D();
			f.TransformPoint(Point2D(-_x + x, -_y + y)).drawPoint2D();
			if (p <= 0) {
				++_x;
				--_y;
				p += 2 * _b * _x - 2 * _a * _y + _a;
			}
			else {
				--_y;
				p += -2 * _a * _y + _a;
			}
		}
		glEnd();
		glFlush();
	}
	virtual bool PointLiesInsideShape(int x, int y) {
		double a = centerPoint.x - x;
		double b = centerPoint.y - y;
		return a * a / (rx * rx) + b * b / (ry * ry) <= 1;
	}
	virtual void process(int type) {
		if (type == '=')
			type = ZOOM_IN;
		if (type == '_')
			type = ZOOM_OUT;
		switch (type) {
		case RO_LEFT:
			this->Rotate(1);
			break;
		case RO_RIGHT:
			this->Rotate(-1);
			break;
		case TR_LEFT:
			this->Translate(-1, 0);
			break;
		case TR_RIGHT:
			this->Translate(1, 0);
			break;
		case TR_UP:
			this->Translate(0, 1);
			break;
		case TR_DOWN:
			this->Translate(0, -1);
			break;
		case ZOOM_IN:
			this->Scale(1.1, 1.1);
			break;
		case ZOOM_OUT:
			this->Scale(0.9, 0.9);
			break;
		}
	}
	virtual string getName() {
		return "Elipse";
	}
};

class GL_Multiply : public Shape {
private:
	GL_Rectangle p1;
	GL_Rectangle p2;
public:
	GL_Multiply(int x, int y) : Shape(), p1(), p2() {
		p1.add(100, 100);
		p1.add(120, 100);
		p1.add(160, 190);
		p1.add(140, 190);
		p2.add(100, 190);
		p2.add(120, 190);
		p2.add(160, 100);
		p2.add(140, 100);
		p1.Translate();
		p1.Translate(x, y);
		p2.Translate();
		p2.Translate(x, y);
	}
	virtual void Draw() {
		p1.Draw();
		p2.Draw();
	}
	virtual bool PointLiesInsideShape(int x, int y) {
		return p1.PointLiesInsideShape(x, y) || p2.PointLiesInsideShape(x, y);
	}
	virtual void process(int type) {
		p1.process(type);
		p2.process(type);
	}
	virtual string getName() {
		return "Multiply";
	}
};

class GL_Line : public Shape {
private:
	Point2D p1;
	Point2D p2;
public:
	GL_Line(int x, int y) : Shape(), p1(0, 0), p2(x, y) {

	}
	virtual void Draw() {
		glBegin(GL_LINES);
		glColor3f(0, 0, 255);
		p1.drawPoint2D();
		p2.drawPoint2D();
		glEnd();
		glFlush();
	}
	virtual bool PointLiesInsideShape(int x, int y) {
		return false;
	}
	virtual void process(int type) {

	}
	virtual string getName() {
		return "Line";
	}
};