#pragma once
#include "NormalHeaders.h"

#include "Entity.h"
#include "Enemy.h"

class Player : public Entity
{
public:

    int Health = 100;

    Texture2D PlayerSpriteSheet = LoadTexture("Textures\\Characters\\Player\\WARRIOR_COMBAT_SPRITE-SHEET.png");

    bool FightWin = false;
    bool DiedinFight = false;
    int NextFightDelay = 60;
    bool FullColiding = false;
    std::list<bool> IsColidings = {};
    std::list<ColidingRecs> AllColidingRecs = {};

    //Texture Things
    Rectangle BaseRectangle;
    Vector2 RectangleDraw = { 0,0 };
    int TextureState = 0;
    int NumberFrames = 3;
    int frameWidth = 0;
    int FrameCount = 0;
    bool Hit = false;

    void Update(std::list<std::variant<Entity, Player>>* MapObjects);
    void CombatUpdate(Enemy* Enemy, bool* Turn);

    int ActionDelay = 12;

    void DrawSprite();
    void SelfMove();
    void Colition(std::list<std::variant<Entity, Player>>* MapObjects);
    void FullColition(std::list<std::variant<Entity, Player>>* MapObjects);
    void CombatDelay();
    void Atack(Enemy* Enemy, int Action, bool* Turn);
    //TEMP
    void DrawColidingRec();
    //TEMP

    Player(int ID, float X, float Y, float WIDTH, float HIGHT)
        : Entity(ID, X, Y, WIDTH, HIGHT) {

        this->frameWidth = ((float)this->PlayerSpriteSheet.width / NumberFrames);

        this->BaseRectangle = Rectangle{ 0, 0, ((float)this->PlayerSpriteSheet.width / 3), (float)this->PlayerSpriteSheet.height };
        this->RectangleDraw = Vector2{ (X * (2 / NumberFrames)), -(Y * (2 / NumberFrames)) };
    }
};