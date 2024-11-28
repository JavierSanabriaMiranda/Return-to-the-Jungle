#pragma once

#include "Player.h"

class Mono : public Player
{
public:
	Mono(float x, float y, Game* game);
	string getType() override;
	void jump() override;
	void setVY(float vy) override;
	void update() override;
	void moveX(float axis) override;
	string getBigIcon() override;
	string getSmallIcon() override;

	Animation* aClimbingRight;
	Animation* aClimbingLeft;

	bool canClimb = false;
	int stateClimbing = -1;
};

