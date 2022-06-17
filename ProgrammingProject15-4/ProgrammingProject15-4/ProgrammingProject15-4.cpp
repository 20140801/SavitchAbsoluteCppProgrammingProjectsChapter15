#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class Creature
{
private:
	int strength = 20;
	int hitpoints = 100;
protected:
	int damage = (rand() % strength) + 1;
public:

	Creature() { ; }
	Creature(int newStrength, int newHit) : strength(newStrength), hitpoints(newHit) { ; }
	virtual int getDamage();
	virtual string getSpecies() = 0;//순수가상
	int getStr() { return strength; } //get set함수
	int getHit() { return hitpoints; }
	void setStr(int s) { strength = s; }
	void setHit(int h) { hitpoints = h; }
	//int battleArena(Creature& creature1, Creature& creature2);
};
int Creature::getDamage() //Human과 같음
{
	//srand(time(NULL));
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " << damage << " points!\n";
	return damage;
}
int battleArena(Creature& creature1, Creature& creature2)
{
	return (creature2.getHit() - creature1.getDamage());
}
class Human :public Creature
{
public:
	Human() { ; } //Intentionly empty
	Human(const int str, const int hit) :Creature(str, hit) { ; }
	string getSpecies() { return "Human"; }
};
class Demons :public Creature
{
public:
	Demons() { ; }
	Demons(const int str, const int hit) :Creature(str, hit) { ; }
	void demonsDamage();
	virtual string getSpecies() { return "Demons"; }
};
void Demons::demonsDamage()
{
	if ((rand() % 100) < 5) //5% 확률
	{
		damage += 50;
		cout << "Demonic attack inflicts 50 additonal damage points!\n";
	}
}
class Cyberdemon :public Demons
{
public:
	Cyberdemon() { ; }
	Cyberdemon(const int str, const int hit) :Demons(str, hit) { ; }
	string getSpecies() { return "Cyberdemon"; }
	int getDamage();
};
int Cyberdemon::getDamage() {
	damage = (rand() % getStr()) + 1;
	cout << getSpecies() << " attacks for " << damage << " points!\n";
	demonsDamage();
	return damage;
}
class Balrog :public Demons
{
public:
	Balrog() { ; }
	Balrog(const int str, const int hit) :Demons(str, hit) { ; }
	string getSpecies() { return "Balrog"; }
	int getDamage();
};
int Balrog::getDamage()
{
	//srand(time(NULL));
	damage = (rand() % getStr()) + 1;
	cout << getSpecies() << " attacks for " << damage << " points!\n";
	demonsDamage();
	int damage2 = (rand() % getStr()) + 1;
	cout << "Balrog speed attack inflicts " << damage2 << " additional damage points!\n";
	damage += damage2;
	return damage;
}
class Elf :public Creature
{
public:
	Elf() { ; }
	Elf(const int str, const int hit) :Creature(str, hit) { ; }
	int getDamage();
	string getSpecies() { return "Elf"; }
};
int Elf::getDamage()
{
	//srand(time(NULL));
	damage = (rand() % getStr()) + 1;
	cout << getSpecies() << " attacks for " << damage << " points!\n";
	if (rand() % 10 == 0) //10퍼
	{
		cout << "Magical attack inflicts " << damage << " additional damage points!\n";
		damage += damage;
	}
	return damage;
}
int main()
{
	srand(time(NULL));
	Human human(25, 200);
	Balrog balrog(22, 100);
	cout << "FIGHTING MATCH\n";
	cout <<"    " << human.getSpecies() << " Strength : " << human.getStr() << " Hit Point : " << human.getHit();
	cout<<"\nVS " << balrog.getSpecies() << " Strength : " << balrog.getStr() << " Hit Point : " << balrog.getHit() << "\n\n\n";
	do
	{
		
		int humanHit = battleArena(human, balrog);
		if (humanHit <= 0) { humanHit = 0; } //죽으면 0
		balrog.setHit(humanHit);

		cout << '\n' << balrog.getSpecies() << " hit points : " << balrog.getHit() << "\n\n";
		
		int balrogHit = battleArena(balrog, human);
		if (balrogHit <= 0) { balrogHit = 0; }
		human.setHit(balrogHit);
		cout << '\n' << human.getSpecies() << " hit points : " << human.getHit() << "\n\n";
		if (human.getHit() <= 0 && balrog.getHit() <= 0)
		{
			cout << "\n\nDraw!\n\n";
			break;
		}
		else if (balrog.getHit() <= 0)
		{
			cout << "\n\nHuman wins!\n\n";
			break;
		}
		else if (human.getHit() <= 0)
		{
			cout << "\n\nBalrog wins!\n\n";
			break;
		}

	} while (1);
	Cyberdemon cyberdemon(10, 100);
	Elf elf(15, 75);
	cout << "\n\nFIGHTING MATCH\n";
	cout << "          " << elf.getSpecies() << " Strength : " << elf.getStr() << " Hit Point : " << elf.getHit();
	cout << "\nVS " << cyberdemon.getSpecies() << " Strength : " << cyberdemon.getStr() << " Hit Point : " << cyberdemon.getHit() << "\n\n\n";
	do
	{
		
		int elfHit = battleArena(elf, cyberdemon);
		if (elfHit <= 0) { elfHit = 0; }
		cyberdemon.setHit(elfHit);

		cout << '\n' << cyberdemon.getSpecies() << " hit points : " << cyberdemon.getHit() << "\n\n";
		
		int cyberdemonHit = battleArena(cyberdemon, elf);
		if (cyberdemonHit <= 0) { cyberdemonHit = 0; }
		elf.setHit(cyberdemonHit);
		cout << '\n' << elf.getSpecies() << " hit points : " << elf.getHit() << "\n\n";
		if (cyberdemon.getHit() <= 0 && elf.getHit() <= 0)
		{
			cout << "\n\nDraw!\n\n";
			break;
		}
		else if (cyberdemon.getHit() <= 0)
		{
			cout << "\n\nElf wins!\n\n";
			break;
		}
		else if (elf.getHit() <= 0)
		{
			cout << "\n\nCyberdemon wins!\n\n";
			break;
		}

	} while (1);
	return 0;
}