#include "Player.h"
#include "Enemy.h"

//update the player object NOT during fights
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

//update the player object during fights
void Player::CombatUpdate(Enemy* Enemy, bool* Turn)
{
	//Temp Exit Fights  for testing
	if (IsKeyPressed(KEY_SPACE) && !this->Hit) {
		this->NextFightDelay = 60;
		this->FightWin = true;
	}
	//Temp Exit Fights for testing

	if (*Turn && this->ActionDelay > 0) {
		this->ActionDelay--;
	}

	//loos the fight
	if (this->Health <= 0 && !this->Hit) {
		this->NextFightDelay = 60;
		this->DiedinFight = true;
	}

	//win the fight
	if (Enemy->Health <= 0 && !this->Hit) {
		this->NextFightDelay = 60;
		this->FightWin = true;
	}

	//Draws [Should be last]
	this->SelfDraw();
	this->DrawSprite();
}

void Player::DrawSprite()
{
	if (this->Hit) {
		this->FrameCount++;

		if (this->FrameCount <= 3) {
			this->TextureState = 0;
			//TEMP
			std::cout << "0\n";
			//TEMP
			goto AFTERCOUNT;
		}
		if (this->FrameCount >= 4 && this->FrameCount <= 6) {
			this->TextureState = 1;
			//TEMP
			std::cout << "1\n";
			//TEMP
			goto AFTERCOUNT;
		}
		if (this->FrameCount >= 7 && this->FrameCount <= 11) {
			this->TextureState = 2;
			//TEMP
			std::cout << "2\n";
			//TEMP
			goto AFTERCOUNT;
		}

		if (this->FrameCount >= 12) {
			this->TextureState = 0;
			this->FrameCount = 0;
			this->Hit = false;
			//TEMP
			std::cout << "Back to 0\n";
			//TEMP
			goto AFTERCOUNT;
		}
	}
	
AFTERCOUNT:;
	this->SourceRec.x = this->TextureState * this->frameWidth;

	//DrawTexturePro(this->PlayerSpriteSheet, this->SourceRec, this->Bounds, this->RectangleDraw, 0.0f, WHITE);

	int tileWidth = (int)(this->SourceRec.width * this->Scail), tileHeight = (int)(this->SourceRec.height * this->Scail);

	DrawTexturePro(this->PlayerSpriteSheet, { this->SourceRec.x, this->SourceRec.y, ((float)this->Bounds.width / tileWidth) * this->SourceRec.width, ((float)this->Bounds.height / tileHeight) * this->SourceRec.height },
		{ this->Bounds.x, this->Bounds.y, this->Bounds.width, this->Bounds.height }, this->RectangleDraw, 0.0f, WHITE);

}

//moving outside of fights [OLD]
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

//Colition handeling outside of fights [OLD]
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

//100% Colition handeling outside of fights [OLD]
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

//delay between fights [OLD]
void Player::CombatDelay()
{
	if (this->FightWin && this->NextFightDelay > 0) this->NextFightDelay--;
	
	if (this->NextFightDelay <= 0) this->FightWin = false;
}

//exicuts fighting actions
void Player::Atack(Enemy* Enemy, int Action, bool* Turn)
{
	if(this->Health <= 0) { return; }

	if (this->ActionDelay > 0 || !IsKeyPressed(KEY_ENTER)) { return; }
	
	if ((Random(0, 10) == 10) && Action != 0) {
		std::cout << *Turn << "Your Action Missed  " << this->Health << "\n";
	}
	
	switch (Action)
	{
	case 0:
		std::cout << *Turn << " Health [nothing will happen for this, its your own health]  " << this->Health << "\n";
		break;
	case 1:
		std::cout << *Turn << " Attack: 10D  " << this->Health << "\n";
		Enemy->Health -= 10;
		Enemy->WasHit = true;
		this->Hit = true;
		*Turn = false;
		break;
	case 2:
		std::cout << *Turn << " Heal 10HP  " << this->Health << "\n";
		this->Health += 10;

		if (this->Health > 100) this->Health = 100;
		*Turn = false;
		break;
	case 3:
		std::cout << *Turn << " Attack 20D  " << this->Health << "\n";
		this->Hit = true;
		Enemy->Health -= 20;
		Enemy->WasHit = true;
		*Turn = false;
		break;
	default:
		std::cout << *Turn << " ???  " << this->Health << "\n";
		break;
	}

	this->ActionDelay = 12;
}

//Draws Colitions outside of fights [OLD]
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
