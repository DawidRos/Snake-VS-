// snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>


const int m = 10;
const int n = 10;

struct psnake
{
	int i;
	int j;
};

void screen(char tab[][n], const psnake * ss, const int & len, psnake & fly);
bool move(char tab[][n], psnake * ss, char & dir, int & len, psnake & fly);
void slide(psnake *ss, int len);
void slideAdd(psnake *ss, int & len);
void score(int len);


int main() {

	srand(time(0));
	char tab[m][n];
	char * pt = &tab[0][0];
	char snake[100];
	psnake waz[100] = { { 5,5 },{ 5,4 },{ 5,3 } };
	psnake fly = { 7,7 };
	char dir = 'd';
	char dirtemp = 'd';
	int len = 3;
	clock_t delay = 0.2*CLOCKS_PER_SEC;
	while (dir != 'q')
	{
		screen(tab, waz, len, fly);
		clock_t start = clock();
		while (clock() - start < delay) { ; }
		if (_kbhit())
			dir = _getch();
		else
			dir = _putch(dir);
		if (!move(tab, waz, dir, len, fly)) {
			score(len);
			break;
		}
		dir = _putch(dir);
	}
	std::cin.get();
	std::cin.get();
	return 0;
}

void screen(char tab[][n], const psnake * ss, const int & len, psnake & fly)
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
				tab[i][j] = -37;
			else
				tab[i][j] = ' ';
		}
	}
	for (int k = 0; k<len; k++)
		tab[ss[k].i][ss[k].j] = 'o';
	if (fly.i == '\0')
	{
		do {
			fly.i = (rand() * (m - 2) / RAND_MAX) + 1;
			fly.j = (rand() * (n - 2) / RAND_MAX) + 1;
			if (tab[fly.i][fly.j] == 'o')
				continue;
		} while (tab[fly.i][fly.j] == 'o');
	}
	tab[fly.i][fly.j] = 'x';

	system("CLS");

	for (int i = 0; i<m; i++)
	{
		std::cout << "\t\t\t"<< (char)-37;
		if (i != 0 && i != m - 1) {
			for (int j = 0; j < n; j++)
				std::cout << tab[i][j] << " ";
			std::cout <<"\b"<< (char)-37 << std::endl;
		}
		else 
		{
			for (int j = 0; j < n; j++)
				std::cout << tab[i][j] << (char)-37;
			std::cout << std::endl;
		}
	}
}

bool move(char tab[][n], psnake * ss, char & dir, int & len, psnake &fly)
{
	switch (dir)
	{
	case 'd':
		if (tab[ss->i][ss->j + 1] == 'o' || tab[ss->i][ss->j + 1] == -37)
			return false;
		else if (tab[ss->i][ss->j + 1] == 'x')
		{
			slideAdd(ss, len);
			ss[0].j++;
			fly.i = '\0';
			return true;
		}
		else
		{
			slide(ss, len);
			ss[0].j++;
			return true;
		}
	case 'a':
		if (tab[ss->i][ss->j - 1] == 'o' || tab[ss->i][ss->j - 1] == -37)
			return false;
		else if (tab[ss->i][ss->j - 1] == 'x')
		{
			slideAdd(ss, len);
			ss[0].j--;
			fly.i = '\0';
			return true;
		}
		else
		{
			slide(ss, len);
			ss[0].j--;
			return true;
		}
	case 'w':
		if (tab[ss->i - 1][ss->j] == 'o' || tab[ss->i - 1][ss->j] == -37)
			return false;
		else if (tab[ss->i - 1][ss->j] == 'x')
		{
			slideAdd(ss, len);
			ss[0].i--;
			fly.i = '\0';
			return true;
		}
		else
		{
			slide(ss, len);
			ss[0].i--;
			return true;
		}
	case 's':
		if (tab[ss->i + 1][ss->j] == 'o' || tab[ss->i + 1][ss->j] == -37)
			return false;
		else if (tab[ss->i + 1][ss->j] == 'x')
		{
			slideAdd(ss, len);
			ss[0].i++;
			fly.i = '\0';
			return true;
		}
		else
		{
			slide(ss, len);
			ss[0].i++;
			return true;
		}
	}
}

void slide(psnake *ss, int len)
{
	for (int i = len - 1; i>0; i--)
		ss[i] = ss[i - 1];
}

void slideAdd(psnake *ss, int & len)
{
	len++;
	for (int i = len - 1; i>0; i--)
		ss[i] = ss[i - 1];
}

void score(int len)
{
	std::cout << "\n\t\t\t    YOUR SCORE: " << len - 3;
	if (len == 3)
		std::cout << "\n\t\t\t\a\a\a     <<<LOSER>>>\n";
	else if (len>3 && len<8)
		std::cout << "\n\t\t\t    <<<BEGGINER>>>\n";
	else if(len>=8 && len<18)
		std::cout << "\n\t\t\t   <<<GOOD GAME>>>\n";
	else if (len >= 18 && len<28)
		std::cout << "\n\t\t\t  <<<LIKE A BOSS>>>\n";
	else if (len >= 28 && len<58)
		std::cout << "\n\t\t\t  <<<LIKE A BOSS>>>\n";
	else if (len >= 58 && len<99)
		std::cout << "\n\t\t\t    <<<RAMPAGE>>>\n";
	else
		std::cout << "\n\t\t     <<<SYSTEM DESTROYED ! ! !>>>\n";
}