#pragma once
#include "NormalHeaders.h"

#include "Entity.h"

class Player;

class Enemy :
    public Entity
{
public:
    int Health = 100;

    bool FightWin = false;
    int ActionDelay = 20;
    bool FullColiding = false;
    const char* ActionText = "";
    std::list<bool> IsColidings = {};
    std::list<ColidingRecs> AllColidingRecs = {};

    void Update(bool* Turn);

    void Atack(Player* Player, bool* Turn);

    Enemy(int ID, float X, float Y, float WIDTH, float HIGHT)
        : Entity(ID, X, Y, WIDTH, HIGHT) {
    }
};

