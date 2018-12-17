#pragma once
#include <iostream>
#include "Candies.h"
#include "Orange.h"
using namespace std;

template <typename T>
class StripedOrange : public Candies<T>
{
public:
	StripedOrange();
	~StripedOrange();
	StripedOrange(StripedOrange<T>&);
	void Display(T, T);
	Candies<T>* Enlarge(Candies<T>&, Candies<T>&);
};

template<typename T>
inline StripedOrange<T>::StripedOrange()
{
	score = 4;
	size = 4;
	dice = 6;
	color1 = 255;
	color2 = 135;
	color3 = 0;
	stripes = new T;
	*stripes = 3;
}

template<typename T>
inline StripedOrange<T>::~StripedOrange()
{
	score = NULL;
	size = NULL;
	dice = NULL;
	if (stripes != nullptr)
	{
		delete stripes;
		stripes = nullptr;
	}
}

template<typename T>
inline StripedOrange<T>::StripedOrange(StripedOrange<T>&c)
{
	score = c.score;
	size = c.size;
	dice = c.dice;
	color1 = c.color1;
	color2 = c.color2;
	color3 = c.color3;
	if (c.stripes != nullptr)
	{
		stripes = new T;
		*stripes = *(c.stripes);
	}
	else
		stripes = nullptr;
}

template<typename T>
inline void StripedOrange<T>::Display(T x1, T y1)
{
	myRect(x1, y1, x1 + 50, y1 + 50, color1, color2, color3);
    if (stripes != nullptr)
	{
		T newsize = 50 / *stripes;
		T x = x1+50, y = y1 + newsize;
		for (int i = 0; i < *stripes; i++)
		{
			myLine(x1, y, x, y, color1, color1, color1);
			y += newsize;
		}
	}
}

template<typename T>
inline Candies<T>* StripedOrange<T>::Enlarge(Candies<T>&a, Candies<T>&b)
{
	Orange<T>* c = new Orange<T>;
	c->SetScore(a.GetScore()+b.GetScore()+this->GetScore() + this->GetStripes() + a.GetStripes() + b.GetStripes());
	c->SetSize(a.GetSize()+b.GetSize()+this->GetSize() + this->GetStripes() + a.GetStripes() + b.GetStripes());
	return c;
}
