#include <iostream>
#include <sstream>
#include "math.h"
#include "container.h"
#include "based.h"
#include "shapes.h"
#include "shapeFactory.h"

using namespace std;

void main()
{
	Container<Shape*> example;
	for (int i = 0; i < 20; i++)
	{
		switch (rand() % 6)
		{
		case 0:
			example.addLast(new Point(ShapeFactory::getPoint()));
			break;
		case 1:
			example.addLast(new Circle(ShapeFactory::getCircle()));
			break;
		case 2:
			example.addLast(new Rect(ShapeFactory::getRect()));
			break;
		case 3:
			example.addLast(new Square(ShapeFactory::getSquare()));
			break;
		case 4:
			example.addLast(new Polyline(ShapeFactory::getPolyline()));
			break;
		case 5:
			example.addLast(new Polygon(ShapeFactory::getPolygon()));
			break;
		default:
			break;
		}
	}
	cout << Shape::getCount() << endl;
	for (Container<Shape*>::Iterator i = example.start(); i != example.end(); i.next())
	{
		delete (example[i]);
	}
	cout << Shape::getCount();
	system("pause");
}