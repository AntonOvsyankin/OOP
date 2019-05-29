#pragma once

#include <iostream>
#include <sstream>
#include "Based.h"
#include "Container.h"
#include "Shapes.h"

using namespace std;

class ShapeFactory {
public:
	static Point getPoint() {
		return Point((float)(rand() % 501), (float)(rand() % 501));
	}
	static Circle getCircle() {
		Point p = ShapeFactory::getPoint();
		return Circle(p, (float)(rand() % 501));
	}
	static Rect getRect() {
		return Rect(ShapeFactory::getPoint(), ShapeFactory::getPoint());
	}
	static Square getSquare() {
		return Square(ShapeFactory::getPoint(), ShapeFactory::getPoint());
	}
	static Polyline getPolyline() {
		int n = rand() % 501 + 1;
		Container<Point> p;
		for (int i = 0; i < n; i++) {
			p.addLast(ShapeFactory::getPoint());
		}
		return Polyline(p);
	}
	static Polygon getPolygon() {
		int n = rand() % 501 + 1;
		Container<Point> p;
		for (int i = 0; i < n; i++) {
			p.addLast(ShapeFactory::getPoint());
		}
		return Polygon(p);
	}
};