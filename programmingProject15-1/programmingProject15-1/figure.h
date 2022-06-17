#include <iostream>
using namespace std;
#ifndef MY_FIGURE
#define MY_FIGURE
class Figure
{
public:
	//When using vitual function
	virtual void erase(); 
	virtual void draw();

	//When using no vitual function
	//void erase();
	//void draw();
	void center();
};
void Figure::center()
{
	cout << "Figure::center()\n";
	erase(); draw();
}
void Figure::erase() {
	cout << "Figure::erase()\n";
}
void Figure::draw() {
	cout << "Figure::draw()\n";
}
#endif