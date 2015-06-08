#include "stdafx.h"
#include "Csnake.h"
#include"Oxy.h"

Csnake::Csnake()
: sorce(0)
, MaxSorce(0)
{
}


Csnake::~Csnake()
{
}
CPoint Csnake::ForsnakeUp()
{
	CPoint temp =this->body[n - 1];
	for (int i =this->n - 1; i > 0; i--){
		this->body[i] = this->body[i - 1];
	}
	this->body[0].x--;
	return temp;
}
CPoint Csnake::ForsnakeRight()
{

	CPoint temp = this->body[n - 1];
	for (int i =this-> n - 1; i > 0; i--){
		 this->body[i] = this->body[i - 1];
	}
	 this->body[0].y++;
	return temp;
}
CPoint  Csnake::ForsnakeDown()
{
	CPoint temp = this->body[n - 1];
	for (int i = this->n - 1; i > 0; i--){
		this->body[i] = this->body[i - 1];
	}
	this->body[0].x++;
	return temp;
}
CPoint  Csnake::ForsnakeLeft()
{
	CPoint temp = this->body[n - 1];
	for (int i =this->n - 1; i > 0; i--){
		this->body[i] = this->body[i - 1];
	}
	this->body[0].y--;
	return temp;
}