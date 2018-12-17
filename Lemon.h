#pragma once
#include <iostream>
#include "Candies.h"
#include "Orange.h"
using namespace std;

template <typename T>
class Lemon : public Candies<T>
{
public:
	Lemon();
	~Lemon();
	Lemon(Lemon<T>&);
	Candies<T>* Enlarge(Candies<T>&, Candies<T>&);
};

template<typename T>
inline Lemon<T>::Lemon()
{
	dice = 3;
	score = 1;
	size = 1;
	color1 = 255;
	color2 = 255;
	color3 = 0;
	stripes = nullptr;
}

template<typename T>
inline Lemon<T>::~Lemon()
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
inline Lemon<T>::Lemon(Lemon<T> &c)
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
inline Candies<T>* Lemon<T>::Enlarge(Candies<T> &a, Candies<T> &b)
{
	Orange<T>* c = new Orange<T>;
	c->SetSize(c->GetSize() + this->GetSize() + a.GetSize() + b.GetSize());
	c->SetScore(c->GetScore() + this->GetScore() + a.GetScore() + b.GetScore());
	return c;
}
