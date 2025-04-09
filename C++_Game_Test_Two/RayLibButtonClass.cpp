#include "RayLibButtonClass.h"

void RayLibButtonClass::Update()
{
    *this->mousePoint = GetMousePosition();
    *this->ButtonAction = false;

    if (CheckCollisionPointRec(*this->mousePoint, *this->ButtonBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            *this->ButtonState = 2;
        }
        else {
            *this->ButtonState = 1;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) *this->ButtonAction = true;
    }
    else {
        *this->ButtonState = 0;
    }

    this->BaseRectangle->y = *this->ButtonState * *this->frameHeight;

    this->SelfDraw();
}

void RayLibButtonClass::SelfDraw()
{
    //Temp OutLine
    //DrawRectangleRec(*this->ButtonBounds, Color{ 230, 41, 55, 127 });
    
    //Temp Texture
    //DrawRectangleRec(*this->BaseRectangle, BLUE);

    DrawTexturePro(*this->ButtonTexture, *this->BaseRectangle, *this->ButtonBounds, *this->RectangleDraw, 0.0f, WHITE);
    
    //DrawTextureRec(*this->ButtonTexture, *this->BaseRectangle, *this->RectangleDraw, WHITE); // Draw button frame
    //DrawTextureRec(*this->ButtonTexture, *this->BaseRectangle, *this->RectangleDraw, GRAY); // Draw button frame
}
