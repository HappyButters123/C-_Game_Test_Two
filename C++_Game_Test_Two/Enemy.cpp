#include "Enemy.h"
#include "Player.h"

//Updates Enemy Object
void Enemy::Update(bool* Turn)
{
	this->SelfDraw();

	if (!*Turn && this->ActionDelay > 0) {
		this->ActionDelay--;
	}

}

//Handels Atacking during fights
void Enemy::Atack(Player* Player, bool* Turn)
{
	if (this->ActionDelay > 0) { return; }
	else {
		switch (Random(0, 3))
		{
		case 0:
			std::cout << *Turn << " Health [MISSED]\n";
			this->ActionText = "Enemy Missed";
			*Turn = true;
			break;
		case 1:
			std::cout << *Turn << " Attack: 10D\n";
			this->ActionText = "Enemy Attack dealing 10 Damage";
			Player->Health -= 10;
			*Turn = true;
			break;
		case 2:
			std::cout << *Turn << " Heal 10HP\n";
			this->ActionText = "Enemy Healed for 10 Health";
			this->Health += 10;

			if (this->Health > 100) this->Health = 100;
			*Turn = true;
			break;
		case 3:
			std::cout << *Turn << " Attack 20D\n";
			this->ActionText = "Enemy Attack dealing 20 Damage";
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