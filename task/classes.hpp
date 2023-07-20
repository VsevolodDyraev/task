#pragma once
#include <iostream>
#include <fstream>
#include<vector>


class Otrezki;

struct point
{
	point(double x_,double y_): x(x_), y(y_){}
	point(point *p): x(p->x), y(p->y) {}
	point():x(0),y(0){}

	double x;
	double y;
};


class Mnogougolnik
{
private:
	std::vector<point> ugli;

public:
	Mnogougolnik();
	~Mnogougolnik();
	void print();
	void check_o(const Otrezki& o1);
};

struct Otrezok
{
	point p[2];

	Otrezok(point p1, point p2) {
		p[0] = p1;
		p[1] = p2;
	}
};

struct Otrezki
{
private:
	std::vector<Otrezok> otrez;
	friend void Mnogougolnik::check_o(const Otrezki& o1);
public:
	Otrezki();
	~Otrezki();

	void print();
};

