#pragma once
#include <iostream>
#include "Candies.h"
using namespace std;

template <typename T>
class Strawberry : public Candies<T>
{
public:
	Strawberry();
	~Strawberry();
	Strawberry(Strawberry<T>&);
	Candies<T>* Enlarge(Candies<T>&, Candies<T>&);
};

template<typename T>
inline Strawberry<T>::Strawberry()
{
	dice = 2;
	score = 4;
	size = 4;
	color1 = 255;
	color2 = 0;
	color3 = 0;
	stripes = nullptr;
}

template<typename T>
inline Strawberry<T>::~Strawberry()
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
inline Strawberry<T>::Strawberry(Strawberry<T>&c)
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
inline Candies<T>* Strawberry<T>::Enlarge(Candies<T> &a, Candies<T> &b)
{
	Strawberry<T>* c = new Strawberry<T>;
	c->SetSize(this->GetSize() * a.GetSize() * b.GetSize());
	c->SetScore(this->GetScore() * a.GetScore() * b.GetScore());
	return c;
}
