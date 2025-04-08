#pragma once
#include "NormalHeaders.h"

#include "Entity.h"
#include "Enemy.h"

class Player : public Entity
{
public:

    int Health = 100;

    bool FightWin = false;
    bool DiedinFight = false;
    int NextFightDelay = 60;
    bool FullColiding = false;
    std::list<bool> IsColidings = {};
    std::list<ColidingRecs> AllColidingRecs = {};

    void Update(std::list<std::variant<Entity, Player>>* MapObjects);
    void CombatUpdate(Enemy* Enemy);

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
    }
};