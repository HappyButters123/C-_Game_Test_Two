#pragma once
#include <iostream>
#include <memory>

#include "raylib.h"

//NUM_FRAMES, BUTTONTEXTURE[], BUTTONBOUNDSHIGHT, BUTTONBOUNDSWIDTH
class RayLibButtonClass
{
public:

    //Internal~data~~~~~~~~~~~~~~~~~~~~~~~~
    Texture2D* ButtonTexture = new Texture2D();
    float* frameHeight = new float(0.0f);
    int* ButtonState = new int(0);
    bool* ButtonAction = new bool(false);
    Vector2* mousePoint = new Vector2(Vector2{0.0f, 0.0f});
    Rectangle* BaseRectangle = new Rectangle(Rectangle{0,0,0,0});
    Vector2* RectangleDraw = new Vector2(Vector2{ 0.0f, 0.0f });
    Rectangle* ButtonBounds = new Rectangle(Rectangle{ 0,0,0,0 });
    //Internal~data~~~~~~~~~~~~~~~~~~~~~~~~

    //Button?~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int* NumberFrames = new int(0);
    //Button?~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    void Update();
    void SelfDraw();

    
    RayLibButtonClass(
        float X, float Y,
        int NUM_FRAMES,
        const char BUTTONTEXTURE[]
    ) {
        *NumberFrames = NUM_FRAMES;

        *ButtonTexture = LoadTexture(BUTTONTEXTURE);
        *frameHeight = ((float)ButtonTexture->height / *NumberFrames);
        *ButtonState = 0;
        *ButtonAction = false;
        *mousePoint = Vector2{ 0.0f, 0.0f };
        *BaseRectangle = Rectangle{ 0, 0, (float)ButtonTexture->width, *frameHeight };
        *ButtonBounds = Rectangle{ X, Y, (float)ButtonTexture->width, *frameHeight };
        *RectangleDraw = Vector2{ (X * (2 / *NumberFrames)), -(Y * (2 / *NumberFrames)) };
	}

    void RayLibButtonClassDeconstruct(){
        delete NumberFrames;

        delete ButtonTexture;
        delete frameHeight;
        delete ButtonState;
        delete ButtonAction;
        delete mousePoint;
        delete BaseRectangle;
        delete ButtonBounds;
        delete RectangleDraw;
    }
};

