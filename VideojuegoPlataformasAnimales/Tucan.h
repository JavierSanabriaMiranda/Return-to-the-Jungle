#pragma once

#include "Player.h"

class Tucan : public Player
{
public:
	Tucan(float x, float y, Game* game);
	void jump() override;
	void update() override;
	string getBigIcon() override;
	string getSmallIcon() override;

	int remainingJumps = 1;
	int jumpCoolDown = 10;
};

