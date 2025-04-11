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
	//this->SelfDraw();
	this->DrawSprite();
}

void Player::DrawSprite()
{
	float SpotX = this->RectangleDraw.x;
	Color Hue = WHITE;

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
	
	//Was Hit
	if (this->WasHit) {

		this->FrameCount++;
		Hue = LIGHTGRAY;

		if (this->FrameCount < 6) {
			this->HitParticle.update((this->Bounds.x + 50), (this->RectangleDraw.y + 25));
		}

		if (this->FrameCount <= 4) {
			SpotX += 2;
		}
		if (this->FrameCount >= 5 && this->FrameCount <= 8) {
			SpotX -= 4;
		}
		if (this->FrameCount >= 9 && this->FrameCount <= 12) {
			SpotX += 2;
		}

		if (this->FrameCount >= 13) {
			this->WasHit = false;
			this->FrameCount = 0;
		}
	}

AFTERCOUNT:;
	this->SourceRec.x = this->TextureState * this->frameWidth;

	//DrawTexturePro(this->PlayerSpriteSheet, this->SourceRec, this->Bounds, this->RectangleDraw, 0.0f, WHITE);

	int tileWidth = (int)(this->SourceRec.width * this->Scail), tileHeight = (int)(this->SourceRec.height * this->Scail);

	DrawTexturePro(this->PlayerSpriteSheet, { this->SourceRec.x, this->SourceRec.y, ((float)this->Bounds.width / tileWidth) * this->SourceRec.width, ((float)this->Bounds.height / tileHeight) * this->SourceRec.height },
		this->Bounds, { SpotX, this->RectangleDraw.y }, 0.0f, Hue);
	
	if (this->WasHit) this->HitParticle.DrawSprite();
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
	
	this->NormalDamage = this->AtackDamage(false, Enemy->Defence, 45);
	this->SpecalDamage = this->AtackDamage(false, Enemy->Defence, 65);
	this->SpllDamage = this->AtackDamage(true, Enemy->Defence, Random((Enemy->Defence - 10), (Enemy->Defence + 10)));

	switch (Action)
	{
	case 0:
		if (this->SpelllCount > 0) {

			//TEMP
			std::cout << "Spell Damage: " << this->SpllDamage << "\n";
			//TEMP

			this->Hit = true;
			Enemy->Health -= (Enemy->Health - this->SpllDamage <= 0) ? Enemy->Health : this->SpllDamage;
			this->SpelllCount--;
			Enemy->WasHit = true;
			*Turn = false;
		}
		break;
	case 1:
		Enemy->Health -= (Enemy->Health - this->NormalDamage <= 0) ? Enemy->Health : this->NormalDamage;
		Enemy->WasHit = true;
		this->Hit = true;
		*Turn = false;
		break;
	case 2:
		this->Health += ((this->Health + 10) > 100) ? (100 - this->Health) : 10;
		*Turn = false;
		break;
	case 3:
		if (this->SpecalCount > 0) {
			this->Hit = true;
			Enemy->Health -= (Enemy->Health - this->SpecalDamage <= 0) ? Enemy->Health : this->SpecalDamage;
			this->SpecalCount--;
			Enemy->WasHit = true;
			*Turn = false;
		}
		break;
	default:
		std::cout << *Turn << "Fatal Error" << this->Health << "\n";
		WindowShouldClose();
		break;
	}
	
	this->ActionDelay = 12;
}

//the cance you hit
int Player::HitChance(bool IsSpell, int EnemyDefenceCenter, int PlayerDamageCenter)
{
	int HitChance = 0;
	double EnemyDefenceRoll = 0;
	double PlayerAtackeRoll = 0;

	if (IsSpell) {
		HitChance = 100;
		goto ENDSPELL;
	}
	else {
		EnemyDefenceRoll = Random((EnemyDefenceCenter - (EnemyDefenceCenter / static_cast<double>(2))), EnemyDefenceCenter + (EnemyDefenceCenter / static_cast<double>(2)));
		PlayerAtackeRoll = Random((PlayerDamageCenter - (PlayerDamageCenter / static_cast<double>(4))), PlayerDamageCenter + (PlayerDamageCenter / static_cast<double>(3)));
	}

	if (PlayerAtackeRoll > EnemyDefenceRoll) {
		HitChance = static_cast<double>((EnemyDefenceRoll + 2) / static_cast<double>(2 * (PlayerAtackeRoll + 1)) * 100);
	}
	else {
		HitChance = ((PlayerAtackeRoll / static_cast<double>(2 * (EnemyDefenceRoll + 1))) * 100);
	}
	
	//TEMP
	std::cout << "EnemyDefenceRoll: " << EnemyDefenceRoll << "\n";
	std::cout << "PlayerAtackeRoll: " << PlayerAtackeRoll << "\n";
	std::cout << "HitChance: " << HitChance << "\n";
	//TEMP

ENDSPELL:;
	return HitChance;
}

int Player::AtackDamage(bool IsSpell, int EnemyDefenceCenter, int PlayerDamageCenter)
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	int PlayerHitRollTop = PlayerDamageCenter + (PlayerDamageCenter / 2);

	int PlayerHitChance = HitChance(IsSpell, EnemyDefenceCenter, PlayerDamageCenter);

	int AtackDamagePerHit = static_cast<double>(PlayerHitChance * ((PlayerHitRollTop / 2) + (1 / (PlayerHitRollTop + 1)))) / static_cast<double>(100);

	//TEMP
	std::cout << "EnemyDefenceCenter: " << EnemyDefenceCenter << "\n";
	std::cout << "PlayerDamageCenter: " << PlayerDamageCenter << "\n";
	std::cout << "PlayerHitRollTop: " << PlayerHitRollTop << "\n";
	std::cout << "PlayerHitChance: " << PlayerHitChance << "\n";
	std::cout << "AtackDamagePerHit: " << AtackDamagePerHit << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n";
	
	//TEMP

	return AtackDamagePerHit;
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
