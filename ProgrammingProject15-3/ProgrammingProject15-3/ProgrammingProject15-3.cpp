#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int matrix[20][20]; //��Ʈ����
int antDigits = 0, doodleDigit = 0; //���� ��
void tempLocation(int, int, int, int&, int&); // ��ġ ����
void show(); // ��Ʈ���� ���
void antKilled(); //Ŭ�����迭 ���ܿ���
void doodleDead(); // Ŭ���� �迭 ���ܿ���

class Organism
{
public:
	int x = -1, y = -1, times = -1;
	virtual void move() = 0; //���������Լ�
	virtual void breed() = 0;
	virtual void starve() = 0;
};
class Ant :public Organism
{
public:
	void birth(const int, const int);
	void move();
	void breed();
	void starve() { matrix[x][y] = 0; }
}ants[400]; //ants �ִ� 400(Ŭ����)
void Ant::birth(const int xi, const int yi)
{
	this->x = xi;
	this->y = yi;
	this->times = 0;
	matrix[xi][yi] = 2;
	antDigits++;
}
void Ant::move()
{
	int k = 0, t1, t2, i;
	times++;
	//bool p[4] = { 0,0,0,0 };
	for (i = 0; i < 4; i++) //�����¿� ���̽�
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 0)
		{
			k++;
			//p[i] = 1;
		}
	}
	if (k == 0) { return; } //�����¿� ������ ������ �׳� ����
	if (k != 1) { k = rand() % k + 1; }

	for (i = 0; i < 4 && k>0; i++) //k�� 0�̵Ǹ� �� �ڸ� t1, t2
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 0)
			k--;
	}

	matrix[x][y] = 0;
	x = t1;
	y = t2;
	matrix[x][y] = 2;


	if (times >= 3) //3�� �Ǹ� ����
	{
		this->breed();
		times = 0;
	}
}
void Ant::breed()
{
	int i, k = 0, t1, t2;
	for (i = 0; i < 4; i++)
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 0)
			k++;
	}
	if (k == 0) { return; } //���������� ������
	if (k != 1)
	{
		k = (rand() % k + 1);
	}
	for (i = 0; i < 4 && k>0; i++)
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 0)
			k--;
	}
	ants[antDigits].birth(t1, t2); //antDigit��° ����
}
class Doodlebug :public Organism
{
public:
	int steps = 0;
	void birth(int e, int f);
	void move();
	void breed();
	void starve() { matrix[x][y] = 0; }
}doodles[400];//doodles �ִ� 400(Ŭ����)



void Doodlebug::birth(int e, int f)
{
	x = e;
	y = f;
	times = 3;
	steps = 0;
	matrix[e][f] = 1;
	doodleDigit++;
}
void Doodlebug::move()
{
	int k = 0, q = 0, t1, t2; //t1,t2 == templocation
	steps++;

	for (int i = 0; i < 4; i++)
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 2)
			k++;
	}

	if (k == 0)
	{
		times--;
		for (int ss = 0; ss < 1; ss++)
		{
			if (times > 0)
			{
				for (int i = 0; i < 4; i++)
				{
					tempLocation(x, y, i, t1, t2);
					if (matrix[t1][t2] == 0)
						q++;
				}
				if (q == 0) { break; }
				else if (q != 1) { q = rand() % q + 1; }

				for (int i = 0; i < 4 && q>0; i++) //q�� 0�̵Ǹ� �� �ڸ� t1, t2
				{
					tempLocation(x, y, i, t1, t2);
					if (matrix[t1][t2] == 0)
						q--;
				}

				matrix[x][y] = 0;
				matrix[t1][t2] = 1;
				x = t1;
				y = t2;
			}
		}
	}
	else
	{
		if (k != 1)
			k = (rand() % k + 1);
		for (int i = 0; i < 4 && k>0; i++)
		{
			tempLocation(x, y, i, t1, t2);
			if (matrix[t1][t2] == 2)
				k--;
		}
		times = 3;

		for (int j = 0; j < antDigits; j++)
		{
			if ((ants[j].x == t1) && (ants[j].y == t2))
			{
				ants[j].starve(); //���� ���ε� �׳� �����Լ��� ���� starve ��
				antKilled();
			}
		}
		matrix[this->x][this->y] = 0;
		matrix[t1][t2] = 1;
		this->x = t1;
		this->y = t2;
	}

	if (steps >= 8) //8�� �̻� ��Ƴ����� ����
		this->breed();
	if (times <= 0) //3�� �̻� �������� ����
		this->starve();
}

void Doodlebug::breed()
{
	int i, k = 0, t1, t2;
	for (i = 0; i < 4; i++)
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 0)
			k++;
	}
	if (k > 0)
	{
		if (k != 1) {
			k = (rand() % k + 1);
		}
		for (i = 0; i < 4 && k>0; i++)
		{
			tempLocation(x, y, i, t1, t2);
			if (matrix[t1][t2] == 0)
				k--;
		}
		doodles[doodleDigit].birth(t1, t2);
	}
}

