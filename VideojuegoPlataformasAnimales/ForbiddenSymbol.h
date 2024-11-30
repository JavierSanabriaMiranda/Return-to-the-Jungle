#pragma once
#include "Actor.h"

class ForbiddenSymbol : public Actor
{
public:
	ForbiddenSymbol(float x, float y, Game* game);
	void draw(float scrollX = 0) override;
	void show();

	bool canDraw = false;
	int drawCooldown = 20;
};

