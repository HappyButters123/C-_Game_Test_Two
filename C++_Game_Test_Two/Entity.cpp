#include "Entity.h"

void Entity::Update()
{
	this->Oragin = { this->Bounds.x + (this->Bounds.width / 2),this->Bounds.y + (this->Bounds.height) };
	
	this->SelfDraw();
}

void Entity::SelfDraw()
{
	DrawRectangleRec(this->Bounds, this->ThisColor);

	//DrawCircle(this->Oragin.x, this->Oragin.y, 16, BLACK);
}

int Entity::Random(int Min, int Max)
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> distrib(Min, Max);

	return distrib(gen);
}
