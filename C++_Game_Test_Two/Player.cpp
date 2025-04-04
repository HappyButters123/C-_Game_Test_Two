#include "Player.h"

void Player::Update(std::list<std::variant<Entity, Player>>* MapObjects)
{
	//Moving
	this->SelfMove();
	this->Oragin = { this->Bounds.x + (this->Bounds.width / 2),this->Bounds.y + (this->Bounds.height) };

	this->Colition(MapObjects);
	this->FullColition(MapObjects);
	
	this->CombatDelay();

	//Draws [Should be last]
	this->SelfDraw();
	this->DrawColidingRec();
}

void Player::CombatUpdate()
{
	//Moving
	this->Bounds.x = -500;
	this->Bounds.y = 200;

	this->Oragin = { this->Bounds.x + (this->Bounds.width / 2),this->Bounds.y + (this->Bounds.height) };

	//Temp Exit Fights
	if (IsKeyPressed(KEY_SPACE)) {
		this->NextFightDelay = 60;
		this->FightWin = true;
	}
	//Temp Exit Fights

	//Draws [Should be last]
	this->SelfDraw();
}

void Player::SelfMove()
{
	if (IsKeyDown(KEY_W)) {
		this->Bounds.y -= 2.5f;
	}

	if (IsKeyDown(KEY_A)) {
		this->Bounds.x -= 2.5f;
	}

	if (IsKeyDown(KEY_S)) {
		this->Bounds.y += 2.5f;
	}

	if (IsKeyDown(KEY_D)) {
		this->Bounds.x += 2.5f;
	}
}

void Player::Colition(std::list<std::variant<Entity, Player>>* MapObjects)
{
	this->AllColidingRecs.clear();
	this->IsColidings.clear();

	for (auto& Evar : *MapObjects) {
		if (std::holds_alternative<Entity>(Evar)) {

			this->IsColidings.push_front(CheckCollisionRecs(this->Bounds, std::get<Entity>(Evar).Bounds));
			
			int BolCount = 0;

			for (auto& Bol : this->IsColidings) {
				if (!Bol) BolCount++;
			}

			if (this->IsColidings.size() == BolCount) {
				this->ThisColor = BLUE;
				this->FullColiding = false;
			}

			if (!*this->IsColidings.begin()) continue;

			this->ThisColor = RED;

			ColidingRecs NewRec = {
				std::get<Entity>(Evar).EntityID,
				GetCollisionRec(this->Bounds, std::get<Entity>(Evar).Bounds)
			};

			this->AllColidingRecs.push_front(NewRec);
		}
	}
}

void Player::FullColition(std::list<std::variant<Entity, Player>>* MapObjects)
{
	for (auto& Evar : *MapObjects) {
		if (std::holds_alternative<Entity>(Evar)) {

			for (auto& Rec : this->AllColidingRecs) {
				if (Rec.ID != std::get<Entity>(Evar).EntityID) {
					continue;
				}

				if ((Rec.Rec.width * Rec.Rec.height) == (std::get<Entity>(Evar).Bounds.width * std::get<Entity>(Evar).Bounds.height)) this->FullColiding = true;
			}
		}
	}
}

void Player::CombatDelay()
{
	if (this->FightWin && this->NextFightDelay > 0) this->NextFightDelay--;
	
	if (this->NextFightDelay <= 0) this->FightWin = false;
}

void Player::DrawColidingRec() {
	bool Draw = false;
	for (auto& Bol : this->IsColidings)
	{
		Draw = Bol;

		for (auto& Rec : this->AllColidingRecs) {
			if (Draw) {
				if (this->FullColiding) {
					DrawRectangleRec(Rec.Rec, Color{ 200, 122, 255, 255 });
				}
				else {
					DrawRectangleRec(Rec.Rec, Color{ 200, 122, 255, 127 });
				}
				
			}
		}
	}
}
