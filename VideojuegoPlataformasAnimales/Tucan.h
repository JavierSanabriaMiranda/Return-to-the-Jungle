#pragma once

#include "Player.h"

class Tucan : public Player
{
public:
	Tucan(float x, float y, Game* game);
	void jump() override;
	void update() override;

	int remainingJumps = 2;
	int jumpCoolDown = 10;
};

