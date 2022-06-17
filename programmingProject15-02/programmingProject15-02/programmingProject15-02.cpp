#include <iostream>

using namespace std;
class Figure
{
public:
	virtual void erase();
	virtual void draw();
	void center();
};
class Rectangle :public Figure
{
public:
	Rectangle() { cout << "Rectangle class made\n"; }
	virtual void erase();
	virtual void draw();
};
void Rectangle::erase() {
	
	cout << "Rectangle::erase()\n";
	cout << "--------------------------\n"; //blank line
}
void Rectangle::draw() {
	cout << "Rectangle::draw()\n";
	int leng1 = 0;
	cout << "Input length 2 or more :";
	cin >> leng1;
	cout << "\n\n";
	if (leng1 < 2) { return; }
	for (int ix = 0; ix < leng1; ix++)
	{
		cout << "* ";
	}
	cout << "\n";
	for (int ix = 0; ix < leng1 - 2; ix++)
	{
		cout << "*";
		for (int jx = 0; jx < 2 * (leng1 - 1) - 1; jx++)
		{
			cout << " ";
		}
		cout << "*";
		cout << "\n";
	}
	for (int ix = 0; ix < leng1; ix++)
	{
		cout << "* ";
	}
	cout << "\n";
}
class Triangle :public Figure
{
public:
	Triangle() { cout << "Triangle class made\n"; }
	virtual void erase();
	virtual void draw();
};
void Triangle::erase()
{
	cout << "Triangle::erase()\n";
	cout << "--------------------------\n"; //blank line
}
void Triangle::draw()
{
	cout << "Triangle::draw()\n";
	int leng2 = 0;
	cout << "Input length 2 or more :";
	cin >> leng2;
	cout << "\n\n";
	if (leng2 < 2) { return; }
	for (int i = 1; i < leng2; i++) {
		cout << " ";
	}
	cout << "*\n";

	for (int i = 1; i <= leng2 - 2; i++)
	{
		for (int j = 1; j < leng2 - i; j++)
		{
			cout << " ";
		}
		cout << "*";
		for (int j = 0; j < 2 * i - 1; j++) {
			cout << " ";
		}
		cout << "*\n";
	}

	for (int i = 0; i < leng2; i++)
	{
		cout << "* ";
	}
	cout << '\n';
}
void Figure::center()
{
	cout << "Figure::center\n";
	cout << "\n\n";
	erase(); draw();
}
void Figure::erase() {
	cout << "Figure::erase()\n";
	cout << "--------------------------\n"; //blank line
}
void Figure::draw() {
	cout << "Figure::draw()\n";
}
int main() {
	Triangle tri;
	tri.draw();
	cout << "\nDerived class Triangle object calling center().\n";
	tri.center();
	Rectangle rect;
	rect.draw();
	cout << "\nDerived class Rectangle object calling center().\n";
	rect.center();
	return 0;
}