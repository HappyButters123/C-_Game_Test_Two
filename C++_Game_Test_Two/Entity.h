#pragma once
#include "NormalHeaders.h"

#include "raylib.h"

//float X, float Y, float WIDTH, float HIGHT
class Entity
{
public:
	
	int EntityID = 0;

	//Color To Draw
	Color ThisColor;

	//corecting to place the center point
	//at the bottom of the players hitbox
	Vector2 Oragin = { 0 };

	//player is a Rectangle
	Rectangle Bounds = { 0 };

	//Member Functions
	
	virtual void Update();
	void SelfDraw();

	//constructor
	Entity(int ID, float X, float Y, float WIDTH, float HIGHT) {
		this->EntityID = ID;
		this->Bounds.x = X;
		this->Bounds.y = Y;
		this->Bounds.width = WIDTH;
		this->Bounds.height = HIGHT;

		this->Oragin = { this->Bounds.x + (this->Bounds.width / 2),this->Bounds.y + (this->Bounds.height) };
	
		ThisColor = BLUE;
	}
};

