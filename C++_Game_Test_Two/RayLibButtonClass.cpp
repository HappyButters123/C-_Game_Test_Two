#include "RayLibButtonClass.h"

void RayLibButtonClass::Update()
{
    *this->mousePoint = GetMousePosition();
    *this->ButtonAction = false;

    if (CheckCollisionPointRec(*this->mousePoint, *this->ButtonBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            *this->TextureState = 2;
        }
        else {
            *this->TextureState = 1;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) *this->ButtonAction = true;
    }
    else {
        *this->TextureState = 0;
    }

    this->SourceRec->y = *this->TextureState * *this->frameHeight;

    this->SelfDraw();
}

void RayLibButtonClass::SelfDraw()
{
    int tileWidth = (int)(this->SourceRec->width * *this->Scail);
    int tileHeight = (int)(this->SourceRec->height * *this->Scail);

    DrawTexturePro(*this->ButtonTexture, { this->SourceRec->x, this->SourceRec->y, ((float)this->ButtonBounds->width / tileWidth) * this->SourceRec->width, ((float)this->ButtonBounds->height / tileHeight) * this->SourceRec->height },
        *this->ButtonBounds, *this->RectangleDraw, 0.0f, WHITE);
}
