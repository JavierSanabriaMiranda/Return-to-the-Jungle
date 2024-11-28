#include "ForbiddenSymbol.h"

ForbiddenSymbol::ForbiddenSymbol(float x, float y, Game* game)
	: Actor("res/prohibido.png", x, y, 70, 70, game)
{
}

void ForbiddenSymbol::draw(float scrollX)
{
	if (canDraw) {
		Actor::draw(scrollX);
		drawCooldown--;
	}
	if (drawCooldown == 0) {
		canDraw = false;
		drawCooldown = 20;
	}
}

void ForbiddenSymbol::show()
{
	canDraw = true;
}