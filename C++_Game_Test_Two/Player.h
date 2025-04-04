#pragma once
#include "NormalHeaders.h"

#include "Entity.h"

// ColidingRecs, 5 components
typedef struct ColidingRecs {
    int ID;                 // Unique idetifier == to that of the entity its from
    Rectangle Rec;
} ColidingRecs;

class Player : public Entity
{
public:

    int Health = 100;

    bool FightWin = false;
    int NextFightDelay = 60;
    bool FullColiding = false;
    std::list<bool> IsColidings = {};
    std::list<ColidingRecs> AllColidingRecs = {};

    void Update(std::list<std::variant<Entity, Player>>* MapObjects);
    void CombatUpdate();

    void SelfMove();
    void Colition(std::list<std::variant<Entity, Player>>* MapObjects);
    void FullColition(std::list<std::variant<Entity, Player>>* MapObjects);
    void CombatDelay();
    //TEMP
    void DrawColidingRec();
    //TEMP

    Player(int ID, float X, float Y, float WIDTH, float HIGHT)
        : Entity(ID, X, Y, WIDTH, HIGHT) {
    }
};