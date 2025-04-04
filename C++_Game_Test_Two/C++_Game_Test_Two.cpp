#include "NormalHeaders.h"

#include "raylib.h"

#include "Entity.h"
#include "Player.h"

void ScroleTest(int* Click);

void TwoDSpace(Camera2D CAM, std::list<std::variant<Entity, Player>>* Entitys);
void TwoDFightSpace(Camera2D CAM, Player* Player);

int main()
{
    int screenWidth = 1200;
    int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "C++ Game Test 2");

    Entity TestEntityOne(0, 200, 200, 100, 100);
    Entity TestEntityTwo(1, -200, -200, 100, 100);

    Player TestPlayer(2, 300, 300, 120, 120);

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

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        for (auto& Pvar : TestObjects) {
            if (std::holds_alternative<Player>(Pvar)) {
                
                if (std::get<Player>(Pvar).FullColiding && !std::get<Player>(Pvar).FightWin) {
                    
                    TwoDFightSpace(MainCamera, &std::get<Player>(Pvar));
                    continue;
                }
                
                TwoDSpace(MainCamera, &TestObjects);
            }
        }
    }

    CloseWindow();
}

struct UpdateModifier {
    void operator()(Entity& e) { e.Update(); }
};

void TwoDSpace(Camera2D CAM, std::list<std::variant<Entity, Player>>* Entitys) {
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

void TwoDFightSpace(Camera2D CAM, Player* Player) {
    BeginDrawing();

    ClearBackground(GRAY);

    BeginMode2D(CAM);

    Player->CombatUpdate();
    
    DrawRectangle((250), (-300), 200, 200, BLACK);

    EndMode2D();

    DrawRectangle(0, (GetScreenHeight() - 100), GetScreenWidth(), 100, GREEN);

    const char* Text = TextFormat("Health %i", Player->Health );

    DrawText(Text, 0, (GetScreenHeight() - 100), 30, RED);

    EndDrawing();
}

//[OLD] Test for scroling with arrow keys
void ScroleTest(int* Click) {
    
    BeginDrawing();

    ClearBackground(GRAY);
    
    if (IsKeyPressed(KEY_DOWN)) {
        switch (*Click)
        {
        case 0:
            *Click += 1;
            break;
        case 1:
            *Click += 1;
            break;
        case 2:
            *Click += 1;
            break;
        case 3:
            *Click = 0;
            break;
        }
    }

    if (IsKeyPressed(KEY_UP)) {
        switch (*Click)
        {
        case 0:
            *Click = 3;
            break;
        case 1:
            *Click -= 1;
            break;
        case 2:
            *Click -= 1;
            break;
        case 3:
            *Click -= 1;
            break;
        }
    }

    DrawText("  Screen One!", 10, 10, 30, RED);
    DrawText("  Screen Two!", 10, 40, 30, RED);
    DrawText("  Screen Three!", 10, 70, 30, RED);
    DrawText("  Screen Four!", 10, 100, 30, RED);

    switch (*Click)
    {
    case 0:
        DrawText("->", 10, 10, 30, RED);
        break;
    case 1:
        DrawText("->", 10, 40, 30, RED);
        break;
    case 2:
        DrawText("->", 10, 70, 30, RED);
        break;
    case 3:
        DrawText("->", 10, 100, 30, RED);
        break;
    }

    EndDrawing();


}