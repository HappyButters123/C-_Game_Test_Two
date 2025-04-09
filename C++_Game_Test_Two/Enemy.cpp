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

	float SpotX = 50.0f;
	float SpotY = 50.0f;
	
	DrawTexture(this->Sprite, this->Bounds.x, this->Bounds.y, WHITE);
	
	DrawTexturePro(this->Sprite, { this->SourceRec.x, this->SourceRec.y, ((float)this->Bounds.width / tileWidth) * this->SourceRec.width, ((float)this->Bounds.height / tileHeight) * this->SourceRec.height },
		this->Bounds, { SpotX, SpotY }, 0.0f, WHITE);

	DrawCircle(this->RectangleDraw.x, this->RectangleDraw.y, 10, RED);
	DrawCircle(SpotX, SpotY, 10, RED);

	DrawText(TextFormat("X %f Y %f", this->RectangleDraw.x, this->RectangleDraw.y), 0, 0, 30, YELLOW);
	DrawText(TextFormat("X %f Y %f", SpotX, SpotY), 0, 40, 30, YELLOW);
}