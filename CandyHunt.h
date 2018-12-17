#pragma once
#include <iostream>
#include <ctime>
#include "Candies.h"
#include "Orange.h"
#include "Strawberry.h"
#include "Chocolate.h"
#include "Lemon.h"
#include "Player.h"
#include "Striped Strawberry.h"
#include "Striped Orange.h"
using namespace std;

template <typename T>
class CandyHunt : public Candies<T>,public Player<T>
{
protected:
	T moves;
	T maxmoves;
public:
	T *Xcomps;
	T *Ycomps;
	void Grid(T,T,T,T);
	bool endGame();
	T checkWinner(Player<T>,Player<T>);
	void SetMaxmoves(T);
	T GetMaxmoves();
	void UpdateMoves();
	T GetMoves();
	Candies<T>* Enlarge(Candies<T>&, Candies<T>&);
	virtual void Play(Player<T>&,Candies<T>**&,int,int&);
	T DiceRoll();
	CandyHunt();
	~CandyHunt();
	CandyHunt(CandyHunt<T>&);
	virtual void RandomFill(T,Candies<T>**,int);
};

template<typename T>
inline void CandyHunt<T>::Grid(T x1, T y1, T x2, T y2)
{
	if (Xcomps != nullptr && Ycomps != nullptr)
	{
		myRect(x1, y1, x2, y2, color1, color2, color3);
		int i = 0, x = 0;
		x += x1 + 2;
		while (i < maxmoves / 5)
		{
			Ycomps[i] = y1;
			int j = 0;
			while (j < (maxmoves / 4))
			{
				Xcomps[j] = x;
				myRect(x, y1, x + 100, y1 + 100, 0, 0, 0);
				x += 102;
				j++;
			}
			x = x1 + 2;
			y1 += 102;
			i++;
		}
	}
}

template<typename T>
inline bool CandyHunt<T>::endGame()
{
	if (moves == maxmoves)
		return true;
	return false;
}

template<typename T>
inline T CandyHunt<T>::checkWinner(Player<T> P1, Player<T> P2)
{
	if (P1.getPoints() > P2.getPoints())
		return 1;
	else if (P1.getPoints() < P2.getPoints())
		return 2;
	else
		return 0;
}

template<typename T>
inline void CandyHunt<T>::SetMaxmoves(T m)
{
	maxmoves = m;
	Xcomps = new T[maxmoves];
	Ycomps = new T[maxmoves];
}

template<typename T>
inline T CandyHunt<T>::GetMaxmoves()
{
	return maxmoves;
}

template<typename T>
inline void CandyHunt<T>::UpdateMoves()
{
	moves++;
}

template<typename T>
inline T CandyHunt<T>::GetMoves()
{
	return moves;
}

template<typename T>
inline Candies<T>* CandyHunt<T>::Enlarge(Candies<T>&a, Candies<T>&b)
{
	return nullptr;
}

template<typename T>
inline void CandyHunt<T>::Play(Player<T>& P, Candies<T>**& ptr, int index, int& size)
{
	if (ptr != nullptr && Xcomps != nullptr && Ycomps != nullptr)
	{
		cin.get();
		system("cls");
		T dice = DiceRoll();
		gotoxy(50,48);
		cout << " ** DICE ** : " << dice;
		RandomFill(dice, ptr, index);
		gotoxy(50, 50);
		cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
		gotoxy(50, 52);
		cout << "Number of Stripes:" << ptr[index]->GetStripes();
		P.setPoints(P.getPoints() + ptr[index]->GetScore());
		bool check = false;
		for (int i = 0; i < index; i++)
		{
			for (int j = i + 1; j < index; j++)
			{
				if (ptr[i] != nullptr && ptr[j] != nullptr)
				{
					if (ptr[index]->AreThree(*(ptr[i]), *(ptr[j])))
					{
						ptr[index] = ptr[index]->Enlarge(*(ptr[i]), *(ptr[j]));
						delete ptr[i];
						ptr[i] = nullptr;
						delete ptr[j];
						ptr[j] = nullptr;
						P.setPoints(P.getPoints() + ptr[index]->GetScore());
						myRect(Xcomps[index % 5], Ycomps[index / 5], Xcomps[(index % 5)] + 100, Ycomps[(index / 5)] + 100, 0, 0, 0);
						myRect(Xcomps[i % 5], Ycomps[i / 5], Xcomps[(i % 5)] + 100, Ycomps[(i / 5)] + 100, 0, 0, 0);
						myRect(Xcomps[j % 5], Ycomps[j / 5], Xcomps[(j % 5)] + 100, Ycomps[(j / 5)] + 100, 0, 0, 0);
						ptr[index]->Display(Xcomps[index % 5] + 20, Ycomps[index / 5] + 20);
						gotoxy(50, 50);
						cout << "Size of CURRENT Candy:" << ptr[index]->GetSize();
						gotoxy(50, 52);
						cout << "Number of Stripes:" << ptr[index]->GetStripes();
						check = true;
						break;
					}
				}
				if (check == true)
					break;
			}
			if (check == true)
				break;
		}
	}
}
template<typename T>
inline T CandyHunt<T>::DiceRoll()
{
	srand(time(NULL));
	T dice = (rand() % 6) + 1;
	return dice;
}

template<typename T>
inline CandyHunt<T>::CandyHunt()
{
	moves = 0;
	maxmoves = 20;
	color1 = 255;
	color2 = 0;
	color3 = 255;
	Xcomps = new T[maxmoves];
	Ycomps = new T[maxmoves];
}

template<typename T>
inline CandyHunt<T>::~CandyHunt()
{
	system("cls");
	moves = 0;
	maxmoves = 0;
	if (Xcomps != nullptr)
	{
		delete [] Xcomps;
		Xcomps = nullptr;
	}
	if (Ycomps!= nullptr)
	{
		delete[] Ycomps;
		Ycomps = nullptr;
	}
}

template<typename T>
inline CandyHunt<T>::CandyHunt(CandyHunt<T>& c)
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
inline void CandyHunt<T>::RandomFill(T dice,Candies<T>** ptr,int index)
{
	if (dice == 1)
	{
		ptr[index] = new Orange<T>;
		ptr[index]->Display(Xcomps[index % 5] + 20, Ycomps[index / 5] + 20);
	}
	else if (dice == 2)
	{
		ptr[index] = new Strawberry<T>;
		ptr[index]->Display(Xcomps[index % 5] + 20, Ycomps[index / 5] + 20);
	}
	else if (dice == 3)
	{
		ptr[index] = new Lemon<T>;
		ptr[index]->Display(Xcomps[index % 5] + 20, Ycomps[index / 5] + 20);
	}
	else if (dice == 4)
	{
		ptr[index] = new StripedStrawberry<T>;
		ptr[index]->Display(Xcomps[index % 5] + 20, Ycomps[index / 5] + 20);
	}
	else if (dice == 5)
	{
		ptr[index] = new Chocolate<T>;
		ptr[index]->Display(Xcomps[index % 5] + 20, Ycomps[index / 5] + 20);
	}
	else if (dice == 6)
	{
		ptr[index] = new StripedOrange<T>;
		ptr[index]->Display(Xcomps[index % 5] + 20, Ycomps[index / 5] + 20);
	}
}

