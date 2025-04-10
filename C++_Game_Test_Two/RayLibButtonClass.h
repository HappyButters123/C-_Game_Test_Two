#pragma once
#include <iostream>
#include <memory>

#include "raylib.h"

//NUM_FRAMES, BUTTONTEXTURE[], BUTTONBOUNDSHIGHT, BUTTONBOUNDSWIDTH
class RayLibButtonClass
{
public:

    //Internal~data~~~~~~~~~~~~~~~~~~~~~~~~
    int* ButtonID = new int(0);
    Texture2D* ButtonTexture = new Texture2D();
    float* frameHeight = new float(0.0f);
    bool* ButtonAction = new bool(false);
    Vector2* mousePoint = new Vector2(Vector2{0.0f, 0.0f});
    Rectangle* ButtonBounds = new Rectangle(Rectangle{ 0,0,0,0 });
    //Internal~data~~~~~~~~~~~~~~~~~~~~~~~~

    //Image-Scailing
    Rectangle* SourceRec = new Rectangle(Rectangle{ 0,0,0,0 });
    Vector2* RectangleDraw = new Vector2({ 0,0 });
    int* TextureState = new int(0);
    int* NumberFrames = new int(0);
    int* frameWidth = new int(0);
    int* FrameCount = new int(0);
    float* Scail = new float(0.0f);
    //Image-Scailing
    
    void Update();
    void SelfDraw();

    RayLibButtonClass(int ID,
        float X, float Y,
        int NUM_FRAMES,
        const char BUTTONTEXTURE[],
        int SCAIL
    ) {

        *this->ButtonID = ID;
        *this->NumberFrames = NUM_FRAMES;
        *this->Scail = SCAIL;

        *this->ButtonTexture = LoadTexture(BUTTONTEXTURE);
        *this->frameHeight = ((float)ButtonTexture->height / *NumberFrames);
        *this->TextureState = 0;
        *this->ButtonAction = false;
        *this->mousePoint = Vector2{ 0.0f, 0.0f };
        *this->SourceRec = Rectangle{ 0, 0, (float)this->ButtonTexture->width, *this->frameHeight };
        *this->ButtonBounds = Rectangle{ X, Y, ((float)this->ButtonTexture->width * *this->Scail), (*this->frameHeight * *this->Scail) };
        *this->RectangleDraw = Vector2{ (X * (2 / *this->NumberFrames)), -(Y * (2 / *this->NumberFrames)) };
	}

    ~RayLibButtonClass() { /* Kill Buttons */ }

    void RayLibButtonClassDestructor(){
        //Internal~data~~~~~~~~~~~~~~~~~~~~~~~~
        delete this->ButtonTexture;
        delete this->frameHeight;
        delete this->ButtonAction;
        delete this->mousePoint;
        delete this->ButtonBounds;
        //Internal~data~~~~~~~~~~~~~~~~~~~~~~~~

        //Image-Scailing
        delete this->SourceRec;
        delete this->RectangleDraw;
        delete this->TextureState;
        delete this->NumberFrames;
        delete this->frameWidth;
        delete this->FrameCount;
        delete this->Scail;
        //Image-Scailing
    }
};