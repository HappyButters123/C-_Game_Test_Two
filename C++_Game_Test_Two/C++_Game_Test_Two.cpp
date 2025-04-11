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
void ScrollableMenu(Player Player, int* Click);

//Referance to pre fight scen [OLD]
void TwoDSpace(Camera2D CAM, std::list<std::variant<Entity, Player>>* Entitys, RayLibButtonClass BUTTON);

//Referance to pre fight scen [Beta]
void NewTwoDSpace(Player* Player, std::vector<RayLibButtonClass> Buttons);

//Referance to were the fights happen
void TwoDFightSpace(Camera2D CAM, Player* Player, Enemy* Enemy, Texture2D BackGround, int* MenueOption, bool* Turn);

//Win & Loos Screens
void loosSpace();
void WinSpace();

//main game loop & program entry point
int main()
{
    //FIRST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
    GetScreenHeight();
    GetScreenWidth();
    */
    int screenWidth = 1200;
    int screenHeight = 900;
    
    InitWindow(screenWidth, screenHeight, "C++ Game Test 2");
    //FIRST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    //The texture in the background of the fights
    Texture2D FightBackground2 = LoadTexture("Textures\\Menu\\Backgrounds\\Placeholder_BG.png");
    
    //Entitys/Player/Enemy~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Entity TestEntityOne(0, 200, 200, 100, 100);
    Entity TestEntityTwo(1, -200, -200, 100, 100);

    Player TestPlayer(2, -575, 259, 80, 112);

    Enemy TestEnemy(2, (100), (-320), 96, 96);

    std::list<std::variant<Entity, Player>> TestObjects = { 
        TestEntityOne,
        TestEntityTwo,
        TestPlayer
    };
    //Entitys/Player/Enemy~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //Camera2D~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Camera2D MainCamera = { 0 };

    MainCamera.target = { 20.0f, 20.0f };
    MainCamera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    MainCamera.rotation = 0.0f;
    MainCamera.zoom = 1.0f;
    //Camera2D~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //Buttons~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    RayLibButtonClass TestButton1(0, 100, 400, 3, "Textures\\Menu\\button.png", 1);

    //Explaned Buttons
    /*
    the class of buttons

    RayLibButtonClass

    it needs a name so

    TestButton

    the button needs:
        int ID,
        float X,
        float Y,
        int NUM_FRAMES,
        const char BUTTONTEXTURE[],
        int SCAIL

    for this test we can just make them
        int ID = 1,
        float X  = 0.0f,
        float Y  = 0.0f,
        int NUM_FRAMES = 3,
        this string is the file location of the texture
        const char BUTTONTEXTURE[] = "Textures\Menu\button.png",
        int SCAIL = 1

    in code this looks like

    RayLibButtonClass TestButton{1, 0.0f, 0.0f, 3, "Textures\\Menu\\button.png", 1};

    thats it, just add your "TestButton" to the Buttons vector and thats it

    you can tweek the values here to better fit your needs

    PS: file locations is strings use "\\" in place of "\"
    */
    //Explaned Buttons

    std::vector<RayLibButtonClass> Buttons = {
        TestButton1,
    };
    //Buttons~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    int MenueOption = 0;
    bool Turn = true;

    SetTargetFPS(24);

    while (!WindowShouldClose()) {

        for (auto& Pvar : TestObjects) {
            if (!std::holds_alternative<Player>(Pvar)) {
                continue;
            }

            if (std::get<Player>(Pvar).FullColiding &&
                !std::get<Player>(Pvar).FightWin &&
                !std::get<Player>(Pvar).DiedinFight
                ) {

                TwoDFightSpace(MainCamera, &std::get<Player>(Pvar), &TestEnemy, FightBackground2, &MenueOption, &Turn);

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
            NewTwoDSpace(&std::get<Player>(Pvar), Buttons);

            /*
            //Pre Fight Screen [OLD]
            TwoDSpace(MainCamera, &TestObjects, TestButton);
            */
        }
    }

    TestButton1.~RayLibButtonClass();

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
void NewTwoDSpace(Player* Player, std::vector<RayLibButtonClass> Buttons) {
    
    if (Player->FullColiding) {
        Player->FullColiding = false;
        Player->FightWin = false;
    }
    BeginDrawing();

    ClearBackground(GRAY);

    for (int x = 0; x < Buttons.size(); x++) {
        Buttons[x].Update();

        if (*Buttons[x].ButtonID == 0 && *Buttons[x].ButtonAction) {
            Player->FullColiding = true;
        }
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
void ScrollableMenu(Player Player, int* Click) {

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
        StatText = TextFormat("   >Spell %i/1  Normal Attack\n    Heal 10HP   Special Attack %i/5", Player.SpelllCount, Player.SpecalCount);
        break;
    case 1:
        StatText = TextFormat("    Spell %i/1 >Normal Attack\n    Heal 10HP   Special Attack %i/5", Player.SpelllCount, Player.SpecalCount);
        break;
    case 2:
        StatText = TextFormat("    Spell %i/1  Normal Attack\n   >Heal 10HP   Special Attack %i/5", Player.SpelllCount, Player.SpecalCount);
        break;
    case 3:
        StatText = TextFormat("    Spell %i/1  Normal Attack\n    Heal 10HP  >Special Attack %i/5", Player.SpelllCount, Player.SpecalCount);
        break;
    default:
        StatText = "  ??";
        break;
    }

    //Draw StatText to the menue box
    DrawText(StatText, 0, (GetScreenHeight() - 100), 30, RED);
}

//were the fights happen
void TwoDFightSpace(Camera2D CAM, Player* Player, Enemy* Enemy, Texture2D BackGround, int* MenueOption, bool* Turn) {
    
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

    const char* EnemyOverHeadStats = TextFormat("E Health: %i", Enemy->Health);
    const char* PlayerOverHeadStats = TextFormat("P Health: %i", Player->Health);
    Vector2 P_point = { (Player->Bounds.x), (Player->Bounds.y - 30) };
    Vector2 E_Health_point = { (Enemy->Bounds.x), (Enemy->Bounds.y - 30) };
    Vector2 E_Action_point = { (Player->Bounds.x + Player->Bounds.width), ((Player->Bounds.y + Player->Bounds.height) - 120) };

    //Draw Stuff
    BeginDrawing();

    ClearBackground(GRAY);

    DrawTexture(BackGround, 0, 0, WHITE);

    //this is the background of the atack menue
    DrawRectangle(0, (GetScreenHeight() - 100), GetScreenWidth(), 100, GREEN);

    //this is the options window for things like atacking during the fight
    ScrollableMenu(*Player, MenueOption);

    //2D Begins here (player and enemy are 2D objects, they are drawn here)
        BeginMode2D(CAM);

            Player->CombatUpdate(Enemy, Turn);
    
            Enemy->Update(Turn);

            //Shows the players health over their head
            DrawTextPro(GetFontDefault(), PlayerOverHeadStats, P_point, { 0,0 }, 0.0f, 30.0f, 1.0f, RED);
            
            //Shows the enemys health over their head
            DrawTextPro(GetFontDefault(), EnemyOverHeadStats, E_Health_point, { 0,0 }, 0.0f, 30.0f, 1.0f, RED);
            
            //Tells Player what the enemy just did
            DrawTextPro(GetFontDefault(), Enemy->ActionText.c_str(), E_Action_point, {0,0}, 0.0f, 30.0f, 1.0f, RED);

        EndMode2D();
    //2D Ends here

    EndDrawing();
    //End of Drawing things
}