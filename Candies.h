#pragma once
#include <help.h>
#include <conio.h>
#include <ctime>
#include <iostream>
using namespace std;

template <typename T>
class Candies
{
protected:
	T *stripes;
	T score;
	T size;
	T dice;
	int color1;
	int color2;
	int color3;
public:
	T getDice();
	void SetStripes(T);
	T GetStripes();
	void SetScore(T);
	void SetSize(T);
	T GetScore();
	virtual bool AreThree(Candies<T>&, Candies<T>&);
	virtual void Display(T, T);
	virtual Candies<T>* Enlarge(Candies<T>&,Candies<T>&) = 0;
	T GetSize();
	Candies();
	Candies<T>(Candies<T>&);
	virtual ~Candies();
};

template<typename T>
inline T Candies<T>::getDice()
{
	return dice;
}

template<typename T>
inline void Candies<T>::SetStripes(T s)
{
	stripes = new T;
	*stripes = s;
}

template<typename T>
inline T Candies<T>::GetStripes()
{
	if (stripes != nullptr)
		return *stripes;
	else
		return 0;
}

template<typename T>
inline void Candies<T>::SetScore(T a)
{
	score = a;
}

template<typename T>
inline void Candies<T>::SetSize(T a)
{
	size = a;
}

template<typename T>
inline T Candies<T>::GetScore()
{
	return score;
}

template<typename T>
inline bool Candies<T>::AreThree(Candies<T> &c1, Candies<T> &c2)
{
   	if (dice == c1.dice && c1.dice == c2.dice)
		return true;
	return false;
}

template<typename T>
inline void Candies<T>::Display(T x1, T y1)
{
	myEllipse(x1, y1, x1 + 50, y1 + 50,color1,color2,color3);
}

template<typename T>
inline T Candies<T>::GetSize()
{
	return size;
}

template<typename T>
inline Candies<T>::Candies()
{
	dice = NULL;
	score = NULL;
	size = NULL;
	stripes = nullptr;
	color1 = 0;
	color2 = 0;
	color3 = 0;
}

template <typename T>
inline Candies<T> ::~Candies()
{
	dice = NULL;
	score = NULL;
	size = NULL;
	if (stripes != nullptr)
	{
		delete stripes;
		stripes = nullptr;
	}
}

template<typename T>
inline Candies<T>::Candies(Candies<T>& c)
{
	score = c.score;
	size = c.size;
	dice = c.dice;
	if (c.stripes != nullptr)
	{
		stripes = new T;
		*stripes = *(c.stripes);
	}
	else
		stripes = nullptr;
}
