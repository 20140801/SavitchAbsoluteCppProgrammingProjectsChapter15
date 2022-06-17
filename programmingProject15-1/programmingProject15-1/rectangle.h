#include <iostream>
#include "figure.h"
using namespace std;
#ifndef MY_RECTANGLE
#define MY_RECTANGLE

class Rectangle :public Figure
{
public:
	void erase() { cout << "Rectangle::erase()\n"; }
	void draw() { cout << "Rectangle::draw()\n"; }
};
#endif