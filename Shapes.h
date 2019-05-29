#pragma once

#include <iostream>
#include <sstream>
#include "Based.h"
#include "Container.h"

class Shape : public Printable{
private: 
	static int count;
public: 
	Shape() {
		count++;
	}
	virtual ~Shape() {
		count--;
	}
	static int getCount() {
		return count;
	}
};

int Shape::count = 0;

class Point : public Shape, Named {
private:
	float x;
	float y;
public:
	Point(float pam_x, float pam_y) : Named("Point"), x(pam_x), y(pam_y) {
	}
	Point(Point const &copy) : Named("Point"), x(copy.x), y(copy.x) {
	}
	float getX() {
		return x;
	}
	float  getY() {
		return y;
	}
	virtual std::string getInformation() {
		std::stringstream info;
		info << "Name : Point" << std::endl << "x : " << x << "y : " << y << std::endl;
		return info.str();
	}
	friend std::ostream& operator << (std::ostream &s, Point &c) {
		return s << c.getInformation();
	}
};

class Circle : public Shape, Named {
private:
	Point center;
	float radius;
public:
	Circle(Point &pam_c, float pam_r) : Named("Circle"),center(pam_c), radius(pam_r) {
	}
	float square() {
		return 2 * 3.14f * radius;
	}
	virtual std::string getInformation() {
		std::stringstream info;
		info << "Name : Circle" << std::endl << "x : " << center.getX() << std::endl <<  "y : " << center.getY() << std::endl 
			 << "radius : " << radius << std::endl << "square : " << square() << std::endl;
		return info.str();
	}
	friend std::ostream& operator << (std::ostream &s, Circle &c) {
		return s << c.getInformation();
	}
};

class Rect : public Shape, Named {
private:
	Point p1;
	Point p2;
public: 
	Rect(Point &pam1, Point &pam2) : Named("Rect"), p1(pam1), p2(pam2) {
	}
	float perimeter() {
		float a = p1.getX() - p2.getX();
		if (a < 0) { 
			a *= -1;
		} 
		float b = p1.getY() - p2.getY();
		if (b < 0) {
			b *= -1;
		}
		return (a + b) * 2;
	}
	float square() {
		float p = (p1.getX() - p2.getX()) * (p1.getY() - p2.getY());
		if (p < 0) {
			p *= -1;
		}
		return p;
	}
	virtual std::string getInformation() {
		std::stringstream info;
		info << "Name : Rect" << std::endl << "x1 : " << p1.getX() << "y1 : " << p1.getY() << std::endl
			<< "x2 : " << p2.getX() << std::endl << "y2 : " << p2.getY() << std::endl 
			<< "square : " << square() << std::endl << "perimeter : " << perimeter() << std::endl;
		return info.str();
	}
	friend std::ostream& operator << (std::ostream &s, Rect &c) {
		return s << c.getInformation();
	}
};

class Square : public Shape, Named {
private:
	Point p1;
	Point p2;
public:
	Square(Point &pam1, Point &pam2) :Named("Square"), p1(pam1), p2(pam2) {
	}
	float perimeter() {
		float a = p1.getX() - p2.getX();
		if (a < 0) {
			a *= -1;
		}
		return a * 4;
	}
	float square() {
		return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX());
	}
	virtual std::string getInformation() {
		std::stringstream info;
		info << "Name : Square" << std::endl << "x1 : " << p1.getX() << "y1 : " << p1.getY() << std::endl
			<< "x2 : " << p2.getX() << "y2 : " << p2.getY() << std::endl
			<< "square : " << square() << std::endl << "perimeter : " << perimeter() << std::endl;
		return info.str();
	}
};

class Polyline : public Shape, Named {
private:
	Container<Point> p;
public:
	Polyline(Container<Point> const &pam) :Named("Polyline"), p(pam) {
	}
	virtual std::string getInformation() {
		std::stringstream s;
		s << "Name : Polyline" << std::endl;
		int count = 0;
		for (Container<Point>::Iterator i = p.start(); i != p.end(); i.next()) {
			s << "x" << count << " = " << p[i].getX() << "; y" << count << " = " << p[i].getY() << std::endl;
			count++;
		}
		s << "Length : " << length() << std::endl;
		return s.str();
	}
	float length() {
		float l = 0;
		for (Container<Point>::Iterator i = p.start(); i != p.end(); i.next()) {
			if ((i.getNext() == p.end())) break;
			Container<Point>::Iterator j = i.getNext();
			float x = p[i].getX() - p[j].getX();
			float y = p[i].getY() - p[j].getY();
			l = l + sqrt(x * x + y * y);
		}
		return l;
	}
	friend std::ostream& operator << (std::ostream &s, Polyline &r) {
		return s << r.getInformation();
	}
};

class Polygon : public Shape, Named {
public:
	Polygon(Container<Point> const &pam) :Named("Polygon"), p(pam) {
	}
	virtual std::string getInformation() {
		std::stringstream info;
		info << "Name : Polygon " << std::endl;
		int count = 0;
		for (Container<Point>::Iterator i = p.start(); i != p.end(); i.next()) {
			info << "x" << count << " = " << p[i].getX() << "; y" << count << " = " << p[i].getY() << std::endl;
			count++;
		}
		info << "Perimeter : " << perimeter() << std::endl;
		return info.str();
	}
	float perimeter() {
		float l = 0;
		for (Container<Point>::Iterator i = p.start(); i != p.end(); i.next()) {
			if ((i.getNext() == p.end())) break;
			Container<Point>::Iterator j = i.getNext();
			float x = p[i].getX() - p[j].getX();
			float y = p[i].getY() - p[j].getY();
			l += sqrt(x * x + y * y);
		}
		return l;
	}
	friend std::ostream& operator << (std::ostream &s, Polygon  &p){
		return s << p.getInformation();
	}
private:
	Container<Point> p;
};