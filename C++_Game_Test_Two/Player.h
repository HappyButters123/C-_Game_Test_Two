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
    Rectangle SourceRec;
    Vector2 RectangleDraw = { 0,0 };
    int TextureState = 0;
    int NumberFrames = 3;
    int frameWidth = 0;
    int FrameCount = 0;
    bool Hit = false;
    bool WasHit = false;
    float Scail = 2.5;

    void Update(std::list<std::variant<Entity, Player>>* MapObjects);
    void CombatUpdate(Enemy* Enemy, bool* Turn);

    int ActionDelay = 12;

    //Skill starts at 2 and can to up
    int Skill = 2;

    int NormalDamage = 0;
    int SpecalDamage = 0;
    int SpllDamage = 0;

    int SpecalCount = 5;
    int SpelllCount = 1;

    void DrawSprite();
    void SelfMove();
    void Colition(std::list<std::variant<Entity, Player>>* MapObjects);
    void FullColition(std::list<std::variant<Entity, Player>>* MapObjects);
    void CombatDelay();
    void Atack(Enemy* Enemy, int Action, bool* Turn);
    int AtackDamage(int EnemyDefenceCenter, int PlayerDamageCenter);
    int HitChance(int EnemyDefenceCenter, int PlayerDamageCenter);
    //TEMP
    void DrawColidingRec();
    //TEMP

    Player(int ID, float X, float Y, float WIDTH, float HIGHT)
        : Entity(ID, X, Y, WIDTH, HIGHT) {

        this->frameWidth = ((float)this->PlayerSpriteSheet.width / NumberFrames);
        
        //this, \/, is why game devs take math classes
        /*
        Y = 259 at scail 1
        Y = 29 at scail 3
        
        P1(1, 259) P2(3, 29)

        Slope = (Y2-Y1)/(X2-X1) = M

        M = (29 - 259)/(3 - 1) = -115 
        
        //its point slope forme from here

        P1(1, 259)
        Y - Y1 = M(x - X1)

        ~~~~~Simplify~~~~~
        Y - 259 = M(x - 1)
        y = M(x-1) + 259
        y = -115(x-1) + 259
        y = -115x + 115 + 259
        y = -115x + 374

        x in this case is the scail
        so in code it looks like

        ( (-115 * this->Scail) + 374 )

        all of this to draw the player sprite
        at a good height during fights

        this->Bounds.y = ( (-115 * this->Scail) + 374 );
        */

        this->Bounds = {
        this->Bounds.x = this->Bounds.x,
        this->Bounds.y = ( (-115 * this->Scail) + 374 ),
        this->Bounds.width = this->Bounds.width * this->Scail,
        this->Bounds.height = this->Bounds.height * this->Scail
        };

        this->SourceRec = Rectangle{ 0, 0, ((float)this->PlayerSpriteSheet.width / 3), (float)this->PlayerSpriteSheet.height };
        this->RectangleDraw = Vector2{ (X * (2 / NumberFrames)), -(Y * (2 / NumberFrames)) };
    }
};