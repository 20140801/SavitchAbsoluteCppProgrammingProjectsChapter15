#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player
{
public:
	virtual int getGuess();
};
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
};
int ComputerPlayer::getGuess()
{
	int g = rand() % 100;
	cout << "The computer's guess number is " << g << '\n';
	return g;
}
bool checkForWin(int guess, int answer)
{
	if (answer == guess)
	{
		cout << "You're right! You win!\n";
		return true;
	}
	else if (answer < guess)
	{
		cout << "Your guess is too high.\n";
	}
	else
	{
		cout << "Your guess is too low.\n";
	}
	return false;
}
void play(Player& player1, Player& player2)
{
	int answer = 0, guess = 0;
	answer = rand() % 100;
	bool win = 0;
	while (!win)
	{
		cout << "Player 1's turn to guess.\n";
		guess = player1.getGuess();
		win = checkForWin(guess, answer);
		if (win) { break; }//I added because both win is unfair for first player
		cout << "Player 2's turn to guess.\n";
		guess = player2.getGuess();
		win = checkForWin(guess, answer);
	}
}
int main()
{
	srand(time(NULL));
	cout << "\nPlease Press Enter To Start New Game(Human vs Human)\n";
	char a;
	a = cin.get();
	HumanPlayer h1;
	HumanPlayer h2;
	ComputerPlayer c1;
	ComputerPlayer c2;
	play(h1, h2);
	cout << "\nPlease Press Enter To Start New Game(Human vs Computer)\n";
	a = cin.get();
	play(h1, c1);
	cout << "Please Press Enter To Start New Game(Computer vs Computer)\n";
	a = cin.get();
	play(c1, c2);
	return 0;
}