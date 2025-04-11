#pragma once
#include "Entity.h"
class particle :
    public Entity
{
public:

    //Image-Scailing
    Texture ParticleTexture{};
    Rectangle SourceRec = { 0,0,0,0 };
    Vector2 RectangleDraw = { 0,0 };
    int TextureState = 0;
    int NumberFrames = 6;
    int MaxNumberFrames = 6;
    int frameWidth = 0;
    int FrameCount = 0;
    float Scail = 2.0f;
    //Image-Scailing

    void update(float X, float Y);
    void DrawSprite();

    particle(int ID, float X, float Y, float WIDTH, float HIGHT, const char* TextureText)
        : Entity(ID, X, Y, WIDTH, HIGHT) {
        
        ParticleTexture = LoadTexture(TextureText);
        
        this->frameWidth = ((float)this->ParticleTexture.width / 3);

        this->Bounds = {
        this->Bounds.x = this->Bounds.x,
        this->Bounds.y = this->Bounds.y,
        this->Bounds.width = this->Bounds.width * this->Scail,
        this->Bounds.height = this->Bounds.height * this->Scail
        };

        this->SourceRec = Rectangle{ 0, 0, ((float)this->ParticleTexture.width / 3), (float)this->ParticleTexture.height };
        this->RectangleDraw = Vector2{ (X * (2 / this->NumberFrames)), -(Y * (2 / this->NumberFrames)) };

    }

};

