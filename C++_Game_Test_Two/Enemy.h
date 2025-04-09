#pragma once
#include "NormalHeaders.h"

#include "Entity.h"

class Player;

class Enemy :
    public Entity
{
public:
    int Health = 100;

    //Texture Things
    Texture2D Sprite = LoadTexture("Textures\\Characters\\Enemys\\aaron_gp0_015.png");
    Rectangle SourceRec;
    Vector2 RectangleDraw = { 0,0 };
    int frameWidth = 0;
    bool Hit = false;
    float Scail = 2;

    bool FightWin = false;
    int ActionDelay = 12;
    bool FullColiding = false;
    const char* ActionText = "";
    std::list<bool> IsColidings = {};
    std::list<ColidingRecs> AllColidingRecs = {};

    void Update(bool* Turn);

    void Atack(Player* Player, bool* Turn);
    void DrawSprite();

    Enemy(int ID, float X, float Y, float WIDTH, float HIGHT)
        : Entity(ID, X, Y, WIDTH, HIGHT) {

        this->frameWidth = this->Sprite.width;

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
        this->Bounds.y = this->Bounds.y,
        this->Bounds.width = this->Bounds.width * this->Scail,
        this->Bounds.height = this->Bounds.height * this->Scail
        };

        this->SourceRec = Rectangle{ 0, 0, (float)this->Sprite.width, (float)this->Sprite.height };
        this->RectangleDraw = Vector2{ (X), (Y) };

    }
};

