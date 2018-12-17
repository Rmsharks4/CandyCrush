#pragma once
#include <iostream>
#include "Candies.h"
using namespace std;

template <typename T>
class StripedStrawberry : public Candies<T>
{
public:
	StripedStrawberry();
	~StripedStrawberry();
	StripedStrawberry(StripedStrawberry<T>&);
	void Display(T, T);
	Candies<T>* Enlarge(Candies<T>&, Candies<T>&);
};

template<typename T>
inline StripedStrawberry<T>::StripedStrawberry()
{
	dice = 4;
	score = 6;
	size = 6;
	color1 = 255;
	color2 = 0;
	color3 = 0;
	stripes = new T;
	*stripes = 4;
}

template<typename T>
inline StripedStrawberry<T>::~StripedStrawberry()
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
inline StripedStrawberry<T>::StripedStrawberry(StripedStrawberry<T>&c)
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
inline void StripedStrawberry<T>::Display(T x1, T y1)
{
	myRect(x1, y1, x1 + 50, y1 + 50, color1, color2, color3);
	if (stripes != nullptr)
	{
		T newsize =  50 / *stripes;
		T x = x1 + 50, y = y1+newsize;
		for (int i = 0; i < *stripes; i++)
		{
			myLine(x1, y, x, y, color1, color1, color1);
			y += newsize;
		}
	}
}

template<typename T>
inline Candies<T>* StripedStrawberry<T>::Enlarge(Candies<T>&a, Candies<T>&b)
{
	StripedStrawberry<T>* c = new StripedStrawberry<T>;
	c->SetScore(a.GetScore()*b.GetScore()*this->GetScore() + this->GetStripes() + a.GetStripes() + b.GetStripes());
	c->SetSize(a.GetSize()*b.GetSize()*this->GetSize() + this->GetStripes() + a.GetStripes() + b.GetStripes());
	c->SetStripes(this->GetStripes() + a.GetStripes() + b.GetStripes());
	return c;
}
