#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include "Candies.h"
#include "CandyHunt.h"
#include "Player.h"
using namespace std;

template <typename T>
class CandyCrush : public CandyHunt<T>
{
	Candies<int> **ptr;
	T gridx;
	T gridy;
public:
	Candies<T>* Allocate(Candies<T>*, Candies<T>*&);
	void Play(Player<T>&, Candies<T>**&, int, int&);
	Candies<T>* Enlarge(Candies<T>&, Candies<T>&);
	void Grid();
	CandyCrush();
	~CandyCrush();
	CandyCrush(CandyCrush<T>&);
	void swap(Player<T>&,T&);
	void roam(Player<T>&,T&);
	void StartGame();
	void VariableInput(int);
	T IsEmpty();
	void RandomFill(T, Candies<T>**, int);
	void CheckAllSides(Player<T>&);
	void CheckCrissCross(Player<T>&,T,bool&);
};

template<typename T>
inline Candies<T>* CandyCrush<T>::Allocate(Candies<T>*p1, Candies<T>*&p2)
{
	if (p1 != nullptr && p2 != nullptr)
	{
		/*dice 1 for orange, 2 for plain strawberry, 3 for lemon, 4 for Stripped strawberry, 5 for Chocolate and 6 for Striped Orange candy*/
		Candies<T>*Result = nullptr;
		if (p2->getDice() == 1)
		{
			Result = new Orange<T>;
			Result->SetScore(p2->GetScore());
			Result->SetSize(p2->GetSize());
			Result->SetStripes(p2->GetStripes());
		}
		else if (p2->getDice() == 2)
		{
			Result = new Strawberry<T>;
			Result->SetScore(p2->GetScore());
			Result->SetSize(p2->GetSize());
			Result->SetStripes(p2->GetStripes());
		}
		else if (p2->getDice() == 3)
		{
			Result = new Lemon<T>;
			Result->SetScore(p2->GetScore());
			Result->SetSize(p2->GetSize());
			Result->SetStripes(p2->GetStripes());
		}
		else if (p2->getDice() == 4)
		{
			Result = new StripedStrawberry<T>;
			Result->SetScore(p2->GetScore());
			Result->SetSize(p2->GetSize());
			Result->SetStripes(p2->GetStripes());
		}
		else if (p2->getDice() == 5)
		{
			Result = new Chocolate<T>;
			Result->SetScore(p2->GetScore());
			Result->SetSize(p2->GetSize());
			Result->SetStripes(p2->GetStripes());
		}
		else if (p2->getDice() == 6)
		{
			Result = new StripedOrange<T>;
			Result->SetScore(p2->GetScore());
			Result->SetSize(p2->GetSize());
			Result->SetStripes(p2->GetStripes());
		}

		if (p1->getDice() == 1)
		{
			p2 = new Orange<T>;
			p2->SetScore(p1->GetScore());
			p2->SetSize(p1->GetSize());
			p2->SetStripes(p1->GetStripes());
		}
		else if (p1->getDice() == 2)
		{
			p2 = new Strawberry<T>;
			p2->SetScore(p1->GetScore());
			p2->SetSize(p1->GetSize());
			p2->SetStripes(p1->GetStripes());
		}
		else if (p1->getDice() == 3)
		{
			p2 = new Lemon<T>;
			p2->SetScore(p1->GetScore());
			p2->SetSize(p1->GetSize());
			p2->SetStripes(p1->GetStripes());
		}
		else if (p1->getDice() == 4)
		{
			p2 = new StripedStrawberry<T>;
			p2->SetScore(p1->GetScore());
			p2->SetSize(p1->GetSize());
			p2->SetStripes(p1->GetStripes());
		}
		else if (p1->getDice() == 5)
		{
			p2 = new Chocolate<T>;
			p2->SetScore(p1->GetScore());
			p2->SetSize(p1->GetSize());
			p2->SetStripes(p1->GetStripes());
		}
		else if (p1->getDice() == 6)
		{
			p2 = new StripedOrange<T>;
			p2->SetScore(p1->GetScore());
			p2->SetSize(p1->GetSize());
			p2->SetStripes(p1->GetStripes());
		}
		return Result;
	}
}

