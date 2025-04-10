#include "Enemy.h"
#include "Player.h"

//Updates Enemy Object
void Enemy::Update(bool* Turn)
{
	if (!*Turn && this->ActionDelay > 0) {
		this->ActionDelay--;
	}

	//Draw things [should be last]
	//this->SelfDraw();
	this->DrawSprite();
}

//Handels Atacking during fights
void Enemy::Atack(Player* Player, bool* Turn)
{
	if(this->Health <= 0){ return; }

	if (this->ActionDelay > 0) { return; }
	
	//1 in 40 to roll for the spell
	//this is more comon the more skill
	//the player has
	int Spellrole = Random(1, (60 / Player->Skill));

	//if the spell role is good then its the move to go with
	//if not then it will not then theo other moves are rolled for
	int Role = (Spellrole == 1 && this->SpellUse > 0) ? 0 : Random(1, 3);

	switch (Role)
	{
	//0 is the spell atack
	case 0:
		if (Random(0, 3) != 0) {
			this->SpellUse--;
			this->ActionText = "Enemy Attacked using a spell Dealing 30 Damage";
			Player->Health -= 30;
			Player->WasHit = true;
			Player->ActionDelay = 12;
			Player->FrameCount = 0;
			*Turn = true;
		}
		else {
			this->ActionText = "Enemy Missed There Spell";
			*Turn = true;
		}

		break;
	//1 is the normal atack
	case 1:
		if (Random(0, 19) != 0) {
			this->ActionText = "Enemy Attacked Dealing 10 Damage";
			Player->Health -= 10;
			Player->WasHit = true;
			Player->ActionDelay = 12;
			Player->FrameCount = 0;
			*Turn = true;
		}
		else {
			this->ActionText = "Enemy Missed their Attack";
			*Turn = true;
		}
		break;
	//2 is the heal move
	case 2:
		if (Random(0, 14) != 0) {
			this->ActionText = "Enemy Healed For 10 Health";
			this->Health += 10;

			if (this->Health > 100) this->Health = 100;
			*Turn = true;
		}
		else {
			this->ActionText = "Enemy Missed their Heals";
			*Turn = true;
		}

		break;
	//3 is the strong atack
	case 3:
		if (Random(0, 9) != 0) {
			this->ActionText = "Enemy Attacked Dealing 20 Damage";
			Player->Health -= 20;
			Player->WasHit = true;
			Player->ActionDelay = 12;
			Player->FrameCount = 0;
			*Turn = true;
		}
		else {
			this->ActionText = "Enemy Missed their Specal Attack";
			*Turn = true;
		}

		break;
	//errors
	default:
		std::cout << *Turn << "Fatal Error" << this->Health << "\n";
		WindowShouldClose();
		break;
	}

	this->ActionDelay = 12;
}

void Enemy::DrawSprite()
{
	int tileWidth = (int)(this->SourceRec.width * this->Scail), tileHeight = (int)(this->SourceRec.height * this->Scail);

	float SpotX = this->SourceRec.x;
	Color Hue = WHITE;

	//Was Hit
	if (this->WasHit) {

		this->FrameCount++;
		Hue = LIGHTGRAY;

		if (this->FrameCount <= 4) SpotX += 2;
		if (this->FrameCount >= 5 && this->FrameCount <= 8) SpotX -= 2;
		if (this->FrameCount >= 9 && this->FrameCount <= 12) SpotX += 2;

		if (this->FrameCount >= 13) {
			this->WasHit = false;
			this->FrameCount = 0;
		}
	}

	//DrawTexture(this->Sprite, this->Bounds.x, this->Bounds.y, WHITE);
	
	DrawTexturePro(this->Sprite, { this->SourceRec.x, this->SourceRec.y, ((float)this->Bounds.width / tileWidth) * this->SourceRec.width, ((float)this->Bounds.height / tileHeight) * this->SourceRec.height },
		this->Bounds, { SpotX, this->SourceRec.y }, 0.0f, Hue);
	

}