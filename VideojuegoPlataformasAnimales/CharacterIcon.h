#pragma once
#include "Actor.h"

class CharacterIcon : public Actor
{
public:
	CharacterIcon(string img, float x, float y, int width, int height, Game* game);
	void setIcon(string img);
};