template<typename T>
inline void CandyCrush<T>::Play(Player<T>&P, Candies<T>**&c, int index, int &size)
{
	while (GetMoves() <= GetMaxmoves())
	{
		roam(P,index);
	}
	if (score > 500)
	{
		system("cls");
		gotoxy(50, 50);
		cout << "WINNER !!" << endl;
	}
}

template<typename T>
inline Candies<T>* CandyCrush<T>::Enlarge(Candies<T>&, Candies<T>&)
{
	return nullptr;
}

template<typename T>
inline void CandyCrush<T>::Grid()
{
	cout << "Enter number of columns : ";
	cin >> gridx;
	cout << "Enter number of rows : ";
	cin >> gridy;
	if (Xcomps != nullptr && Ycomps != nullptr && ptr!=nullptr)
	{
		delete[]Xcomps;
		delete[]Ycomps;
		delete[]ptr;
	}
	Xcomps = new T[gridx*gridy];
	Ycomps = new T[gridx*gridy];
	ptr = new Candies<T>*[gridx*gridy];
	if (gridx > 0 && gridy > 0)
	{
		myRect(0, 0, gridx * 103, gridy * 103, color1, color2, color3);
		T i = 0, x = 0,j=0,l=0,y=0;
		x  = 2;
		y  = 2;
		while (l < gridy)
		{
			int k = 0;
			while (k < gridx)
			{
				Ycomps[i] = y;
				Xcomps[j] = x;
				myRect(x, y, x + 100, y + 100, 0, 0, 0);
				x += 102;
				j++;
				i++;
				k++;
			}
			x = 2;
			y += 102;
			l++;
		}
	}
}

template<typename T>
inline CandyCrush<T>::CandyCrush()
{
	moves = 0;
	maxmoves = 16;
	color1 = 255;
	color2 = 0;
	color3 = 255;
	gridx = 4;
	gridy = 4;
	Xcomps = new T[gridx*gridy];
	Ycomps = new T[gridx*gridy];
	ptr = new Candies<T>*[gridx*gridy];
}

template<typename T>
inline CandyCrush<T>::~CandyCrush()
{
	system("cls");
	moves = 0;
	maxmoves = 0;
	if (Xcomps != nullptr)
	{
		delete[] Xcomps;
		Xcomps = nullptr;
	}
	if (Ycomps != nullptr)
	{
		delete[] Ycomps;
		Ycomps = nullptr;
	}
}

template<typename T>
inline CandyCrush<T>::CandyCrush(CandyCrush<T>&c)
{
	moves = c.moves;
	maxmoves = c.maxmoves;
	color1 = c.color1;
	color2 = c.color2;
	color3 = c.color3;
	if (c.Xcomps != nullptr && c.Ycomps != nullptr)
	{
		Xcomps = new T[maxmoves];
		for (int i = 0; i < maxmoves; i++)
			Xcomps[i] = c.Xcomps;
		Ycomps = new T[maxmoves];
		for (int i = 0; i < maxmoves; i++)
			Ycomps[i] = c.Ycomps;
	}
	else
	{
		Xcomps = nullptr;
		Ycomps = nullptr;
	}
}

