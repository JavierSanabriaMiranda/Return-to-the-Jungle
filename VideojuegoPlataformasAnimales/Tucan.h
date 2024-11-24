#pragma once

#include "Player.h"

class Tucan : public Player
{
	Tucan(float x, float y, Game* game);
	void jump() override;
};

