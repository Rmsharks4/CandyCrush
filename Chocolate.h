#pragma once
#include <iostream>
#include "Candies.h"
using namespace std;

template <typename T>
class Chocolate : public Candies<T>
{
public:
	Chocolate();
	~Chocolate();
	Chocolate(Chocolate<T>&);
	Candies<T>* Enlarge(Candies<T>&,Candies<T>&);
};

template<typename T>
inline Chocolate<T>::Chocolate()
{
	dice = 5;
	score = 5;
	size = 5;
	color1 = 185;
	color2 = 122;
	color3 = 87;
	stripes = nullptr;
}

template<typename T>
inline Chocolate<T>::~Chocolate()
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
inline Chocolate<T>::Chocolate(Chocolate<T>& c)
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
inline Candies<T>* Chocolate<T>::Enlarge(Candies<T> &a, Candies<T> &b)
{
	Chocolate<T>* c = new Chocolate<T>;
	c->SetSize((this->GetSize() + a.GetSize() + b.GetSize())/3);
	c->SetScore((this->GetScore() + a.GetScore() + b.GetScore())/3);
	return c;
}
