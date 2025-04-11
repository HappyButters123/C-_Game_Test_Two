#include "particle.h"

void particle::update(float X, float Y)
{
	this->Bounds.x = X;
	this->Bounds.y = Y;
	this->RectangleDraw = Vector2{ (X * (2 / this->NumberFrames)), -(Y * (2 / this->NumberFrames)) };

	if (this->FrameCount <= MaxNumberFrames) {
		this->TextureState += ((this->FrameCount % 2) == 0) ? 1 : 0;
		this->FrameCount--;
	}

	if (this->FrameCount <= 0) {
		this->TextureState = 0;
		this->FrameCount = MaxNumberFrames;
	}
}

void particle::DrawSprite()
{
	if (this->FrameCount > MaxNumberFrames) { return; }

	this->SourceRec.x = this->TextureState * this->frameWidth;

	int tileWidth = (int)(this->SourceRec.width * this->Scail), tileHeight = (int)(this->SourceRec.height * this->Scail);

	DrawTexturePro(this->ParticleTexture, { this->SourceRec.x, this->SourceRec.y, ((float)this->Bounds.width / tileWidth) * this->SourceRec.width, ((float)this->Bounds.height / tileHeight) * this->SourceRec.height },
		this->Bounds, this->RectangleDraw, 0.0f, WHITE);
}
