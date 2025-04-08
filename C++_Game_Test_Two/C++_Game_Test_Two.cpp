//Headers that are included in C++
#include "NormalHeaders.h"

//raylib witch is 100% needed for grapics
#include "raylib.h"

//Classes made for this project
#include "RayLibButtonClass.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

//Referance to scroleing through stat menue hadeling
void ScrollableMenu(int* Click);

//Referance to pre fight scen [OLD]
void TwoDSpace(Camera2D CAM, std::list<std::variant<Entity, Player>>* Entitys, RayLibButtonClass BUTTON);

//Referance to pre fight scen [Beta]
void NewTwoDSpace(Player* Player, RayLibButtonClass BUTTON);

//Referance to were the fights happen
void TwoDFightSpace(Camera2D CAM, Player* Player, Enemy* Enemy, int* MenueOption, bool* Turn);

//Win & Loos Screens
void loosSpace();
void WinSpace();

//main game loop & program entry point
int main()
{
    int screenWidth = 1200;
    int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "C++ Game Test 2");

    Entity TestEntityOne(0, 200, 200, 100, 100);
    Entity TestEntityTwo(1, -200, -200, 100, 100);

    Player TestPlayer(2, -500, 200, 80, 112);

    Enemy TestEnemy(2, (250), (-300), 120, 120);

    std::list<std::variant<Entity, Player>> TestObjects = { 
        TestEntityOne,
        TestEntityTwo,
        TestPlayer
    };

    Camera2D MainCamera = { 0 };

    MainCamera.target = { 20.0f, 20.0f };
    MainCamera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    MainCamera.rotation = 0.0f;
    MainCamera.zoom = 1.0f;

    RayLibButtonClass TestButton(100, 400, 3, "Textures\\Menu\\button.png");

    int MenueOption = 0;
    bool Turn = true;

    SetTargetFPS(24);

    while (!WindowShouldClose()) {

        for (auto& Pvar : TestObjects) {
            if (!std::holds_alternative<Player>(Pvar)) {
                continue;
            }

            if (std::get<Player>(Pvar).FullColiding && !std::get<Player>(Pvar).FightWin && !std::get<Player>(Pvar).DiedinFight) {

                TwoDFightSpace(MainCamera, &std::get<Player>(Pvar), &TestEnemy, &MenueOption, &Turn);

                continue;
            }

            //Win
            if (std::get<Player>(Pvar).FightWin) {
                WinSpace();
                continue;
            }

            //Loos
            if (std::get<Player>(Pvar).DiedinFight) {
                loosSpace();
                continue;
            }

            //Pre Fight Screen [Beta]
            NewTwoDSpace(&std::get<Player>(Pvar), TestButton);

            /*
            //Pre Fight Screen [OLD]
            TwoDSpace(MainCamera, &TestObjects, TestButton);
            */
        }
    }

    TestButton.RayLibButtonClassDeconstruct();

    CloseWindow();
}

//aplys Updates to list of entitys
struct UpdateModifier {
    void operator()(Entity& e) { e.Update(); }
};

//pre fight scen [OLD]
void TwoDSpace(Camera2D CAM, std::list<std::variant<Entity, Player>>* Entitys, RayLibButtonClass BUTTON) {
    BeginDrawing();

    ClearBackground(GRAY);

    BeginMode2D(CAM);

    for (auto& var : *Entitys) {
        std::visit(UpdateModifier{}, var);
    }
    
    for (auto& Pvar : *Entitys) {
        if (std::holds_alternative<Player>(Pvar)) {
            std::get<Player>(Pvar).Update(Entitys);
        }
    }

    EndMode2D();

    EndDrawing();
}

//Pre Fight Scen [Menu]
void NewTwoDSpace(Player* Player, RayLibButtonClass BUTTON) {
    
    if (Player->FullColiding) {
        Player->FullColiding = false;
        Player->FightWin = false;
    }
    BeginDrawing();

    ClearBackground(GRAY);

    BUTTON.Update();

    if (*BUTTON.ButtonAction) {
        Player->FullColiding = true;
    }

    EndDrawing();
}

//Win Screen Test
void WinSpace() {
    
    BeginDrawing();

    ClearBackground(GRAY);

    DrawText("You Win!", 10, 10, 50, GREEN);

    EndDrawing();
}

//Loss Screen Test
void loosSpace() {
    
    BeginDrawing();

    ClearBackground(GRAY);

    DrawText("You Loos!", 10, 10, 50, RED);

    EndDrawing();
}

//scroleing through stat menue hadeling
void ScrollableMenu(int* Click) {

    //0 - 3 alowed

    const char* StatText = " ";

    //Going Down in the menue
    if (IsKeyPressed(KEY_DOWN)) {
        
        *Click = *Click + 1;

        if (*Click >= 4) *Click = 0;
    }

    //Going Up in the menue
    if (IsKeyPressed(KEY_UP)) {
        
        *Click = *Click - 1;

        if (*Click <= -1) *Click = 3;
    }

    //StatText arrow position
    switch (*Click)
    {
    case 0:
        StatText = TextFormat("  ->Spell   Attack: 10D\n    Heal 10HP   Attack 20D");
        break;
    case 1:
        StatText = TextFormat("    Spell ->Attack: 10D\n    Heal 10HP   Attack 20D");
        break;
    case 2:
        StatText = TextFormat("    Spell   Attack: 10D\n  ->Heal 10HP   Attack 20D");
        break;
    case 3:
        StatText = TextFormat("    Spell   Attack: 10D\n    Heal 10HP ->Attack 20D");
        break;
    default:
        StatText = "  ??";
        break;
    }

    //Draw StatText to the menue box
    DrawText(StatText, 0, (GetScreenHeight() - 100), 30, RED);
}

//were the fights happen
void TwoDFightSpace(Camera2D CAM, Player* Player, Enemy* Enemy, int* MenueOption, bool* Turn) {
    
    //whos turn can atack
    switch (*Turn)
    {
    case true:
        Player->Atack(Enemy, *MenueOption, Turn);
        break;
    case false:
        Enemy->Atack(Player, Turn);
        break;
    }
    
    //Draw Stuff
    BeginDrawing();

    ClearBackground(GRAY);

    BeginMode2D(CAM);

    Player->CombatUpdate(Enemy, Turn);
    
    Enemy->Update(Turn);

    EndMode2D();

    DrawRectangle(0, (GetScreenHeight() - 100), GetScreenWidth(), 100, GREEN);

    ScrollableMenu(MenueOption);

    const char* EnemyStatText = TextFormat(" Enemy Health: %i\n Player Health: %i", Enemy->Health, Player->Health);

    DrawText(EnemyStatText, 800, (GetScreenHeight() - 100), 30, RED);

    EndDrawing();
}