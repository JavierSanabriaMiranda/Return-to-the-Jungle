#pragma once

#include "Player.h"

class Serpiente : public Player
{
public:
	Serpiente(float x, float y, Game* game);

	void moveX(float axis) override;
	void jump() override;
	string getBigIcon() override;
	string getSmallIcon() override;

	int jumpQuantity = -13;
};

