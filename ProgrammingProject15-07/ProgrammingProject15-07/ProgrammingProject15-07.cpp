#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class Dice
{
public:
	Dice();
	Dice(int numSides);
	virtual int rollDice()const;
protected:
	int numSides;
};
Dice::Dice()
{
	numSides = 6; //default
	srand(time(NULL));
}
Dice::Dice(int numSides)
{
	this->numSides = numSides;
	srand(time(NULL));
}
int Dice::rollDice()const
{
	return ((rand() % numSides) + 1);
}
int rollTwoDice(const Dice& die1, const Dice& die2)
{
	return die1.rollDice() + die2.rollDice();
}
class LoadedDice :public Dice
{
public:
	LoadedDice() { ; } //default
	LoadedDice(int a) :Dice(a) { ; }
	virtual int rollDice()const;
};
int LoadedDice::rollDice()const //overriding
{
	if (rand() % 2 == 0) //50%
	{
		return numSides;
	}
	else //50%
	{
		Dice::rollDice();
		//return ((rand() % numSides) + 1);
	}
}
int main()
{
	int s = 0;
	cout << "Input a side of number of first Dice :";
	while (s <= 0) { //0이하면 안되니까
		cin >> s;
	}

	Dice a(s);
	cout << "Input a side of number of second Dice :";
	s = 0;
	while (s <= 0) { //0이하면 안되니까
		cin >> s;
	}

	Dice b(s);
	int sum = 0;
	cout << "\nResult of sum of two dices is :\n";
	for (int i = 0; i < 10; i++)
	{
		int t = rollTwoDice(a, b);
		sum += t;
		cout << t << '\n'; //기댓값(s1+s2+2)/2
	}
	cout << "Mean : " << (double)sum / 10.0 << '\n';
	cout << "\n\nInput a side of number of first LoadedDice :";
	s = 0;
	while (s <= 0) {
		cin >> s;
	}
	LoadedDice c(s);

	cout << "Input a side of number of second LoadedDice :";
	s = 0;
	while (s <= 0) {
		cin >> s;
	}
	LoadedDice d(s);
	sum = 0;
	cout << "\nResult of sum of two loaded dices is :\n";
	for (int i = 0; i < 10; i++)
	{

		int t = rollTwoDice(c, d);
		sum += t;
		cout << t << '\n'; //기댓값 (3*s1+3*s2+2)/4
	}
	cout << "Mean : " << (double)sum / 10.0 << '\n';
	return 0;
}