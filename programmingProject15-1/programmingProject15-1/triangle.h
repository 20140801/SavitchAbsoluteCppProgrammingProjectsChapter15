#include <iostream>
#include "figure.h"
using namespace std;
#ifndef MY_TRIANGLE
#define MY_TRIANGLE

class Triangle :public Figure
{
public:
	void erase() { cout << "Triangle::erase()\n"; }
	void draw() { cout << "Triangle::draw()\n"; }
};
#endif