void show()
{
	int i, j;
	char c[3] = "";
	system("cls"); //ȭ���ʱ�ȭ
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (matrix[i][j] == 0) //����
				strcpy(c, "- ");
			else if (matrix[i][j] == 1) //doodlebug
				strcpy(c, "X ");
			else if (matrix[i][j] == 2) //ant
				strcpy(c, "O ");
			cout << c;
		}
		cout << "\n";
	}
}

void tempLocation(int x, int y, int i, int& t1, int& t2)
{
	t1 = x;
	t2 = y;
	if (i == 0) //�����¿�
		t2--;
	else if (i == 1)
		t2++;
	else if (i == 2)
		t1--;
	else if (i == 3)
		t1++;
	if (t1 < 0 || t2 < 0 || t1>19 || t2>19) //���ʸӷ� ���� �������
	{
		t1 = x;
		t2 = y;
	}
}

void antKilled()
{
	int j, k;
	if (antDigits != 1)
		for (j = 0; j < antDigits;)
		{
			if (matrix[ants[j].x][ants[j].y] == 0)
			{
				antDigits--;
				for (k = j; k < antDigits; k++)
					ants[k] = ants[k + 1];
			}
			else
				j++;
		}
	if (antDigits == 1)
		if (matrix[ants[0].x][ants[0].y] == 0)
		{
			antDigits--;
		}
}

void doodleDead()
{
	int j, k;
	if (doodleDigit != 1)
		for (j = 0; j < doodleDigit;)
		{
			if (matrix[doodles[j].x][doodles[j].y] == 0)
			{
				doodleDigit--;
				for (k = j; k < doodleDigit; k++)
					doodles[k] = doodles[k + 1]; //���ܿ���
			}
			else
				j++;
		}
	if (doodleDigit == 1)
		if (matrix[doodles[0].x][doodles[0].y] == 0)
			doodleDigit--;
}
//�غ��� doodle�� ������ó�� ���� ��ü�� �ѷ��θ� �̱�� �ƴϸ� ��
int main()
{
	srand(time(NULL));
	int row, col, i = 0, j = 0, doodleNum = 401, antNum = 401;
	char command = 'v';
	//���̿� doodle 0�̻� 400�̸� �յ� 0�̻� 400�̸�
	while ((doodleNum > 400 || doodleNum < 0) || (antNum > 400 || antNum < 0) || ((doodleNum + antNum) > 400 || (doodleNum + antNum) < 0))
	{
		system("cls");
		cout << "ENTER how many DODDLEBUGS :";
		cin >> doodleNum;
		cout << "ENTER how many ANTS :";
		cin >> antNum;
	}
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++)
		{
			matrix[i][j] = 0;
		}
	}
	for (i = 0; i < doodleNum; i++) //�ʱ� doodle ��ġ ����
	{
		do {
			row = rand() % 20;
			col = rand() % 20;
			if (matrix[row][col] == 0)
			{
				break;
			}
		} while (1);
		doodles[i].birth(row, col);
	}
	for (i = 0; i < antNum; i++) //�ʱ� ant ��ġ ����
	{
		do {
			row = rand() % 20;
			col = rand() % 20;
			if (matrix[row][col] == 0)
			{
				break;
			}
			else { continue; }
		} while (1);
		ants[i].birth(row, col);
	}
	show();
	command = cin.get(); //�̷��� �ؾ� ���� ����
	bool doodleExist = 0;
	bool antExist = 0;
	int times = 0; //�� Ƚ��
	while (1)
	{
		times++;
		for (int ix = 0; ix < 20; ix++)
		{
			for (int jx = 0; jx < 20; jx++)
			{
				if (matrix[ix][jx] == 1) {
					doodleExist = 1;
				}
				else if (matrix[ix][jx] == 2) {
					antExist = 1;
				}
			}
			if (doodleExist && antExist)
			{
				break;
			}
		}
		cout << times << "Turn\n\n";
		if (!doodleExist && !antExist) {
			"\n\nAll the creature's all dead! Game over\n"; //�� Ȯ�� ����
			break;
		}
		else if (!doodleExist) {
			cout << "\n\nAnts win! Doodlebug's all dead! Game over!\n";
			break;
		}
		else if (!antExist) {
			cout << "\n\nDoodlebugs win! Ant's all dead! Game over!\n";
			break;
		}
		cout << "Press ENTER to refresh (Exit:q or Q)";
		command = cin.get();
		if (command == 'q' || command == 'Q')//q�� Q ������ ����
		{
			break;
		}
		int dd = doodleDigit; //�̷��� �ϴ� ������ for������ digit�� �ٲ�Ƿ� breed�� �͵� ��������
		for (i = 0; i < dd; i++) //doodle ��ü ������(���� ����)
			doodles[i].move();
		doodleDead();
		int ad = antDigits;
		for (i = 0; i < ad; i++) //���� ��ü ������
			ants[i].move();
		show();
		doodleExist = 0;
		antExist = 0;
	}
	return 0;
}