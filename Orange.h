#pragma once
#include <iostream>
#include "Candies.h"
using namespace std;

template <typename T>
class Orange : public Candies<T>
{
public:
	Orange();
	~Orange();
	Orange(Orange<T>&);
	Candies<T>* Enlarge(Candies<T>&, Candies<T>&);
};

template<typename T>
inline Orange<T>::Orange()
{
	dice = 1;
	score = 5;
	size = 5;
	color1 = 255;
	color2 = 135;
	color3 = 0;
	stripes = nullptr;
}

template<typename T>
inline Orange<T>::~Orange()
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
inline Orange<T>::Orange(Orange<T>&c)
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
inline Candies<T>* Orange<T>::Enlarge(Candies<T> &a, Candies<T> &b)
{
	Orange<T>* c = new Orange<T>;
	c->SetSize(this->GetSize() + a.GetSize() + b.GetSize());
	c->SetScore(this->GetScore() + a.GetScore() + b.GetScore());
	return c;
}
