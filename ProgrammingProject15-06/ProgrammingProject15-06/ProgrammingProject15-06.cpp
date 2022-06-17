#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class Player
{
protected:
	int topBoundary = 99; //추가 (가능한 최대값)
	int lowBoundary = 0; //추가 (가능한 최소값)
public:
	virtual int getGuess();
	virtual bool checkForWin(int guess, int answer);
	void setTopBound(int a) { topBoundary = a; } //추가
	void setLowBound(int a) { lowBoundary = a; } //추가
	Player& operator=(const Player& right); //추가
};
Player& Player::operator=(const Player& right)
{
	this->topBoundary = right.topBoundary;
	this->lowBoundary = right.lowBoundary;
	return *this;
}
bool Player::checkForWin(int guess, int answer)
{
	if (answer == guess)
	{
		cout << "You're right! You win!\n";
		return true;
	}
	else if (answer < guess)
	{
		cout << "Your guess is too high.\n";
		if (guess <= topBoundary) {
			setTopBound(guess - 1);
		}
	}
	else
	{
		cout << "Your guess is too low.\n";
		if (guess >= lowBoundary) {
			setLowBound(guess + 1);
		}
	}
	return false;
}
void play(Player& player1, Player& player2)
{
	player1.setTopBound(99); player1.setLowBound(0);
	player2.setTopBound(99); player2.setLowBound(0); //초기화
	int answer = 0, guess = 0;
	answer = rand() % 100;
	bool win = 0;
	while (!win)
	{
		cout << "Player 1's turn to guess.\n";
		guess = player1.getGuess();
		win = player1.checkForWin(guess, answer);
		player2 = player1;
		if (win) { break; }//I added because both win is unfair for first player
		cout << "Player 2's turn to guess.\n";
		guess = player2.getGuess();
		win = player2.checkForWin(guess, answer);
		if (win) { break; }
		player1 = player2;
	}
	player1.setTopBound(99); player1.setLowBound(0);
	player2.setTopBound(99); player2.setLowBound(0); //초기화
}
int Player::getGuess()
{
	return 0;
}
class HumanPlayer :public Player
{
public:
	virtual int getGuess();
};
int HumanPlayer::getGuess()
{
	int g = -1;
	while (g < 0 || g >= 100) {
		cout << "Enter your guess number(0~99) :";
		cin >> g;
	}
	return g;
}
class ComputerPlayer : public Player
{
public:
	virtual int getGuess();
	int range() { return topBoundary - lowBoundary + 1; } //추가 가능한 범위의 크기 리턴
};
int ComputerPlayer::getGuess()
{
	int g = (rand() % range()) + lowBoundary; //가능한 범위 내에서 무작위
	cout << "The computer's guess number is " << g << '\n';
	return g;
}

int main()
{
	srand(time(NULL));
	char a;
	HumanPlayer h1;
	ComputerPlayer c1;
	cout << "Please Press Enter To Start New Game(Human vs Computer)\n";
	a = cin.get();
	play(h1, c1);
	cout << "\nPlease Press Enter To Start Second Game(Human vs Computer)\n";
	a = cin.get();
	play(h1, c1);
	return 0;
}