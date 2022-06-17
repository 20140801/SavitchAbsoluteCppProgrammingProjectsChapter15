#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int matrix[20][20]; //매트릭스
int antDigits = 0, doodleDigit = 0; //마리 수
void tempLocation(int, int, int, int&, int&); // 위치 선정
void show(); // 매트릭스 출력
void antKilled(); //클래스배열 땡겨오기
void doodleDead(); // 클래스 배열 땡겨오기

class Organism
{
public:
	int x = -1, y = -1, times = -1;
	virtual void move() = 0; //순수가상함수
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
}ants[400]; //ants 최대 400(클래스)
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
	for (i = 0; i < 4; i++) //상하좌우 케이스
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 0)
		{
			k++;
			//p[i] = 1;
		}
	}
	if (k == 0) { return; } //상하좌우 공백이 없으면 그냥 리턴
	if (k != 1) { k = rand() % k + 1; }

	for (i = 0; i < 4 && k>0; i++) //k가 0이되면 그 자리 t1, t2
	{
		tempLocation(x, y, i, t1, t2);
		if (matrix[t1][t2] == 0)
			k--;
	}

	matrix[x][y] = 0;
	x = t1;
	y = t2;
	matrix[x][y] = 2;


	if (times >= 3) //3번 되면 번식
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
	if (k == 0) { return; } //공간없으면 나가기
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
	ants[antDigits].birth(t1, t2); //antDigit번째 생성
}
class Doodlebug :public Organism
{
public:
	int steps = 0;
	void birth(int e, int f);
	void move();
	void breed();
	void starve() { matrix[x][y] = 0; }
}doodles[400];//doodles 최대 400(클래스)



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

				for (int i = 0; i < 4 && q>0; i++) //q가 0이되면 그 자리 t1, t2
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
				ants[j].starve(); //먹힌 것인데 그냥 가상함수를 위해 starve 씀
				antKilled();
			}
		}
		matrix[this->x][this->y] = 0;
		matrix[t1][t2] = 1;
		this->x = t1;
		this->y = t2;
	}

	if (steps >= 8) //8번 이상 살아남으면 번식
		this->breed();
	if (times <= 0) //3번 이상 못먹으면 죽음
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
	system("cls"); //화면초기화
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (matrix[i][j] == 0) //없음
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
	if (i == 0) //상하좌우
		t2--;
	else if (i == 1)
		t2++;
	else if (i == 2)
		t1--;
	else if (i == 3)
		t1++;
	if (t1 < 0 || t2 < 0 || t1>19 || t2>19) //벽너머로 가면 원래대로
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
					doodles[k] = doodles[k + 1]; //땡겨오기
			}
			else
				j++;
		}
	if (doodleDigit == 1)
		if (matrix[doodles[0].x][doodles[0].y] == 0)
			doodleDigit--;
}
//해보니 doodle이 학익진처럼 개미 전체를 둘러싸면 이기고 아니면 짐
int main()
{
	srand(time(NULL));
	int row, col, i = 0, j = 0, doodleNum = 401, antNum = 401;
	char command = 'v';
	//개미와 doodle 0이상 400미만 합도 0이상 400미만
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
	for (i = 0; i < doodleNum; i++) //초기 doodle 위치 선정
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
	for (i = 0; i < antNum; i++) //초기 ant 위치 선정
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
	command = cin.get(); //이렇게 해야 엔터 받음
	bool doodleExist = 0;
	bool antExist = 0;
	int times = 0; //턴 횟수
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
			"\n\nAll the creature's all dead! Game over\n"; //될 확률 없음
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
		if (command == 'q' || command == 'Q')//q나 Q 받으면 중지
		{
			break;
		}
		int dd = doodleDigit; //이렇게 하는 이유는 for문에서 digit이 바뀌므로 breed한 것도 움직여서
		for (i = 0; i < dd; i++) //doodle 전체 움직임(포식 포함)
			doodles[i].move();
		doodleDead();
		int ad = antDigits;
		for (i = 0; i < ad; i++) //개미 전체 움직임
			ants[i].move();
		show();
		doodleExist = 0;
		antExist = 0;
	}
	return 0;
}