template<typename T>
inline void CandyCrush<T>::swap(Player<T>&P,T& index)
{
	bool check = false;
	Sleep(200);
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (index - 1 >= 0)
		{
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myRect(Xcomps[index-1], Ycomps[index-1], Xcomps[index-1] + 100, Ycomps[index-1] + 100, 0, 0, 0);
			ptr[index] = Allocate(ptr[index], ptr[index - 1]);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			index--;
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
			Sleep(200);
			CheckCrissCross(P,index,check);
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
			CheckAllSides(P);
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (index + 1 < gridx*gridy)
		{
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myRect(Xcomps[index + 1], Ycomps[index + 1], Xcomps[index + 1] + 100, Ycomps[index + 1] + 100, 0, 0, 0);
			ptr[index] = Allocate(ptr[index], ptr[index + 1]);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			index++;
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
			Sleep(200);
			CheckCrissCross(P,index,check);
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
			CheckAllSides(P);
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (index - gridy >= 0)
		{
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myRect(Xcomps[index - gridy], Ycomps[index - gridy], Xcomps[index - gridy] + 100, Ycomps[index - gridy] + 100, 0, 0, 0);
			ptr[index] = Allocate(ptr[index], ptr[index - gridy]);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			index -= gridy;
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
			Sleep(200);
			CheckCrissCross(P,index,check);
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
			CheckAllSides(P);
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (index + gridy < gridx*gridy)
		{
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myRect(Xcomps[index + gridy], Ycomps[index + gridy], Xcomps[index + gridy] + 100, Ycomps[index + gridy] + 100, 0, 0, 0);
			ptr[index] = Allocate(ptr[index], ptr[index + gridy]);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			index += gridy;
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
			Sleep(200);
			CheckCrissCross(P,index,check);
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
			CheckAllSides(P);
			myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
			myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
			myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
			ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.DisplayScore(50, 54);
		}
	}
}

template<typename T>
inline void CandyCrush<T>::roam(Player<T>&P,T& index)
{
	if (Xcomps != nullptr && Ycomps != nullptr && ptr != nullptr)
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (index - 1 >= 0)
			{
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 0,0,0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				index--;
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
				myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				system("cls");
				gotoxy(50, 50);
				cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
				gotoxy(50, 52);
				cout << "Number of Stripes:" << ptr[index]->GetStripes();
				P.DisplayScore(50, 54);
				Sleep(200);
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (index + 1 < gridx*gridy)
			{
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 0, 0, 0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				index++;
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
				myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				system("cls");
				gotoxy(50, 50);
				cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
				gotoxy(50, 52);
				cout << "Number of Stripes:" << ptr[index]->GetStripes();
				P.DisplayScore(50, 54);
				Sleep(200);
			}
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			if (index - gridy >= 0)
			{
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 0, 0, 0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				index -= gridy;
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
				myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				system("cls");
				gotoxy(50, 50);
				cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
				gotoxy(50, 52);
				cout << "Number of Stripes:" << ptr[index]->GetStripes();
				P.DisplayScore(50, 54);
				Sleep(200);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (index + gridy < gridx*gridy)
			{
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 0, 0, 0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				index += gridy;
				myEllipse(Xcomps[index] + 10, Ycomps[index] + 10, Xcomps[index] + 80, Ycomps[index] + 80, 255, 255, 255);
				myEllipse(Xcomps[index] + 12, Ycomps[index] + 12, Xcomps[index] + 77, Ycomps[index] + 77, 0, 0, 0);
				ptr[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
				system("cls");
				gotoxy(50, 50);
				cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
				gotoxy(50, 52);
				cout << "Number of Stripes:" << ptr[index]->GetStripes();
				P.DisplayScore(50, 54);
				Sleep(200);
			}
		}
		else if (GetAsyncKeyState(VK_CONTROL))
		{
			cout << "GAME PAUSED! " << "PRESS 1 TO CONTINUE : " << endl;
			Sleep(200);
			ifstream fin;
			fin.open("savegame.txt");
			fin >> index;
			char c='\0';
			cin >> c;
			while (c!='1')
			{
				cin >> c;
			}
			fin >> index;
			fin.close();
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			swap(P,index);
			UpdateMoves();
		}
	}
}


template<typename T>
inline void CandyCrush<T>::StartGame()
{
	for (int i = 0; i < gridx*gridy; i++)
	{
		srand(time(NULL));
		T dice = DiceRoll();
		Sleep(500);
		RandomFill(dice, ptr, i);
	}
}

template<typename T>
inline void CandyCrush<T>::VariableInput(int index)
{
	srand(time(NULL));
	T dice = DiceRoll();
	Sleep(100);
	RandomFill(dice, ptr, index);
}

template<typename T>
inline T CandyCrush<T>::IsEmpty()
{
	for (int i = 0; i < gridx*gridy; i++)
	{
		if (ptr[i] == nullptr)
			return i;
	}
	return -1;
}

template<typename T>
inline void CandyCrush<T>::RandomFill(T dice, Candies<T>** p, int index)
{
	if (dice == 1)
	{
		p[index] = new Orange<T>;
		myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
		p[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
	}
	else if (dice == 2)
	{
		p[index] = new Strawberry<T>;
		myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
		p[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
	}
	else if (dice == 3)
	{
		p[index] = new Lemon<T>;
		myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
		p[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
	}
	else if (dice == 4)
	{
		p[index] = new StripedStrawberry<T>;
		myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
		p[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
	}
	else if (dice == 5)
	{
		p[index] = new Chocolate<T>;
		myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
		p[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
	}
	else if (dice == 6)
	{
		p[index] = new StripedOrange<T>;
		myRect(Xcomps[index], Ycomps[index], Xcomps[index] + 100, Ycomps[index] + 100, 0, 0, 0);
		p[index]->Display(Xcomps[index] + 20, Ycomps[index] + 20);
	}
}

template<typename T>
inline void CandyCrush<T>::CheckAllSides(Player<T>&P)
{
	bool check = true;
	for (int i = 0; i < gridx*gridy; i++)
	{
		CheckCrissCross(P,i,check);
			myRect(Xcomps[i], Ycomps[i], Xcomps[i] + 100, Ycomps[i] + 100, 0, 0, 0);
			ptr[i]->Display(Xcomps[i] + 20, Ycomps[i] + 20);
		Sleep(10);
	}
}

template<typename T>
inline void CandyCrush<T>::CheckCrissCross(Player<T>&P,T index,bool& check)
{
	if (index - gridy >= 0 && index - (2 * gridy) >= 0)
	{
		if (ptr[index]->AreThree(*(ptr[index - gridy]), *(ptr[index - (2 * gridy)])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index - gridy]), *(ptr[index - (2 * gridy)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index - gridy];
			ptr[index - gridy] = nullptr;
			delete ptr[index - (2 * gridy)];
			ptr[index - (2 * gridy)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index - 1) % gridx != gridx - 1) && ((index + 1) % gridx != 0) && (index - 1) >= 0 && (index + 1) <= gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index - 1]), *(ptr[index + 1])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index - 1]), *(ptr[index + 1]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index - 1];
			ptr[index - 1] = nullptr;
			delete ptr[index + 1];
			ptr[index + 1] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index - 1) % gridx != gridx - 1) && ((index - 2) % gridx != gridx - 1) && (index - 1) >= 0 && (index - 2) >= 0)
	{
		if (ptr[index]->AreThree(*(ptr[index - 1]), *(ptr[index - 2])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index - 1]), *(ptr[index - 2]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index - 1];
			ptr[index - 1] = nullptr;
			delete ptr[index - 2];
			ptr[index - 2] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index + 1) % gridx != 0) && ((index + 2) % gridx != 0) && (index + 1) < gridx*gridy && (index + 2) < gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index + 1]), *(ptr[index + 2])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index + 1]), *(ptr[index + 2]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index + 1];
			ptr[index + 1] = nullptr;
			delete ptr[index + 2];
			ptr[index + 2] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (index + gridy < gridx*gridy && index + 2 * gridy < gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index + gridy]), *(ptr[index + 2 * gridy])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index + gridy]), *(ptr[index + (2 * gridy)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index + gridy];
			ptr[index + gridy] = nullptr;
			delete ptr[index + (2 * gridy)];
			ptr[index + (2 * gridy)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}	
	if (index - gridy >= 0 && index + gridy < gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index - gridy]), *(ptr[index + gridy])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index - gridy]), *(ptr[index + gridy]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index - gridy];
			ptr[index - gridy] = nullptr;
			delete ptr[index + gridy];
			ptr[index + gridy] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index % (gridx) !=gridx-1  && index - (gridx-1) % gridx!=0 ) && (index % gridx != 0 && index + (gridx - 1) % (gridx-1) != 0)) && index - (gridx - 1) >= 0 && index + (gridx - 1) < gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index - (gridx - 1)]), *(ptr[index + (gridx - 1)])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index - (gridx - 1)]), *(ptr[index + (gridx - 1)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index + (gridx - 1)];
			ptr[index + (gridx - 1)] = nullptr;
			delete ptr[index - (gridx - 1)];
			ptr[index - (gridx - 1)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index % (gridx) != 0 && index - (gridx + 1) % gridx != gridx-1) && (index % gridx != gridx-1 && index + (gridx + 1) % gridx != 0)) && index - (gridx + 1) >= 0 && index + (gridx + 1) < gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index + (gridx + 1)]), *ptr[index - (gridx + 1)]))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index + (gridx + 1)]), *(ptr[index - (gridx + 1)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index + (gridx + 1)];
			ptr[index + (gridx + 1)] = nullptr;
			delete ptr[index - (gridx + 1)];
			ptr[index - (gridx + 1)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index % (gridx) != gridx - 1 && index - (gridx - 1) % gridx != 0) && (index - (gridx-1) % gridx != gridx-1 && (index - 2*(gridx - 1)) % gridx != 0)) && index - (gridx - 1) >= 0 && index - 2 * (gridx - 1) >= 0)
    {
		if (ptr[index]->AreThree(*(ptr[index - (gridx - 1)]), *(ptr[index - 2 * (gridx - 1)])))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index - (gridx - 1)]), *(ptr[index - 2 * (gridx - 1)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index - (gridx - 1)];
			ptr[index - (gridx - 1)] = nullptr;
			delete ptr[index - 2 * (gridx - 1)];
			ptr[index - 2 * (gridx - 1)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}	
	if((((index - (gridx+1)) % gridx != gridx-1 && index % gridx != 0) && ((index - (gridx + 1)) % gridx != 0 && (index - 2 * (gridx + 1)) % gridx != gridx-1)) && index - (gridx + 1) >= 0 && index - 2 * (gridx + 1) >= 0)
	{
		if (ptr[index]->AreThree(*(ptr[index - (gridx + 1)]), *ptr[index - 2 * (gridx + 1)]))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index - (gridx + 1)]), *(ptr[index - 2 * (gridx + 1)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index - (gridx + 1)];
			ptr[index - (gridx + 1)] = nullptr;
			delete ptr[index - 2 * (gridx + 1)];
			ptr[index - 2 * (gridx + 1)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index % gridx != 0 && index + (gridx - 1) % gridx != gridx-1) && (index + (gridx - 1) % gridx != 0 && (index + 2 * (gridx - 1)) % gridx != gridx-1)) && index + (gridx - 1) < gridx*gridy && index + 2 * (gridx - 1) < gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index + (gridx - 1)]), *ptr[index + 2 * (gridx - 1)]))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index + (gridx - 1)]), *(ptr[index + 2 * (gridx - 1)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index + (gridx - 1)];
			ptr[index + (gridx - 1)] = nullptr;
			delete ptr[index + 2 * (gridx - 1)];
			ptr[index + 2 * (gridx - 1)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
	if (((index % gridx != gridx-1 && index + (gridx + 1) % gridx != 0) && (index + (gridx + 1) % gridx != gridx - 1 && (index + 2 * (gridx + 1)) % gridx != 0)) && index + (gridx - 1) < gridx*gridy && index + 2 * (gridx - 1) < gridx*gridy)
	{
		if (ptr[index]->AreThree(*(ptr[index + (gridx + 1)]), *ptr[index + 2 * (gridx + 1)]))
		{
			
			check = true;
			ptr[index] = ptr[index]->Enlarge(*(ptr[index + (gridx + 1)]), *(ptr[index + 2 * (gridx + 1)]));
			system("cls");
			gotoxy(50, 50);
			cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
			gotoxy(50, 52);
			cout << "Number of Stripes:" << ptr[index]->GetStripes();
			P.setPoints(P.getPoints() + ptr[index]->GetScore());
			P.DisplayScore(50, 54);
			delete ptr[index + (gridx + 1)];
			ptr[index + (gridx + 1)] = nullptr;
			delete ptr[index + 2 * (gridx + 1)];
			ptr[index + 2 * (gridx + 1)] = nullptr;
			T maybe = IsEmpty();
			while (maybe != -1)
			{
				VariableInput(maybe);
				maybe = IsEmpty();
			}
		}
	}
}


