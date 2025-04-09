#include "Enemy.h"
#include "Player.h"

//Updates Enemy Object
void Enemy::Update(bool* Turn)
{
	if (!*Turn && this->ActionDelay > 0) {
		this->ActionDelay--;
	}

	//Draw things [should be last]
	this->SelfDraw();
	this->DrawSprite();
}

//Handels Atacking during fights
void Enemy::Atack(Player* Player, bool* Turn)
{
	if(this->Health <= 0){ return; }

	if (this->ActionDelay > 0) { return; }
	else {
		switch (Random(0, 3))
		{
		case 0:
			std::cout << *Turn << " Health [MISSED]\n";
			this->ActionText = "Enemy Missed There Action";
			*Turn = true;
			break;
		case 1:
			std::cout << *Turn << " Attack: 10D\n";
			this->ActionText = "Enemy Attacked Dealing 10 Damage";
			Player->Health -= 10;
			*Turn = true;
			break;
		case 2:
			std::cout << *Turn << " Heal 10HP\n";
			this->ActionText = "Enemy Healed For 10 Health";
			this->Health += 10;

			if (this->Health > 100) this->Health = 100;
			*Turn = true;
			break;
		case 3:
			std::cout << *Turn << " Attack 20D\n";
			this->ActionText = "Enemy Attacked Dealing 20 Damage";
			Player->Health -= 20;
			*Turn = true;
			break;
		default:
			std::cout << *Turn << " ???\n";
			break;
		}

		this->ActionDelay = 12;
	}
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

		if (this->FrameCount <= 4) {
			SpotX += 2;
			//TEMP
			std::cout << "this->SourceRec.x: " << this->SourceRec.x << " SpotX: " << SpotX << "\n";
			//TEMP
		}
		if (this->FrameCount >= 5 && this->FrameCount <= 8) {
			SpotX -= 2;
			//TEMP
			std::cout << "this->SourceRec.x: " << this->SourceRec.x << " SpotX: " << SpotX << "\n";
			//TEMP
		}
		if (this->FrameCount >= 9 && this->FrameCount <= 12) {
			SpotX += 2;
			//TEMP
			std::cout << "this->SourceRec.x: " << this->SourceRec.x << " SpotX: " << SpotX << "\n";
			//TEMP
		}

		if (this->FrameCount >= 13) {
			this->WasHit = false;
			this->FrameCount = 0;
			//TEMP
			std::cout << "this->SourceRec.x: " << this->SourceRec.x << " SpotX: " << SpotX << "\n";
			//TEMP
		}
	}

	//DrawTexture(this->Sprite, this->Bounds.x, this->Bounds.y, WHITE);
	
	DrawTexturePro(this->Sprite, { this->SourceRec.x, this->SourceRec.y, ((float)this->Bounds.width / tileWidth) * this->SourceRec.width, ((float)this->Bounds.height / tileHeight) * this->SourceRec.height },
		this->Bounds, { SpotX, this->SourceRec.y }, 0.0f, Hue);
	

}